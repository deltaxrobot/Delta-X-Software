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

    void addVar(const QString& key, const QVariant& value);
    void removeVar(const QString& key);
    void updateVar(const QString& key, const QVariant& value);
    QVariant getVar(const QString& key) const;
    bool contains(const QString& key);

signals:
    void varAdded(const QString& key, const QVariant& value);
    void varRemoved(const QString& key);
    void varUpdated(const QString& key, const QVariant& value);

private:
    VarManager();

    static VarManager* m_instance;
    QSettings* m_settings;
};

#endif // VARMANAGER_H
