#ifndef VARIABLEMANAGER_H
#define VARIABLEMANAGER_H

#include <QObject>
#include <QHash>
#include <QPointer>
#include <QReadWriteLock>
#include <QSet>
#include <QSettings>
#include <QStandardItemModel>
#include <QTimer>
#include <QVariant>
#include <QVector>
#include <QVector3D>

#include <ObjectInfo.h>

class VariableManager final : public QObject
{
    Q_OBJECT
public:
    enum class Persistence {
        Persistent,
        Runtime
    };
    Q_ENUM(Persistence)

    static VariableManager& instance();

    // Keys passed to the legacy API are absolute. Project-owned components
    // must use the scoped API; no mutable global prefix exists anymore.
    static QString normalizeKey(const QString& key);
    static QString scopedKey(const QString& scope, const QString& key);

    void addItemModel(QStandardItemModel* model);

    void addVar(const QString& absoluteKey, const QVariant& value);
    void addVarSilent(const QString& absoluteKey, const QVariant& value);
    void updateVar(const QString& absoluteKey, const QVariant& value);
    void updateVarSilent(const QString& absoluteKey, const QVariant& value);
    void updateVarAbsolute(const QString& absoluteKey, const QVariant& value);

    void updateVarScoped(const QString& scope, const QString& key,
                         const QVariant& value,
                         Persistence persistence = Persistence::Persistent);
    void updateVarScopedSilent(const QString& scope, const QString& key,
                               const QVariant& value,
                               Persistence persistence = Persistence::Persistent);
    void updateBatchAbsolute(const QHash<QString, QVariant>& values,
                             Persistence persistence = Persistence::Persistent,
                             bool notify = true);
    void updateBatchScoped(const QString& scope,
                           const QHash<QString, QVariant>& values,
                           Persistence persistence = Persistence::Persistent,
                           bool notify = true);

    QVariant getVar(const QString& absoluteKey,
                    QVariant defaultValue = QVariant()) const;
    QVariant getVarScoped(const QString& scope, const QString& key,
                          QVariant defaultValue = QVariant()) const;

    void removeVar(const QString& absoluteKey);
    void removeVarScoped(const QString& scope, const QString& key = QString());
    bool containsSubKey(const QString& absoluteKey) const;
    bool containsSubKeyScoped(const QString& scope, const QString& key = QString()) const;
    bool containsFullKey(const QString& absoluteKey) const;
    bool containsFullKeyScoped(const QString& scope, const QString& key) const;

    // Copy-based object snapshots replace the former raw QVector pointer map.
    // A reader can never race a tracking writer or dereference a stale pointer.
    void updateObjectSnapshot(const QString& scope, const QString& listName,
                              const QVector<ObjectInfo>& objects);
    void removeObjectSnapshot(const QString& scope, const QString& listName);

    QHash<QString, QVariant> snapshot(bool includeRuntime = true) const;
    QStringList keys(const QString& scope = QString(),
                     bool includeRuntime = true) const;

    void scheduleSave(int delayMs = 750);
    QSettings* getSettings();

public slots:
    void saveToQSettings();
    void loadFromQSettings();
    void UpdateVarToModel(QString key, QVariant value);
    void UpdateVarsToModels(QHash<QString, QVariant> values);

signals:
    void varAdded(QString key, QVariant value);
    void varRemoved(QString key);
    void varUpdated(QString key, QVariant value);
    void varsUpdated(QHash<QString, QVariant> values);
    void varsRemoved(QStringList keys);

private:
    explicit VariableManager(QObject* parent = nullptr);
    Q_DISABLE_COPY_MOVE(VariableManager)

    QVariant getObjectInfoValue(const QString& absoluteKey) const;
    QVariant normalizeInputValue(const QVariant& value) const;
    void writeOne(const QString& absoluteKey, const QVariant& value,
                  Persistence persistence, bool notify, bool addedSignal);
    static bool isSameOrDescendant(const QString& candidate,
                                   const QString& root);
    static bool isValidKey(const QString& key);

    mutable QReadWriteLock m_dataLock;
    QHash<QString, QVariant> m_data;
    QSet<QString> m_runtimeKeys;

    mutable QReadWriteLock m_objectLock;
    QHash<QString, QVector<ObjectInfo>> m_objectSnapshots;

    mutable QReadWriteLock m_modelLock;
    QList<QPointer<QStandardItemModel>> m_itemModels;

    QSettings m_settings;
    QTimer* m_saveTimer = nullptr;
    bool m_loaded = false;
};

#endif // VARIABLEMANAGER_H
