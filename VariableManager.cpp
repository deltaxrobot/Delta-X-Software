#include "VariableManager.h"

VariableManager &VariableManager::instance()
{
    static VariableManager _instance;
    return _instance;
}

void VariableManager::addItemModel(QStandardItemModel *model)
{
    model->setHorizontalHeaderLabels(QStringList() << "Name" << "Value");
    connect(&instance(), SIGNAL(varUpdated(QString, QVariant)), this, SLOT(UpdateVarToModel(QString, QVariant)));
    connect(&instance(), SIGNAL(varAdded(QString, QVariant)), this, SLOT(UpdateVarToModel(QString, QVariant)));
    itemModelList.append(model);
}

void VariableManager::addVar(const QString &key, const QVariant &value)
{
    const QString fullKey = getFullKey(key);
    std::lock_guard<std::mutex> lock(dataMutex);
    dataMap[fullKey] = value;
    emit varAdded(fullKey, value);
}

void VariableManager::setVariable(const QString &key, const QVariant &value)
{
    const QString fullKey = getFullKey(key);
    std::lock_guard<std::mutex> lock(dataMutex);
    dataMap[fullKey] = value;
    emit varAdded(fullKey, value);
}

void VariableManager::updateVar(const QString &key, const QVariant &value)
{
    const QString fullKey = getFullKey(key);
    std::lock_guard<std::mutex> lock(dataMutex);
    dataMap[fullKey] = value;
    emit varUpdated(fullKey, value);
}

QVariant VariableManager::getVariable(const QString &key, QVariant defaultValue)
{
    const QString fullKey = getFullKey(key);
    std::lock_guard<std::mutex> lock(dataMutex);
    if(dataMap.find(fullKey) != dataMap.end())
    {
        return dataMap[fullKey];
    }
    return defaultValue;
}

QVariant VariableManager::getVar(const QString &key, QVariant defaultValue)
{
    return getVariable(key);
}

void VariableManager::removeVar(const QString &key)
{
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

bool VariableManager::contains(const QString &key)
{
    const QString fullKey = getFullKey(key);
    std::lock_guard<std::mutex> lock(dataMutex);
    return (dataMap.find(fullKey) != dataMap.end());
}

void VariableManager::saveToQSettings()
{
    std::lock_guard<std::mutex> lock(dataMutex);
//    for(const auto& kv : dataMap)
//    {
//        settings.setValue(kv.first, kv.second);
//    }

    settings.clear();

    foreach (const QString &key, dataMap.keys())
    {
        settings.setValue(key, dataMap[key]);
    }
}

void VariableManager::loadFromQSettings()
{
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
        QStandardItem *parent = model->invisibleRootItem();
        UnityTool::UpdateVarToModel(parent, key, value);
    }
}

const QString VariableManager::getFullKey(const QString key)
{
    QString fullKey = key;
    // Kiểm tra xe key đã có prefix chưa
    
    if (Prefix != "")
    {
        if (!key.startsWith(Prefix))
            fullKey = Prefix + "." + key;
    }

    fullKey.replace("#", "");

    return fullKey;
}
