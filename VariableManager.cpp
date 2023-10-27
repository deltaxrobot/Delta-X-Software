#include "VariableManager.h"

VariableManager &VariableManager::instance()
{
    static VariableManager _instance;
    return _instance;
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
    dataMap.erase(fullKey);
    emit varRemoved(fullKey);
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
    for(const auto& kv : dataMap)
    {
        settings.setValue(kv.first, kv.second);
    }
}

void VariableManager::loadFromQSettings()
{
    std::lock_guard<std::mutex> lock(dataMutex);
    QStringList keys = settings.allKeys();
    for(const QString& key : keys)
    {
        dataMap[key] = settings.value(key);
    }
}

QSettings *VariableManager::getSettings()
{
    saveToQSettings();
    return &settings;
}

const QString VariableManager::getFullKey(const QString key)
{
    QString fullKey = key;
    if (Prefix != "")
    {
        fullKey = Prefix + "." + key;
    }

    fullKey.replace("#", "");

    return fullKey;
}
