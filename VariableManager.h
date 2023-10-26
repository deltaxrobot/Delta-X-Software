#ifndef VARIABLEMANAGER_H
#define VARIABLEMANAGER_H

#include <QSettings>
#include <QVariant>
#include <unordered_map>
#include <mutex>
#include <string>

class VariableManager : public QObject
{
    Q_OBJECT
public:
    // Singleton instance
    static VariableManager& instance();

    void addVar(const QString &key, const QVariant &value);

    // Set variable
    void setVariable(const QString &key, const QVariant &value);
    void updateVar(const QString &key, const QVariant& value);

    // Get variable
    QVariant getVariable(const QString &key, QVariant defaultValue = NULL);
    QVariant getVar(const QString &key, QVariant defaultValue = NULL);

    void removeVar(const QString &key);
    bool contains(const QString &key);

    // Save all variables to QSettings explicitly
    void saveToQSettings();

    // Load all variables from QSettings explicitly
    void loadFromQSettings();

    QSettings *getSettings();

    QString Prefix = "";

signals:
    void varAdded(QString key, QVariant value);
    void varRemoved(QString key);
    void varUpdated(QString key, QVariant value);



private:
    const QString getFullKey(const QString key);

    VariableManager() : settings("./settings.ini", QSettings::IniFormat) {}
    std::map<QString, QVariant> dataMap;
    std::mutex dataMutex;
    QSettings settings;
};


#endif // VARIABLEMANAGER_H
