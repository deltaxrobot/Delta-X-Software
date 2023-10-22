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
    std::map<std::string, QVariant> dataMap;
    std::mutex dataMutex;
    QSettings settings;
};

//#include <QWidget>
//#include <QTreeWidget>
//#include <QCoreApplication>
//#include <QHash>
//#include <QMutex>
//#include <QAbstractItemModel>
//#include <QVariant>
//#include <QDebug>

//class VariableManager : public QWidget
//{
//    Q_OBJECT
//public:
//    explicit VariableManager(QWidget *parent = nullptr);

//    void SetTreeWidget(QTreeWidget* treeWidget);

//    void AddVariable(QString name, QString value);
//    void AddVariable(QString name, QString value, QTreeWidgetItem* item);
//    QString GetValue(QString name);

//    QMap<QString, QString>* GetMap();


//public slots:
//    void changeVariableItem(QTreeWidgetItem *item, int col);

//signals:
//    void variableChanged(QString name, QString value);

//private:
//    QTreeWidgetItem *getItem(QString name, QTreeWidgetItem* rootItem);
//    QTreeWidgetItem *getItem(QString name, QTreeWidget* tree);

//    QTreeWidget* treeWidgetDisplay;
//    QMap<QString, QString>* varPairs;
//};



#endif // VARIABLEMANAGER_H
