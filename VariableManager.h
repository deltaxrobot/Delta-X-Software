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
#include <QTimer>
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
    void addVarSilent(const QString &key, const QVariant &value);

    // Set variable
    void updateVar(const QString &key, const QVariant& value);
    void updateVarSilent(const QString &key, const QVariant& value);

    // Get variable
    QVariant getVar(const QString &key, QVariant defaultValue = QVariant());

    void removeVar(const QString &key);
    bool containsSubKey(const QString &key);
    bool containsFullKey(const QString &key);

    void saveToQSettings();
    // Debounced save to avoid blocking UI on frequent calls
    void scheduleSave(int delayMs = 750);

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
    
    // Performance optimization helpers
    bool isLikelyObjectInfoKey(const QString &fullKey) const;
    void clearKeyCache();
    const QString& getCachedFullKey(const QString& key) const;

    VariableManager();
//    std::map<QString, QVariant> dataMap;
    QHash<QString, QVariant> dataMap;
    mutable std::mutex dataMutex;
    mutable std::mutex objectInfosMutex; // Thread safety for ObjectInfos
    QSettings settings;
    QList<QStandardItemModel*> itemModelList;
    QTimer* m_saveTimer = nullptr;
    
    // Performance optimization caches
    mutable QHash<QString, QString> keyCache;
    mutable std::mutex keyCacheMutex;
};


#endif // VARIABLEMANAGER_H
