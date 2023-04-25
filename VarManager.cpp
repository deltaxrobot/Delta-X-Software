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

void VarManager::addVar(QString key, QVariant value)
{
    if (Prefix != "")
    {
        key = Prefix + "." + key;
    }
    m_settings->setValue(key, value);
    emit varAdded(key, value);
}

void VarManager::removeVar(QString key)
{
    if (Prefix != "")
    {
        key = Prefix + "." + key;
    }
    QStringList keys = m_settings->allKeys();
    for (QString k : keys)
    {
        if (k.startsWith(key))
        {
            m_settings->remove(k);
        }
    }
    emit varRemoved(key);
}

void VarManager::updateVar(QString key, QVariant value)
{
    if (Prefix != "")
    {
        key = Prefix + "." + key;
    }
    m_settings->setValue(key, value);
    emit varUpdated(key, value);
}

QVariant VarManager::getVar(QString key, QVariant defaultValue)
{
    if (Prefix != "")
    {
        key = Prefix + "." + key;
    }
    return m_settings->value(key, defaultValue);
}

bool VarManager::contains(QString key)
{
    if (Prefix != "")
    {
        key = Prefix + "." + key;
    }
    return m_settings->contains(key);
}

QSettings *VarManager::getSettings()
{
    return m_settings;
}
