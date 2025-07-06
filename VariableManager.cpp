#include "VariableManager.h"
#include "qglobal.h"
#include <QDebug>

VariableManager &VariableManager::instance()
{
    static VariableManager _instance;
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
    
    const QString fullKey = getFullKey(key);
    std::lock_guard<std::mutex> lock(dataMutex);
    dataMap[fullKey] = value;
    emit varAdded(fullKey, value);
}

void VariableManager::updateVar(const QString &key, const QVariant &value)
{
    if (!isValidKey(key)) {
        qWarning() << "VariableManager: Invalid key provided to updateVar:" << key;
        return;
    }
    
    const QString fullKey = getFullKey(key);
    std::lock_guard<std::mutex> lock(dataMutex);
    dataMap[fullKey] = value;
    emit varUpdated(fullKey, value);
}

QVariant VariableManager::getVar(const QString &key, QVariant defaultValue)
{
    if (!isValidKey(key)) {
        qWarning() << "VariableManager: Invalid key provided to getVar:" << key;
        return defaultValue;
    }
    
    const QString fullKey = getFullKey(key.trimmed().replace("#", ""));
    
    // First try to get from ObjectInfos
    QVariant objectValue = getObjectInfoValue(fullKey);
    if (objectValue.isValid()) {
        return objectValue;
    }
    
    // Then try to get from variable map
    return getVariableFromMap(fullKey, defaultValue);
}

void VariableManager::removeVar(const QString &key)
{
    if (!isValidKey(key)) {
        qWarning() << "VariableManager: Invalid key provided to removeVar:" << key;
        return;
    }
    
    const QString fullKey = getFullKey(key);
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
}

bool VariableManager::containsSubKey(const QString &key)
{
    if (!isValidKey(key)) {
        return false;
    }
    
    const QString fullKey = getFullKey(key);
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
    
    const QString fullKey = getFullKey(key);
    std::lock_guard<std::mutex> lock(dataMutex);
    return (dataMap.find(fullKey) != dataMap.end());
}

void VariableManager::saveToQSettings()
{
    std::lock_guard<std::mutex> lock(dataMutex);

    settings.clear();

    foreach (const QString &key, dataMap.keys())
    {
        settings.setValue(key, dataMap[key]);
    }
}

void VariableManager::loadFromQSettings()
{
    connect(&instance(), SIGNAL(varUpdated(QString, QVariant)), this, SLOT(UpdateVarToModel(QString, QVariant)));
    connect(&instance(), SIGNAL(varAdded(QString, QVariant)), this, SLOT(UpdateVarToModel(QString, QVariant)));

    std::lock_guard<std::mutex> lock(dataMutex);
    QStringList keys = settings.allKeys();
    for(const QString& key : keys)
    {
        dataMap[key] = settings.value(key);
        emit varAdded(key, settings.value(key));
    }
}

QSettings *VariableManager::getSettings()
{
    saveToQSettings();
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
