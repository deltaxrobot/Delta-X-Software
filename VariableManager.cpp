#include "VariableManager.h"

VariableManager::VariableManager(QWidget *parent) : QWidget(parent)
{
    varPairs = new QMap<QString, QString>();
}

void VariableManager::SetTreeWidget(QTreeWidget *treeWidget)
{
    treeWidgetDisplay = treeWidget;
    connect(treeWidgetDisplay, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(changeVariableItem(QTreeWidgetItem*, int)));
}

void VariableManager::AddVariable(QString name, QString value)
{
    varPairs->insert(name, value);

    QStringList names = name.split('.');

    QTreeWidgetItem* item = getItem(names[0], treeWidgetDisplay);

    // if var is not available, create new
    if (item == NULL)
    {
        item = new QTreeWidgetItem(treeWidgetDisplay);
        item->setText(0, names[0]);
    }

    if (names.size() == 1)
    {
        item->setText(1, value);
        item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);

    }
    // if name has child, add value to child2
    else
    {
        AddVariable(name.mid(names[0].length() + 1), value, item);
    }    

    emit variableChanged(name, value);
}

void VariableManager::AddVariable(QString name, QString value, QTreeWidgetItem *item)
{
    name = name.replace("_", ".");
    QStringList names = name.split('.');

    QTreeWidgetItem* childItem = getItem(names[0], item);

    // if var is not available, create new
    if (childItem == NULL)
    {
        childItem = new QTreeWidgetItem(item);
        childItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);

        childItem->setText(0, names[0]);
    }

    if (names.size() == 1)
    {
        childItem->setText(1, value);

    }
    // if name has child, add value to child
    else
    {
        AddVariable(name.mid(names[0].length() + 1), value, childItem);
    }
}

QString VariableManager::GetValue(QString name)
{
    return varPairs->value(name);
}

void VariableManager::changeVariableItem(QTreeWidgetItem *item, int col)
{
    QString key = item->text(0);
    QString value = item->text(col);
}

QTreeWidgetItem *VariableManager::getItem(QString name, QTreeWidgetItem *rootItem)
{
    for(int i = 0; i < rootItem->childCount(); i++)
    {
        if (rootItem->child(i)->text(0) == name)
            return rootItem->child(i);
    }

    return NULL;
}

QTreeWidgetItem *VariableManager::getItem(QString name, QTreeWidget *tree)
{
    for (int i = 0; i < tree->topLevelItemCount(); i++)
    {
        QTreeWidgetItem* item = treeWidgetDisplay->topLevelItem(i);

        if (item->text(0) == name)
        {
            return item;
        }
    }

    return NULL;
}

QMap<QString, QString> *VariableManager::GetMap()
{
    return varPairs;
}
