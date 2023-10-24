#include "VariableManager.h"

//VariableManager::VariableManager(QWidget *parent) : QWidget(parent)
//{
//    varPairs = new QMap<QString, QString>();
//}

//void VariableManager::SetTreeWidget(QTreeWidget *treeWidget)
//{
//    treeWidgetDisplay = treeWidget;
//    connect(treeWidgetDisplay, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(changeVariableItem(QTreeWidgetItem*, int)));
//}

//void VariableManager::AddVariable(QString name, QString value)
//{
//    varPairs->insert(name, value);

//    QStringList names = name.split('.');

//    QTreeWidgetItem* item = getItem(names[0], treeWidgetDisplay);

//    // if var is not available, create new
//    if (item == NULL)
//    {
//        item = new QTreeWidgetItem(treeWidgetDisplay);
//        item->setText(0, names[0]);
//    }

//    if (names.size() == 1)
//    {
//        item->setText(1, value);
//        item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);

//    }
//    // if name has child, add value to child2
//    else
//    {
//        AddVariable(name.mid(names[0].length() + 1), value, item);
//    }

//    emit variableChanged(name, value);
//}

//void VariableManager::AddVariable(QString name, QString value, QTreeWidgetItem *item)
//{
//    name = name.replace("_", ".");
//    QStringList names = name.split('.');

//    QTreeWidgetItem* childItem = getItem(names[0], item);

//    // if var is not available, create new
//    if (childItem == NULL)
//    {
//        childItem = new QTreeWidgetItem(item);
//        childItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);

//        childItem->setText(0, names[0]);
//    }

//    if (names.size() == 1)
//    {
//        childItem->setText(1, value);

//    }
//    // if name has child, add value to child
//    else
//    {
//        AddVariable(name.mid(names[0].length() + 1), value, childItem);
//    }
//}

//QString VariableManager::GetValue(QString name)
//{
//    return varPairs->value(name);
//}

//void VariableManager::changeVariableItem(QTreeWidgetItem *item, int col)
//{
//    QString key = item->text(0);
//    QString value = item->text(col);
//}

//QTreeWidgetItem *VariableManager::getItem(QString name, QTreeWidgetItem *rootItem)
//{
//    for(int i = 0; i < rootItem->childCount(); i++)
//    {
//        if (rootItem->child(i)->text(0) == name)
//            return rootItem->child(i);
//    }

//    return NULL;
//}

//QTreeWidgetItem *VariableManager::getItem(QString name, QTreeWidget *tree)
//{
//    for (int i = 0; i < tree->topLevelItemCount(); i++)
//    {
//        QTreeWidgetItem* item = treeWidgetDisplay->topLevelItem(i);

//        if (item->text(0) == name)
//        {
//            return item;
//        }
//    }

//    return NULL;
//}

//QMap<QString, QString> *VariableManager::GetMap()
//{
//    return varPairs;
//}

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
    emit varAdded(key, value);
}

void VariableManager::setVariable(const QString &key, const QVariant &value)
{
    const QString fullKey = getFullKey(key);
    std::lock_guard<std::mutex> lock(dataMutex);
    dataMap[fullKey] = value;
    emit varAdded(key, value);
}

void VariableManager::updateVar(const QString &key, const QVariant &value)
{
    const QString fullKey = getFullKey(key);
    std::lock_guard<std::mutex> lock(dataMutex);
    dataMap[fullKey] = value;
    emit varUpdated(key, value);
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
    emit varRemoved(key);
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
    return &settings;
}

const QString VariableManager::getFullKey(const QString key)
{
    QString fullKey = key;
    if (Prefix != "")
    {
        fullKey = Prefix + "." + key;
    }

    return fullKey;
}
