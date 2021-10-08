#ifndef PRINTINGPLUGIN_H
#define PRINTINGPLUGIN_H

#include "form.h"
#include "../../../DeltaRobot-Software/sdk/DeltaXPlugin.h"
#include <QThread>

class IndustrialCameraPlugin : public DeltaXPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.imwi.deltaxstudio" FILE "IndustrialCameraPlugin.json")
    Q_INTERFACES(DeltaXPlugin)

    ~IndustrialCameraPlugin();
    QWidget* GetUI();
    QString GetName();
    QString GetTitle();

public slots:
    void ProcessCommand(QString cmd);
    void TranferEmit(QString msg);
    void GetCaptureImageSignal(cv::Mat mat);
signals:
    void EmitCommand(QString cmd);
    void CapturedImage(cv::Mat mat);
private:
    Form* pluginForm;

    QString pluginName = "industrialcamera";
    QString pluginTitle = "IndustrialCamera";
};

#endif // PRINTINGPLUGIN_H


