#ifndef VARIABLEMANAGER_H
#define VARIABLEMANAGER_H

#include <QWidget>
#include <QTreeWidget>

class VariableManager : public QWidget
{
    Q_OBJECT
public:
    explicit VariableManager(QWidget *parent = nullptr);

    void SetTreeWidget(QTreeWidget* treeWidget);

    void AddVariable(QString name, QString value);
    void AddVariable(QString name, QString value, QTreeWidgetItem* item);

signals:

private:
    QTreeWidgetItem *getItem(QString name, QTreeWidgetItem* rootItem);
    QTreeWidgetItem *getItem(QString name, QTreeWidget* tree);

    QTreeWidget* treeWidgetDisplay;
};

#endif // VARIABLEMANAGER_H
