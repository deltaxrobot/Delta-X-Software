#include "Authority.h"

Authority::Authority(QObject *parent) : QObject(parent), RobotEnableList()
{

}

void Authority::SetPassword(QString pass)
{
    password = pass;
}

bool Authority::IsPassword(QString pass)
{
    if (pass == password)
        return true;

    return false;
}

void Authority::ApplyOperatorSettings()
{
    // ---- Get require ----
    QStringList operatorDisplayWidget;

    for (int i = 0; i < lwOperatorDisplayWidget->count(); i++)
    {
        operatorDisplayWidget.append(lwOperatorDisplayWidget->item(i)->text());
    }

    QStringList operatorDisplayVariable;

    for (int i = 0; i < lwOperatorDisplayVariable->count(); i++)
    {
        operatorDisplayVariable.append(lwOperatorDisplayVariable->item(i)->text());
    }

    operatorGcodeProgram.clear();

    for (int i = 0; i < RobotEnableList.count(); i++)
    {
        layoutOperatorRobotOnOff->removeWidget(RobotEnableList.at(i));

        delete RobotEnableList.at(i);
    }

    RobotEnableList.clear();

    for (int i = 0; i < lwOperatorGcodeProgram->count(); i++)
    {
        QString row = lwOperatorGcodeProgram->item(i)->text();
        operatorGcodeProgram.append(row);

        QString robotName = row.split(':').at(0);

        QCheckBox* cbOperatorEnableRobot = new QCheckBox(fOperatorRobotOnOffPanel);
        cbOperatorEnableRobot->setText(robotName);
        QFont font3;
        font3.setPointSize(12);
        cbOperatorEnableRobot->setFont(font3);
        cbOperatorEnableRobot->setChecked(true);

        layoutOperatorRobotOnOff->addWidget(cbOperatorEnableRobot, i, 0, 1, 1);

        RobotEnableList.append(cbOperatorEnableRobot);
     }

    // ---- Get objects ----

    ProjectManager* projectManager = SoftwareManager::GetInstance()->SoftwareProjectManager;

    if (operatorDisplayWidget.count() > 0)
    {
        QStringList paras = operatorDisplayWidget[0].split("/");
        robotWindow = projectManager->GetProject(paras[0]);
        subDisplayWidget = robotWindow->GetWidget(paras[2]);
        oldSubDisplayWidgetParent = subDisplayWidget->parentWidget();
        wgOperatorDisplay->layout()->addWidget(subDisplayWidget);
    }

    // ---- var ----

    AddVarPair(operatorDisplayVariable);

    UpdateVariableToDisplay();
}

void Authority::ReturnProgramer()
{
    try {
        if (oldSubDisplayWidgetParent == NULL)
            return;
        if (oldSubDisplayWidgetParent->layout() == nullptr)
            return;

        if (lwOperatorDisplayWidget->count() > 0 && oldSubDisplayWidgetParent->layout() != NULL)
        {
            oldSubDisplayWidgetParent->layout()->addWidget(subDisplayWidget);
        }
    }  catch (...) {

    }

}

void Authority::AddVarPair(QStringList list)
{
    foreach(QString str, list)
    {
        QStringList paras = str.split(':');
        if (paras.count() < 2)
            continue;

        Vars.insert(paras[0], paras[1]);
    }
}

void Authority::UpdateVariableToDisplay()
{
    foreach(QString name, Vars.keys())
    {

        QVariant value = VariableManager::instance().getVar(name);
        UpdateVariableToDisplay(name, value);
    }
}

void Authority::UpdateVariableToDisplay(const QString& key, const QVariant& value)
{
    // ---- check if #var is display var
    if (Vars.keys().contains(key) == false)
        return;

    //---- check if #var is new or not
    QTreeWidgetItem* item = NULL;
    bool isNew = true;
    for (int i = 0; i < twOperatorParameter->topLevelItemCount(); i++)
    {
        QString name = Vars.value(key);
        if (twOperatorParameter->topLevelItem(i)->text(0) == name)
        {
            item = twOperatorParameter->topLevelItem(i);
            isNew = false;
        }
    }

    if (isNew == true)
    {
        item = new QTreeWidgetItem(twOperatorParameter);
    }

    if (item == NULL)
        return;

    item->setText(0, Vars.value(key));
    item->setText(1, value.toString());
}
