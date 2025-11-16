#include "VariableManager.h"
#include "qglobal.h"
#include <QDebug>
#include <QSet>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>
#include <QPointF>
#include <QDate>
#include <QTime>
#include <QDateTime>
#include <QRegularExpression>
#include "QtMatrixCompat.h"

VariableManager &VariableManager::instance()
{
    static VariableManager _instance;
    if (!_instance.m_saveTimer) {
        // Lazy init save timer
        _instance.m_saveTimer = new QTimer(&_instance);
        _instance.m_saveTimer->setSingleShot(true);
        QObject::connect(_instance.m_saveTimer, &QTimer::timeout, &_instance, &VariableManager::saveToQSettings);
    }
    return _instance;
}

void VariableManager::addItemModel(QStandardItemModel *model)
{
    if (!model) {
        qWarning() << "VariableManager: Null model provided to addItemModel";
        return;
    }
    model->setHorizontalHeaderLabels(QStringList() << "Name" << "Value");    
    itemModelList.append(model);
}

void VariableManager::addVar(const QString &key, const QVariant &value)
{
    if (!isValidKey(key)) {
        qWarning() << "VariableManager: Invalid key provided to addVar:" << key;
        return;
    }
    
    // Make a copy of the cached full key to avoid dangling reference
    // when purging entries from keyCache below.
    QString fullKey = getCachedFullKey(key);
    std::lock_guard<std::mutex> lock(dataMutex);
    dataMap[fullKey] = value;
    emit varAdded(fullKey, value);
}

void VariableManager::addVarSilent(const QString &key, const QVariant &value)
{
    if (!isValidKey(key)) {
        qWarning() << "VariableManager: Invalid key provided to addVarSilent:" << key;
        return;
    }
    
    QString fullKey = getCachedFullKey(key);
    std::lock_guard<std::mutex> lock(dataMutex);
    dataMap[fullKey] = value;
    // No signal emission
}

void VariableManager::updateVar(const QString &key, const QVariant &value)
{
    if (!isValidKey(key)) {
        qWarning() << "VariableManager: Invalid key provided to updateVar:" << key;
        return;
    }
    
    QString fullKey = getCachedFullKey(key);
    std::lock_guard<std::mutex> lock(dataMutex);
    dataMap[fullKey] = value;
    emit varUpdated(fullKey, value);
}

void VariableManager::updateVarSilent(const QString &key, const QVariant &value)
{
    if (!isValidKey(key)) {
        qWarning() << "VariableManager: Invalid key provided to updateVarSilent:" << key;
        return;
    }
    
    QString fullKey = getCachedFullKey(key);
    std::lock_guard<std::mutex> lock(dataMutex);
    dataMap[fullKey] = value;
    // No signal emission
}

QVariant VariableManager::getVar(const QString &key, QVariant defaultValue)
{
    if (!isValidKey(key)) {
        qWarning() << "VariableManager: Invalid key provided to getVar:" << key;
        return defaultValue;
    }
    
    QString fullKey = getCachedFullKey(key.trimmed().replace("#", ""));
    
    // Optimized flow: Check variable map first (90% of cases)
    QVariant result = getVariableFromMap(fullKey, QVariant());
    if (result.isValid()) {
        return result;
    }
    
    // Only check ObjectInfos for keys that likely contain object data
    if (isLikelyObjectInfoKey(fullKey)) {
        QVariant objectValue = getObjectInfoValue(fullKey);
        if (objectValue.isValid()) {
            return objectValue;
        }
    }
    
    return defaultValue;
}

void VariableManager::removeVar(const QString &key)
{
    if (!isValidKey(key)) {
        qWarning() << "VariableManager: Invalid key provided to removeVar:" << key;
        return;
    }
    
    QString fullKey = getCachedFullKey(key);
    std::lock_guard<std::mutex> lock(dataMutex);
    
    for (auto it = dataMap.begin(); it != dataMap.end();)
    {
        if (it.key().startsWith(fullKey))
        {
            emit varRemoved(it.key());
            it = dataMap.erase(it);
        }
        else
        {
            ++it;
        }
    }
    
    // Clear cache entries that start with this key
    {
        std::lock_guard<std::mutex> cacheLock(keyCacheMutex);
        for (auto it = keyCache.begin(); it != keyCache.end();)
        {
            if (it.value().startsWith(fullKey))
            {
                it = keyCache.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
}

bool VariableManager::containsSubKey(const QString &key)
{
    if (!isValidKey(key)) {
        return false;
    }
    
    QString fullKey = getCachedFullKey(key);
    std::lock_guard<std::mutex> lock(dataMutex);
    for (auto it = dataMap.begin(); it != dataMap.end(); ++it)
    {
        if (it.key().startsWith(fullKey))
        {
            return true;
        }
    }
    return false;
}

bool VariableManager::containsFullKey(const QString &key)
{
    if (!isValidKey(key)) {
        return false;
    }
    
    QString fullKey = getCachedFullKey(key);
    std::lock_guard<std::mutex> lock(dataMutex);
    return (dataMap.find(fullKey) != dataMap.end());
}

void VariableManager::saveToQSettings()
{
    // Take a snapshot under lock to minimize blocking time for writers
    QHash<QString, QVariant> snapshot;
    {
        std::lock_guard<std::mutex> lock(dataMutex);
        snapshot = dataMap; // deep copy
    }

    auto toSettingsFriendly = [](const QVariant &in, QVariant &out) -> bool {
        // Types natively handled well by QSettings (Ini)
        switch (in.type()) {
            case QVariant::Bool:
            case QVariant::Int:
            case QVariant::UInt:
            case QVariant::LongLong:
            case QVariant::ULongLong:
            case QVariant::Double:
            case QVariant::String:
            case QVariant::ByteArray:
            case QVariant::StringList:
            case QVariant::Date:
            case QVariant::Time:
            case QVariant::DateTime:
                out = in; return true;
            default:
                break;
        }
        // Special cases
        if (in.canConvert<QVector3D>()) {
            QVector3D v = in.value<QVector3D>();
            out = QString("%1,%2,%3").arg(v.x()).arg(v.y()).arg(v.z());
            return true;
        }
        if (in.canConvert<QTransform>()) {
            QTransform t = in.value<QTransform>();
            // Serialize as m11,m12,m21,m22,dx,dy
            out = QString("%1,%2,%3,%4,%5,%6")
                      .arg(t.m11(), 0, 'g', 16)
                      .arg(t.m12(), 0, 'g', 16)
                      .arg(t.m21(), 0, 'g', 16)
                      .arg(t.m22(), 0, 'g', 16)
                      .arg(t.dx(),  0, 'g', 16)
                      .arg(t.dy(),  0, 'g', 16);
            return true;
        }
        // QMatrix (legacy) support
        if (in.userType() == qMetaTypeId<QMatrix>()) {
            QMatrix m = in.value<QMatrix>();
            out = QString("%1,%2,%3,%4,%5,%6")
                      .arg(m.m11(), 0, 'g', 16)
                      .arg(m.m12(), 0, 'g', 16)
                      .arg(m.m21(), 0, 'g', 16)
                      .arg(m.m22(), 0, 'g', 16)
                      .arg(m.dx(),  0, 'g', 16)
                      .arg(m.dy(),  0, 'g', 16);
            return true;
        }
        if (in.canConvert<QPointF>()) {
            QPointF p = in.value<QPointF>();
            out = QString("%1,%2").arg(p.x()).arg(p.y());
            return true;
        }
        if (in.canConvert<QUrl>()) {
            out = in.value<QUrl>().toString();
            return true;
        }
        // QVariantMap / QVariantList: serialize to JSON string if possible
        if (in.type() == QVariant::Map || in.type() == QVariant::List) {
            QJsonDocument doc = QJsonDocument::fromVariant(in);
            if (!doc.isNull()) {
                out = QString::fromUtf8(doc.toJson(QJsonDocument::Compact));
                return true;
            }
        }
        // Fallback: try toString; if empty and not useful, skip
        QString s = in.toString();
        if (!s.isEmpty()) { out = s; return true; }
        return false; // unsupported type (e.g., cv::Mat, QMatrix)
    };

    // Remove keys that no longer exist and update only changed values
    const QStringList existingKeys = settings.allKeys();
    QSet<QString> existingSet = QSet<QString>(existingKeys.begin(), existingKeys.end());

    // Build allowed top-level prefixes from snapshot to avoid removing unrelated sections
    QSet<QString> allowedPrefixes;
    for (const QString &k : snapshot.keys()) {
        QString top = k.section('.', 0, 0);
        if (!top.isEmpty()) allowedPrefixes.insert(top);
    }

    // Remove stale keys
    for (const QString &k : existingSet) {
        if (!snapshot.contains(k)) {
            QString top = k.section('.', 0, 0);
            if (allowedPrefixes.contains(top)) {
                settings.remove(k);
            }
        }
    }

    // Write only changed/new keys (convert unsupported types safely)
    for (auto it = snapshot.constBegin(); it != snapshot.constEnd(); ++it) {
        const QString &k = it.key();
        const QVariant &v = it.value();
        QVariant sv;
        if (!toSettingsFriendly(v, sv)) {
            qWarning() << "VariableManager: skip saving unsupported QVariant type for key" << k << ", type=" << v.typeName();
            continue;
        }
        QVariant current = settings.value(k, QVariant());
        if (current != sv) {
            settings.setValue(k, sv);
        }
    }

    settings.sync();
    if (settings.status() != QSettings::NoError) {
        qWarning() << "VariableManager: QSettings sync error:" << settings.status();
    }
}

void VariableManager::scheduleSave(int delayMs)
{
    if (!m_saveTimer) {
        m_saveTimer = new QTimer(this);
        m_saveTimer->setSingleShot(true);
        QObject::connect(m_saveTimer, &QTimer::timeout, this, &VariableManager::saveToQSettings);
    }
    m_saveTimer->start(delayMs);
}

void VariableManager::loadFromQSettings()
{
    connect(&instance(), SIGNAL(varUpdated(QString, QVariant)), this, SLOT(UpdateVarToModel(QString, QVariant)));
    connect(&instance(), SIGNAL(varAdded(QString, QVariant)), this, SLOT(UpdateVarToModel(QString, QVariant)));

    std::lock_guard<std::mutex> lock(dataMutex);
    QStringList keys = settings.allKeys();
    for(const QString& key : keys)
    {
        QVariant raw = settings.value(key);
        QVariant v = raw;
        // Attempt to restore structured types we serialized (JSON / vector formats)
        if (raw.type() == QVariant::String) {
            QString s = raw.toString().trimmed();
            // JSON object/array
            if ((!s.isEmpty()) && (s.front() == '{' || s.front() == '[')) {
                QJsonParseError err; QJsonDocument doc = QJsonDocument::fromJson(s.toUtf8(), &err);
                if (err.error == QJsonParseError::NoError && !doc.isNull()) {
                    v = doc.toVariant();
                }
            } else {
                // Try "x,y" -> QPointF or "x,y,z" -> QVector3D
                const QStringList parts = s.split(',');
                if (parts.size() == 2) {
                    bool ok1=false, ok2=false; double x=parts[0].toDouble(&ok1), y=parts[1].toDouble(&ok2);
                    if (ok1 && ok2) { v = QVariant::fromValue(QPointF(x, y)); }
                } else if (parts.size() == 3) {
                    bool ok1=false, ok2=false, ok3=false; double x=parts[0].toDouble(&ok1), y=parts[1].toDouble(&ok2), z=parts[2].toDouble(&ok3);
                    if (ok1 && ok2 && ok3) { v = QVariant::fromValue(QVector3D(x, y, z)); }
                } else if (parts.size() == 6) {
                    // Interpret as QTransform serialized: m11,m12,m21,m22,dx,dy
                    bool ok[6] = {false,false,false,false,false,false};
                    double a = parts[0].toDouble(&ok[0]);
                    double b = parts[1].toDouble(&ok[1]);
                    double c = parts[2].toDouble(&ok[2]);
                    double d = parts[3].toDouble(&ok[3]);
                    double tx= parts[4].toDouble(&ok[4]);
                    double ty= parts[5].toDouble(&ok[5]);
                    if (ok[0]&&ok[1]&&ok[2]&&ok[3]&&ok[4]&&ok[5]) {
                        QTransform t(a,b,0,
                                     c,d,0,
                                     tx,ty,1);
                        v = QVariant::fromValue(t);
                    }
                }
            }
        }
        dataMap[key] = v;
        emit varAdded(key, v);
    }
}

QSettings *VariableManager::getSettings()
{
    // Do not force-save here to avoid unexpected I/O.
    return &settings;
}

void VariableManager::UpdateVarToModel(QString key, QVariant value)
{
    for (QStandardItemModel* model : itemModelList)
    {
        if (model) {
            QStandardItem *parent = model->invisibleRootItem();
            UnityTool::UpdateVarToModel(parent, key, value);
        }
    }
}

// Private helper methods
QVariant VariableManager::getObjectInfoValue(const QString &fullKey) const
{
    std::lock_guard<std::mutex> lock(objectInfosMutex);
    
    QStringList objKeys = ObjectInfos.keys();
    
    for (const QString &objKey : objKeys)
    {
        if (fullKey.contains(objKey))
        {
            auto objectInfo = ObjectInfos[objKey];
            if (!objectInfo) {
                continue;
            }
            
            // key = "#project0.Objects.0"
            QStringList paras = fullKey.split(".");
            if (paras.size() < 2) {
                continue;
            }
            
            QString last = paras[paras.size() - 1];
            
            // Kiểm tra nếu last là một số nguyên
            bool isInt = false;
            int index = last.toInt(&isInt);

            if (isInt && index >= 0 && index < objectInfo->size())
            {
                return QPointF(objectInfo->at(index).center.x(), objectInfo->at(index).center.y());
            }

            // Kiểm tra nếu có property name (X, Y, Type)
            if (paras.size() >= 3) {
                QString indexS = paras[paras.size() - 2];
                index = indexS.toInt(&isInt);

                if (isInt && index >= 0 && index < objectInfo->size())
                {
                    const ObjectInfo &obj = objectInfo->at(index);
                    if (last == "X")
                    {
                        return obj.center.x();
                    }
                    else if (last == "Y")
                    {
                        return obj.center.y();
                    }
                    else if (last == "Type")
                    {
                        return obj.type;
                    }
                }
            }
        }
    }
    
    return QVariant(); // Invalid variant
}

QVariant VariableManager::getVariableFromMap(const QString &fullKey, const QVariant &defaultValue) const
{
    std::lock_guard<std::mutex> lock(dataMutex);
    auto it = dataMap.find(fullKey);
    if (it != dataMap.end())
    {
        return it.value();
    }
    return defaultValue;
}

bool VariableManager::isValidKey(const QString &key) const
{
    return !key.isEmpty() && !key.trimmed().isEmpty();
}

const QString VariableManager::getFullKey(const QString key) const
{
    QString fullKey = key;
    // Kiểm tra xe key đã có prefix chưa
    
    if (!Prefix.isEmpty())
    {
        if (!key.startsWith(Prefix))
            fullKey = Prefix + "." + key;
    }

    fullKey.replace("#", "");

    return fullKey;
}

// Performance optimization helper methods
const QString& VariableManager::getCachedFullKey(const QString& key) const
{
    std::lock_guard<std::mutex> cacheLock(keyCacheMutex);
    
    auto it = keyCache.find(key);
    if (it != keyCache.end()) {
        return it.value();
    }
    
    // Cache miss - compute and store
    QString fullKey = getFullKey(key);
    keyCache[key] = fullKey;
    return keyCache[key];
}

bool VariableManager::isLikelyObjectInfoKey(const QString &fullKey) const
{
    // Quick pattern check: ObjectInfo keys typically contain numbers and specific patterns
    // Example: "project0.Objects.0.X" or "project0.Objects.5"
    return fullKey.contains("Objects") || 
           (fullKey.contains('.') && fullKey.contains(QRegularExpression("\\d")));
}

void VariableManager::clearKeyCache()
{
    std::lock_guard<std::mutex> cacheLock(keyCacheMutex);
    keyCache.clear();
}
