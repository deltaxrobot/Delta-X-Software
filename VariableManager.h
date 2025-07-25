#ifndef VARIABLEMANAGER_H
#define VARIABLEMANAGER_H

#include <QSettings>
#include <QVariant>
//#include <unordered_map>
#include <QHash>
#include <mutex>
#include <string>
#include <QStandardItemModel>
#include <QVector3D>
#include <UnityTool.h>
#include <ObjectInfo.h>

class VariableManager : public QObject
{
    Q_OBJECT
public:
    // Singleton instance
    static VariableManager& instance();

    void addItemModel(QStandardItemModel* model);

    void addVar(const QString &key, const QVariant &value);

    // Set variable
    void updateVar(const QString &key, const QVariant& value);

    // Get variable
    QVariant getVar(const QString &key, QVariant defaultValue = QVariant());

    void removeVar(const QString &key);
    bool containsSubKey(const QString &key);
    bool containsFullKey(const QString &key);

    void saveToQSettings();

    void loadFromQSettings();

    QSettings *getSettings();

    QString Prefix = "";

    QHash<QString, QVector<ObjectInfo>*> ObjectInfos;

public slots:
    void UpdateVarToModel(QString key, QVariant value);
signals:
    void varAdded(QString key, QVariant value);
    void varRemoved(QString key);
    void varUpdated(QString key, QVariant value);

private:
    // Helper methods for better code organization
    QVariant getObjectInfoValue(const QString &fullKey) const;
    QVariant getVariableFromMap(const QString &fullKey, const QVariant &defaultValue) const;
    bool isValidKey(const QString &key) const;
    const QString getFullKey(const QString key) const;

    VariableManager() : settings("./settings.ini", QSettings::IniFormat)
    {

    }
//    std::map<QString, QVariant> dataMap;
    QHash<QString, QVariant> dataMap;
    mutable std::mutex dataMutex;
    mutable std::mutex objectInfosMutex; // Thread safety for ObjectInfos
    QSettings settings;
    QList<QStandardItemModel*> itemModelList;
};


#endif // VARIABLEMANAGER_H
