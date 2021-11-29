#include "Authority.h"

Authority::Authority(QObject *parent) : QObject(parent)
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

    // ---- Get objects ----

    if (operatorDisplayVariable.count() > 0)
    {
        QStringList paras = operatorDisplayWidget[0].split("/");


        ProjectManager* projectManager = SoftwareManager::GetInstance()->SoftwareProjectManager;

        robotManager = projectManager->GetProject(paras[0]);
        robotWindow = robotManager->GetRobot(paras[1]);
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
    if (lwOperatorDisplayWidget->count() > 0)
    {
        oldSubDisplayWidgetParent->layout()->addWidget(subDisplayWidget);
    }
}

void Authority::AddVarPair(QStringList list)
{
    foreach(QString str, list)
    {
        QStringList paras = str.split(':');
        Vars.insert(paras[0], paras[1]);
    }
}

void Authority::UpdateVariableToDisplay()
{
    foreach(QString name, Vars.keys())
    {
        QString value = SoftwareManager::GetInstance()->ProgramVariableManager->GetValue(name);
        UpdateVariableToDisplay(name, value);
    }
}

void Authority::UpdateVariableToDisplay(QString key, QString value)
{
    // ---- check if #var is display var
    if (Vars.keys().contains(key) == false)
        return;

    //---- check if #var is new or not
    QTreeWidgetItem* item;
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

    item->setText(0, Vars.value(key));
    item->setText(1, value);
}
