#include "VariableManager.h"

#include <algorithm>
#include <utility>
#include <QCoreApplication>
#include <QDate>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonArray>
#include <QMetaObject>
#include <QPointF>
#include <QPolygonF>
#include <QRectF>
#include <QRegularExpression>
#include <QStandardPaths>
#include <QThread>
#include <QTime>
#include <QTransform>
#include <QUrl>

#include "QtMatrixCompat.h"
#include "UnityTool.h"

namespace {
QString resolveSettingsFilePath()
{
    QString baseDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (baseDir.isEmpty())
        baseDir = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    if (baseDir.isEmpty())
        baseDir = QDir::homePath() + QLatin1String("/.DeltaRobotSoftware");

    QDir dir(baseDir);
    if (!dir.exists())
        dir.mkpath(QStringLiteral("."));

    const QString targetPath = dir.filePath(QStringLiteral("settings.ini"));
    const QString legacyPath = QDir(QCoreApplication::applicationDirPath())
                                   .filePath(QStringLiteral("settings.ini"));
    if (!QFileInfo::exists(targetPath) && QFileInfo::exists(legacyPath))
        QFile::copy(legacyPath, targetPath);
    return targetPath;
}

const QString kManifestKey = QStringLiteral("__variables/keys");
const QString kTypePrefix = QStringLiteral("__variable_types/");

bool encodeForSettings(const QVariant& input, QVariant& output, QString& typeTag)
{
    const int typeId = input.metaType().id();
    switch (typeId) {
    case QMetaType::Bool:
    case QMetaType::Int:
    case QMetaType::UInt:
    case QMetaType::LongLong:
    case QMetaType::ULongLong:
    case QMetaType::Double:
    case QMetaType::QString:
    case QMetaType::QByteArray:
    case QMetaType::QStringList:
    case QMetaType::QDate:
    case QMetaType::QTime:
    case QMetaType::QDateTime:
        output = input;
        typeTag = QString::fromLatin1(input.metaType().name());
        return true;
    default:
        break;
    }

    if (typeId == qMetaTypeId<QVector3D>()) {
        const QVector3D value = input.value<QVector3D>();
        output = QStringLiteral("%1,%2,%3")
                     .arg(value.x(), 0, 'g', 16)
                     .arg(value.y(), 0, 'g', 16)
                     .arg(value.z(), 0, 'g', 16);
        typeTag = QStringLiteral("QVector3D");
        return true;
    }
    if (typeId == qMetaTypeId<QPointF>()) {
        const QPointF value = input.toPointF();
        output = QStringLiteral("%1,%2")
                     .arg(value.x(), 0, 'g', 16)
                     .arg(value.y(), 0, 'g', 16);
        typeTag = QStringLiteral("QPointF");
        return true;
    }
    if (typeId == qMetaTypeId<QRectF>()) {
        const QRectF value = input.toRectF();
        output = QStringLiteral("%1,%2,%3,%4")
                     .arg(value.x(), 0, 'g', 16)
                     .arg(value.y(), 0, 'g', 16)
                     .arg(value.width(), 0, 'g', 16)
                     .arg(value.height(), 0, 'g', 16);
        typeTag = QStringLiteral("QRectF");
        return true;
    }
    if (typeId == qMetaTypeId<QPolygonF>()) {
        QJsonArray points;
        const QPolygonF polygon = input.value<QPolygonF>();
        for (const QPointF& point : polygon)
            points.append(QJsonArray{point.x(), point.y()});
        output = QString::fromUtf8(QJsonDocument(points).toJson(QJsonDocument::Compact));
        typeTag = QStringLiteral("QPolygonF");
        return true;
    }
    if (typeId == qMetaTypeId<QTransform>()) {
        const QTransform value = input.value<QTransform>();
        output = QStringLiteral("%1,%2,%3,%4,%5,%6")
                     .arg(value.m11(), 0, 'g', 16)
                     .arg(value.m12(), 0, 'g', 16)
                     .arg(value.m21(), 0, 'g', 16)
                     .arg(value.m22(), 0, 'g', 16)
                     .arg(value.dx(), 0, 'g', 16)
                     .arg(value.dy(), 0, 'g', 16);
        typeTag = QStringLiteral("QTransform");
        return true;
    }
    if (typeId == qMetaTypeId<QMatrix>()) {
        const QMatrix value = input.value<QMatrix>();
        output = QStringLiteral("%1,%2,%3,%4,%5,%6")
                     .arg(value.m11(), 0, 'g', 16)
                     .arg(value.m12(), 0, 'g', 16)
                     .arg(value.m21(), 0, 'g', 16)
                     .arg(value.m22(), 0, 'g', 16)
                     .arg(value.dx(), 0, 'g', 16)
                     .arg(value.dy(), 0, 'g', 16);
        typeTag = QStringLiteral("QMatrix");
        return true;
    }
    if (typeId == QMetaType::QVariantMap || typeId == QMetaType::QVariantList) {
        const QJsonDocument document = QJsonDocument::fromVariant(input);
        if (!document.isNull()) {
            output = QString::fromUtf8(document.toJson(QJsonDocument::Compact));
            typeTag = typeId == QMetaType::QVariantMap
                ? QStringLiteral("QVariantMap") : QStringLiteral("QVariantList");
            return true;
        }
    }
    if (typeId == qMetaTypeId<QUrl>()) {
        output = input.toUrl().toString();
        typeTag = QStringLiteral("QUrl");
        return true;
    }
    return false;
}

QVariant decodeLegacyValue(const QVariant& raw)
{
    if (raw.metaType().id() != QMetaType::QString)
        return raw;

    const QString text = raw.toString().trimmed();
    if (!text.isEmpty() && (text.front() == '{' || text.front() == '[')) {
        QJsonParseError error;
        const QJsonDocument document = QJsonDocument::fromJson(text.toUtf8(), &error);
        if (error.error == QJsonParseError::NoError && !document.isNull())
            return document.toVariant();
    }

    const QStringList parts = text.split(',');
    QVector<double> numbers;
    numbers.reserve(parts.size());
    for (const QString& part : parts) {
        bool ok = false;
        const double number = part.toDouble(&ok);
        if (!ok)
            return raw;
        numbers.append(number);
    }
    if (numbers.size() == 2)
        return QPointF(numbers[0], numbers[1]);
    if (numbers.size() == 3)
        return QVariant::fromValue(QVector3D(numbers[0], numbers[1], numbers[2]));
    if (numbers.size() == 6)
        return QVariant::fromValue(QTransform(numbers[0], numbers[1], 0,
                                              numbers[2], numbers[3], 0,
                                              numbers[4], numbers[5], 1));
    return raw;
}

QVariant decodeTypedValue(const QVariant& raw, const QString& typeTag)
{
    if (typeTag.isEmpty())
        return decodeLegacyValue(raw);
    if (typeTag == QStringLiteral("QString"))
        return raw.toString();
    if (typeTag == QStringLiteral("QVector3D")) {
        const QStringList values = raw.toString().split(',');
        if (values.size() == 3)
            return QVariant::fromValue(QVector3D(values[0].toDouble(),
                                                 values[1].toDouble(),
                                                 values[2].toDouble()));
    }
    if (typeTag == QStringLiteral("QPointF")) {
        const QStringList values = raw.toString().split(',');
        if (values.size() == 2)
            return QPointF(values[0].toDouble(), values[1].toDouble());
    }
    if (typeTag == QStringLiteral("QRectF")) {
        const QStringList values = raw.toString().split(',');
        if (values.size() == 4)
            return QRectF(values[0].toDouble(), values[1].toDouble(),
                          values[2].toDouble(), values[3].toDouble());
    }
    if (typeTag == QStringLiteral("QPolygonF")) {
        QJsonParseError error;
        const QJsonDocument document = QJsonDocument::fromJson(
            raw.toString().toUtf8(), &error);
        if (error.error == QJsonParseError::NoError && document.isArray()) {
            QPolygonF polygon;
            for (const QJsonValue& value : document.array()) {
                const QJsonArray point = value.toArray();
                if (point.size() == 2)
                    polygon.append(QPointF(point[0].toDouble(), point[1].toDouble()));
            }
            return polygon;
        }
    }
    if (typeTag == QStringLiteral("QTransform") || typeTag == QStringLiteral("QMatrix")) {
        const QStringList values = raw.toString().split(',');
        if (values.size() == 6) {
            const double m11 = values[0].toDouble();
            const double m12 = values[1].toDouble();
            const double m21 = values[2].toDouble();
            const double m22 = values[3].toDouble();
            const double dx = values[4].toDouble();
            const double dy = values[5].toDouble();
            if (typeTag == QStringLiteral("QMatrix"))
                return QVariant::fromValue(QMatrix(m11, m12, m21, m22, dx, dy));
            return QVariant::fromValue(QTransform(m11, m12, 0,
                                                  m21, m22, 0,
                                                  dx, dy, 1));
        }
    }
    if (typeTag == QStringLiteral("QVariantMap") ||
        typeTag == QStringLiteral("QVariantList")) {
        QJsonParseError error;
        const QJsonDocument document = QJsonDocument::fromJson(raw.toString().toUtf8(), &error);
        if (error.error == QJsonParseError::NoError)
            return document.toVariant();
    }
    if (typeTag == QStringLiteral("QUrl"))
        return QUrl(raw.toString());
    return raw;
}
}

VariableManager::VariableManager(QObject* parent)
    : QObject(parent),
      m_settings(resolveSettingsFilePath(), QSettings::IniFormat),
      m_saveTimer(new QTimer(this))
{
    qRegisterMetaType<QHash<QString, QVariant>>("QHash<QString,QVariant>");
    m_saveTimer->setSingleShot(true);
    connect(m_saveTimer, &QTimer::timeout, this, &VariableManager::saveToQSettings);
    connect(this, &VariableManager::varAdded,
            this, &VariableManager::UpdateVarToModel);
    connect(this, &VariableManager::varUpdated,
            this, &VariableManager::UpdateVarToModel);
    connect(this, &VariableManager::varsUpdated,
            this, &VariableManager::UpdateVarsToModels);
}

VariableManager& VariableManager::instance()
{
    static VariableManager manager;
    return manager;
}

QString VariableManager::normalizeKey(const QString& key)
{
    QString result = key.trimmed();
    result.remove('#');
    result.remove(QRegularExpression(QStringLiteral("\\s+")));
    while (result.contains(QStringLiteral("..")))
        result.replace(QStringLiteral(".."), QStringLiteral("."));
    while (result.startsWith('.'))
        result.remove(0, 1);
    while (result.endsWith('.'))
        result.chop(1);
    return result;
}

QString VariableManager::scopedKey(const QString& scope, const QString& key)
{
    const QString normalizedScope = normalizeKey(scope);
    const QString normalizedKey = normalizeKey(key);
    if (normalizedScope.isEmpty())
        return normalizedKey;
    if (normalizedKey.isEmpty() || normalizedKey == normalizedScope)
        return normalizedScope;
    if (normalizedKey.startsWith(normalizedScope + '.'))
        return normalizedKey;
    return normalizedScope + '.' + normalizedKey;
}

bool VariableManager::isValidKey(const QString& key)
{
    return !normalizeKey(key).isEmpty();
}

bool VariableManager::isSameOrDescendant(const QString& candidate,
                                         const QString& root)
{
    return candidate == root || candidate.startsWith(root + '.');
}

void VariableManager::addItemModel(QStandardItemModel* model)
{
    if (!model)
        return;
    model->setHorizontalHeaderLabels({QStringLiteral("Name"), QStringLiteral("Value")});
    QWriteLocker locker(&m_modelLock);
    for (const QPointer<QStandardItemModel>& existing : std::as_const(m_itemModels)) {
        if (existing == model)
            return;
    }
    m_itemModels.append(QPointer<QStandardItemModel>(model));
}

QVariant VariableManager::normalizeInputValue(const QVariant& value) const
{
    if (!value.isValid() || value.metaType().id() != QMetaType::QString)
        return value;

    QString text = value.toString().trimmed();
    if (text.isEmpty())
        return value;
    if (text.startsWith('(') && text.endsWith(')') && text.size() > 2)
        text = text.mid(1, text.size() - 2);

    const QStringList parts = text.split(QRegularExpression(QStringLiteral("\\s*,\\s*")),
                                         Qt::SkipEmptyParts);
    QVector<double> numbers;
    numbers.reserve(parts.size());
    for (const QString& part : parts) {
        bool ok = false;
        const double number = part.toDouble(&ok);
        if (!ok)
            return value;
        numbers.append(number);
    }
    if (numbers.size() == 2)
        return QPointF(numbers[0], numbers[1]);
    if (numbers.size() == 3)
        return QVariant::fromValue(QVector3D(numbers[0], numbers[1], numbers[2]));
    return value;
}

void VariableManager::writeOne(const QString& absoluteKey, const QVariant& value,
                               Persistence persistence, bool notify,
                               bool addedSignal)
{
    const QString key = normalizeKey(absoluteKey);
    if (!isValidKey(key))
        return;
    const QVariant normalizedValue = normalizeInputValue(value);
    {
        QWriteLocker locker(&m_dataLock);
        m_data.insert(key, normalizedValue);
        if (persistence == Persistence::Runtime)
            m_runtimeKeys.insert(key);
        else
            m_runtimeKeys.remove(key);
    }
    if (!notify)
        return;
    if (addedSignal)
        emit varAdded(key, normalizedValue);
    else
        emit varUpdated(key, normalizedValue);
}

void VariableManager::addVar(const QString& key, const QVariant& value)
{
    writeOne(key, value, Persistence::Persistent, true, true);
}

void VariableManager::addVarSilent(const QString& key, const QVariant& value)
{
    writeOne(key, value, Persistence::Persistent, false, true);
}

void VariableManager::updateVar(const QString& key, const QVariant& value)
{
    writeOne(key, value, Persistence::Persistent, true, false);
}

void VariableManager::updateVarSilent(const QString& key, const QVariant& value)
{
    writeOne(key, value, Persistence::Persistent, false, false);
}

void VariableManager::updateVarAbsolute(const QString& key, const QVariant& value)
{
    updateVar(key, value);
}

void VariableManager::updateVarScoped(const QString& scope, const QString& key,
                                      const QVariant& value,
                                      Persistence persistence)
{
    writeOne(scopedKey(scope, key), value, persistence, true, false);
}

void VariableManager::updateVarScopedSilent(const QString& scope, const QString& key,
                                            const QVariant& value,
                                            Persistence persistence)
{
    writeOne(scopedKey(scope, key), value, persistence, false, false);
}

void VariableManager::updateBatchAbsolute(const QHash<QString, QVariant>& values,
                                          Persistence persistence, bool notify)
{
    QHash<QString, QVariant> normalized;
    normalized.reserve(values.size());
    for (auto it = values.cbegin(); it != values.cend(); ++it) {
        const QString key = normalizeKey(it.key());
        if (isValidKey(key))
            normalized.insert(key, normalizeInputValue(it.value()));
    }
    if (normalized.isEmpty())
        return;

    {
        QWriteLocker locker(&m_dataLock);
        for (auto it = normalized.cbegin(); it != normalized.cend(); ++it) {
            m_data.insert(it.key(), it.value());
            if (persistence == Persistence::Runtime)
                m_runtimeKeys.insert(it.key());
            else
                m_runtimeKeys.remove(it.key());
        }
    }
    if (!notify)
        return;
    emit varsUpdated(normalized);
}

void VariableManager::updateBatchScoped(const QString& scope,
                                        const QHash<QString, QVariant>& values,
                                        Persistence persistence, bool notify)
{
    QHash<QString, QVariant> qualified;
    qualified.reserve(values.size());
    for (auto it = values.cbegin(); it != values.cend(); ++it)
        qualified.insert(scopedKey(scope, it.key()), it.value());
    updateBatchAbsolute(qualified, persistence, notify);
}

QVariant VariableManager::getVar(const QString& absoluteKey,
                                 QVariant defaultValue) const
{
    const QString key = normalizeKey(absoluteKey);
    if (!isValidKey(key))
        return defaultValue;
    {
        QReadLocker locker(&m_dataLock);
        const auto it = m_data.constFind(key);
        if (it != m_data.cend())
            return it.value();
    }
    const QVariant objectValue = getObjectInfoValue(key);
    return objectValue.isValid() ? objectValue : defaultValue;
}

QVariant VariableManager::getVarScoped(const QString& scope, const QString& key,
                                       QVariant defaultValue) const
{
    return getVar(scopedKey(scope, key), defaultValue);
}

void VariableManager::removeVar(const QString& absoluteKey)
{
    const QString root = normalizeKey(absoluteKey);
    if (!isValidKey(root))
        return;
    QStringList removed;
    {
        QWriteLocker locker(&m_dataLock);
        for (auto it = m_data.begin(); it != m_data.end();) {
            if (isSameOrDescendant(it.key(), root)) {
                removed.append(it.key());
                m_runtimeKeys.remove(it.key());
                it = m_data.erase(it);
            } else {
                ++it;
            }
        }
    }
    if (removed.isEmpty())
        return;
    emit varsRemoved(removed);
    for (const QString& key : std::as_const(removed))
        emit varRemoved(key);
}

void VariableManager::removeVarScoped(const QString& scope, const QString& key)
{
    removeVar(scopedKey(scope, key));
}

bool VariableManager::containsSubKey(const QString& absoluteKey) const
{
    const QString root = normalizeKey(absoluteKey);
    if (!isValidKey(root))
        return false;
    QReadLocker locker(&m_dataLock);
    for (auto it = m_data.cbegin(); it != m_data.cend(); ++it) {
        if (isSameOrDescendant(it.key(), root))
            return true;
    }
    return false;
}

bool VariableManager::containsSubKeyScoped(const QString& scope,
                                           const QString& key) const
{
    return containsSubKey(scopedKey(scope, key));
}

bool VariableManager::containsFullKey(const QString& absoluteKey) const
{
    const QString key = normalizeKey(absoluteKey);
    QReadLocker locker(&m_dataLock);
    return m_data.contains(key);
}

bool VariableManager::containsFullKeyScoped(const QString& scope,
                                            const QString& key) const
{
    return containsFullKey(scopedKey(scope, key));
}

void VariableManager::updateObjectSnapshot(const QString& scope,
                                           const QString& listName,
                                           const QVector<ObjectInfo>& objects)
{
    const QString key = scopedKey(scope, listName);
    if (!isValidKey(key))
        return;
    QWriteLocker locker(&m_objectLock);
    m_objectSnapshots.insert(key, objects);
}

void VariableManager::removeObjectSnapshot(const QString& scope,
                                           const QString& listName)
{
    QWriteLocker locker(&m_objectLock);
    m_objectSnapshots.remove(scopedKey(scope, listName));
}

QVariant VariableManager::getObjectInfoValue(const QString& absoluteKey) const
{
    QReadLocker locker(&m_objectLock);
    QString matchedList;
    for (auto it = m_objectSnapshots.cbegin(); it != m_objectSnapshots.cend(); ++it) {
        if (isSameOrDescendant(absoluteKey, it.key()) &&
            it.key().size() > matchedList.size())
            matchedList = it.key();
    }
    if (matchedList.isEmpty())
        return QVariant();

    const auto snapshotIt = m_objectSnapshots.constFind(matchedList);
    if (snapshotIt == m_objectSnapshots.cend())
        return QVariant();
    const QVector<ObjectInfo>& objects = snapshotIt.value();
    QString suffix = absoluteKey.mid(matchedList.size());
    if (suffix.startsWith('.'))
        suffix.remove(0, 1);
    if (suffix.isEmpty())
        return QVariant();

    const QStringList parts = suffix.split('.');
    bool ok = false;
    const int index = parts[0].toInt(&ok);
    if (!ok || index < 0 || index >= objects.size())
        return QVariant();
    const ObjectInfo& object = objects[index];
    if (parts.size() == 1)
        return QPointF(object.center.x(), object.center.y());

    const QString property = parts[1];
    if (property.compare(QStringLiteral("X"), Qt::CaseInsensitive) == 0) return object.center.x();
    if (property.compare(QStringLiteral("Y"), Qt::CaseInsensitive) == 0) return object.center.y();
    if (property.compare(QStringLiteral("Z"), Qt::CaseInsensitive) == 0) return object.center.z();
    if (property.compare(QStringLiteral("W"), Qt::CaseInsensitive) == 0) return object.width;
    if (property.compare(QStringLiteral("L"), Qt::CaseInsensitive) == 0) return object.height;
    if (property.compare(QStringLiteral("A"), Qt::CaseInsensitive) == 0) return object.angle;
    if (property.compare(QStringLiteral("UID"), Qt::CaseInsensitive) == 0) return object.uid;
    if (property.compare(QStringLiteral("Type"), Qt::CaseInsensitive) == 0) return object.type;
    if (property.compare(QStringLiteral("IsPicked"), Qt::CaseInsensitive) == 0) return object.isPicked;
    if (property.compare(QStringLiteral("ClaimOwner"), Qt::CaseInsensitive) == 0) return object.claimOwner;
    if (property.compare(QStringLiteral("ClaimExpiresAt"), Qt::CaseInsensitive) == 0) return object.claimExpiresAtMs;
    if (property.compare(QStringLiteral("IsClaimed"), Qt::CaseInsensitive) == 0) return !object.claimOwner.isEmpty();
    if (property.compare(QStringLiteral("Offset"), Qt::CaseInsensitive) == 0) return object.offset;
    if (property.compare(QStringLiteral("State"), Qt::CaseInsensitive) == 0) {
        if (object.isPicked) return QStringLiteral("PICKED");
        if (!object.claimOwner.isEmpty()) return QStringLiteral("CLAIMED");
        if (object.missedFrames > 0) return QStringLiteral("LOST");
        return object.confirmed ? QStringLiteral("CONFIRMED") : QStringLiteral("TENTATIVE");
    }
    if (property.compare(QStringLiteral("Confirmed"), Qt::CaseInsensitive) == 0) return object.confirmed;
    if (property.compare(QStringLiteral("HitCount"), Qt::CaseInsensitive) == 0) return object.hitCount;
    if (property.compare(QStringLiteral("MissedFrames"), Qt::CaseInsensitive) == 0) return object.missedFrames;
    if (property.compare(QStringLiteral("LastSeenAt"), Qt::CaseInsensitive) == 0) return object.lastSeenAtMs;
    return QVariant();
}

QHash<QString, QVariant> VariableManager::snapshot(bool includeRuntime) const
{
    QReadLocker locker(&m_dataLock);
    if (includeRuntime)
        return m_data;
    QHash<QString, QVariant> result;
    result.reserve(m_data.size() - m_runtimeKeys.size());
    for (auto it = m_data.cbegin(); it != m_data.cend(); ++it) {
        if (!m_runtimeKeys.contains(it.key()))
            result.insert(it.key(), it.value());
    }
    return result;
}

QStringList VariableManager::keys(const QString& scope, bool includeRuntime) const
{
    const QString root = normalizeKey(scope);
    const QHash<QString, QVariant> values = snapshot(includeRuntime);
    QStringList result;
    result.reserve(values.size());
    for (auto it = values.cbegin(); it != values.cend(); ++it) {
        if (root.isEmpty() || isSameOrDescendant(it.key(), root))
            result.append(it.key());
    }
    result.sort();
    return result;
}

void VariableManager::scheduleSave(int delayMs)
{
    const int safeDelay = qMax(0, delayMs);
    if (QThread::currentThread() != thread()) {
        QMetaObject::invokeMethod(this, [this, safeDelay]() {
            m_saveTimer->start(safeDelay);
        }, Qt::QueuedConnection);
        return;
    }
    m_saveTimer->start(safeDelay);
}

void VariableManager::saveToQSettings()
{
    if (QThread::currentThread() != thread()) {
        QMetaObject::invokeMethod(this, &VariableManager::saveToQSettings,
                                  Qt::QueuedConnection);
        return;
    }

    const QHash<QString, QVariant> persistentValues = snapshot(false);
    const QStringList oldKeys = m_settings.value(kManifestKey).toStringList();
    for (const QString& oldKey : oldKeys) {
        if (!persistentValues.contains(oldKey)) {
            m_settings.remove(oldKey);
            m_settings.remove(kTypePrefix + oldKey);
        }
    }

    QStringList savedKeys;
    savedKeys.reserve(persistentValues.size());
    for (auto it = persistentValues.cbegin(); it != persistentValues.cend(); ++it) {
        QVariant encoded;
        QString typeTag;
        if (!encodeForSettings(it.value(), encoded, typeTag)) {
            qWarning() << "VariableManager: unsupported persistent type"
                       << it.key() << it.value().typeName();
            continue;
        }
        if (m_settings.value(it.key()) != encoded)
            m_settings.setValue(it.key(), encoded);
        m_settings.setValue(kTypePrefix + it.key(), typeTag);
        savedKeys.append(it.key());
    }
    savedKeys.sort();
    m_settings.setValue(kManifestKey, savedKeys);
    m_settings.sync();
    if (m_settings.status() != QSettings::NoError)
        qWarning() << "VariableManager: QSettings sync error" << m_settings.status();
}

void VariableManager::loadFromQSettings()
{
    if (QThread::currentThread() != thread()) {
        QMetaObject::invokeMethod(this, &VariableManager::loadFromQSettings,
                                  Qt::BlockingQueuedConnection);
        return;
    }
    if (m_loaded)
        return;
    m_loaded = true;

    QStringList storedKeys = m_settings.value(kManifestKey).toStringList();
    if (storedKeys.isEmpty()) {
        for (const QString& key : m_settings.allKeys()) {
            if (!key.startsWith(QStringLiteral("__")))
                storedKeys.append(key);
        }
    }

    QHash<QString, QVariant> loaded;
    for (const QString& rawKey : std::as_const(storedKeys)) {
        const QString key = normalizeKey(rawKey);
        if (!isValidKey(key))
            continue;
        const QVariant rawValue = m_settings.value(rawKey);
        const QString typeTag = m_settings.value(kTypePrefix + rawKey).toString();
        loaded.insert(key, normalizeInputValue(decodeTypedValue(rawValue, typeTag)));
    }
    {
        QWriteLocker locker(&m_dataLock);
        for (auto it = loaded.cbegin(); it != loaded.cend(); ++it) {
            m_data.insert(it.key(), it.value());
            m_runtimeKeys.remove(it.key());
        }
    }
    for (auto it = loaded.cbegin(); it != loaded.cend(); ++it)
        emit varAdded(it.key(), it.value());
}

QSettings* VariableManager::getSettings()
{
    return &m_settings;
}

void VariableManager::UpdateVarToModel(QString key, QVariant value)
{
    QList<QPointer<QStandardItemModel>> models;
    {
        QReadLocker locker(&m_modelLock);
        models = m_itemModels;
    }
    bool hasNull = false;
    for (const QPointer<QStandardItemModel>& model : std::as_const(models)) {
        if (!model) {
            hasNull = true;
            continue;
        }
        UnityTool::UpdateVarToModel(model->invisibleRootItem(), key, value);
    }
    if (hasNull) {
        QWriteLocker locker(&m_modelLock);
        m_itemModels.erase(std::remove_if(m_itemModels.begin(), m_itemModels.end(),
            [](const QPointer<QStandardItemModel>& model) { return model.isNull(); }),
            m_itemModels.end());
    }
}

void VariableManager::UpdateVarsToModels(QHash<QString, QVariant> values)
{
    for (auto it = values.cbegin(); it != values.cend(); ++it)
        UpdateVarToModel(it.key(), it.value());
}
