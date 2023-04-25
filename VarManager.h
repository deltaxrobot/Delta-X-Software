#ifndef VARMANAGER_H
#define VARMANAGER_H

#include <QObject>
#include <QSettings>

class VarManager : public QObject
{
    Q_OBJECT

public:
    static VarManager* getInstance();
    ~VarManager();

    void addVar(QString key, QVariant value);
    void removeVar(QString key);
    void updateVar(QString key, QVariant value);
    QVariant getVar(QString key, QVariant defaultValue = NULL);
    bool contains(QString key);
    QSettings *getSettings();

    QString Prefix = "";

signals:
    void varAdded(QString key, QVariant value);
    void varRemoved(QString key);
    void varUpdated(QString key, QVariant value);

private:
    VarManager();

    static VarManager* m_instance;
    QSettings* m_settings;
};

#endif // VARMANAGER_H
