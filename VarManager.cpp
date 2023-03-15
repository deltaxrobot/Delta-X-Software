#include "VarManager.h"

VarManager* VarManager::m_instance = nullptr;

VarManager* VarManager::getInstance()
{
    if (!m_instance) {
        m_instance = new VarManager();
    }
    return m_instance;
}

VarManager::VarManager() : QObject()
{
    m_settings = new QSettings("settings.ini", QSettings::IniFormat);
}

VarManager::~VarManager()
{
    delete m_settings;
}

void VarManager::addVar(const QString& key, const QVariant& value)
{
    m_settings->setValue(key, value);
    emit varAdded(key, value);
}

void VarManager::removeVar(const QString& key)
{
    m_settings->remove(key);
    emit varRemoved(key);
}

void VarManager::updateVar(const QString& key, const QVariant& value)
{
    m_settings->setValue(key, value);
    emit varUpdated(key, value);
}

QVariant VarManager::getVar(const QString& key) const
{
    return m_settings->value(key, NULL);
}

bool VarManager::contains(const QString &key)
{
    return m_settings->contains(key);
}

QSettings *VarManager::getSettings()
{
    return m_settings;
}
