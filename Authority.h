#ifndef AUTHORITY_H
#define AUTHORITY_H

#include <QObject>
#include <QWidget>
#include <SoftwareManager.h>
#include <ProjectManager.h>
#include <RobotWindow.h>
#include <QVBoxLayout>
#include <QGraphicsView>

class Authority : public QObject
{
    Q_OBJECT
public:
    explicit Authority(QObject *parent = nullptr);
    void SetPassword(QString pass);
    bool IsPassword(QString pass);
    void ApplyOperatorSettings();
    void ReturnProgramer();
    void AddVarPair(QStringList list);
    void UpdateVariableToDisplay();

    QString Name = "Delta Robot System";

    QWidget* wgOperatorDisplay;
    QTreeWidget* twOperatorParameter;
    QListWidget* lwOperatorDisplayWidget;
    QListWidget* lwOperatorDisplayVariable;
    QListWidget* lwOperatorGcodeProgram;
    QFrame* fOperatorRobotOnOffPanel;
    QGridLayout* layoutOperatorRobotOnOff;

    QGraphicsView* gvOperatorViewer;

    QList<QCheckBox*> RobotEnableList;

    RobotWindow* robotWindow = NULL;

    QStringList operatorGcodeProgram;
public slots:
    void UpdateVariableToDisplay(const QString& key, const QVariant& value);

signals:

private:

    QString password;
    QMap<QString, QString>  Vars;

    QWidget* oldSubDisplayWidgetParent = NULL;
    QWidget* subDisplayWidget = NULL;

};

#endif // AUTHORITY_H
