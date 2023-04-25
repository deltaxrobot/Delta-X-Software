#ifndef PRINTINGPLUGIN_H
#define PRINTINGPLUGIN_H

#include "form.h"
#include "../../sdk/DeltaXPlugin.h"
#include <QThread>
#include <QSettings>

class IndustrialCameraPlugin : public DeltaXPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.imwi.deltaxstudio" FILE "IndustrialCameraPlugin.json")
    Q_INTERFACES(DeltaXPlugin)

    ~IndustrialCameraPlugin();
    QWidget* GetUI();
    QString GetName();
    QString GetTitle();
    void LoadSettings(QSettings* setting);
    void SaveSettings(QSettings* setting);

public slots:
    void ProcessCommand(QString cmd);
    void TranferEmit(QString msg);
signals:
    //void EmitCommand(QString cmd);
    void CapturedImage(cv::Mat mat);
    void StartedCapture();
    void RequestCapture();
private:
    Form* pluginForm;

    QString pluginName = "industrialcamera";
    QString pluginTitle = "IndustrialCamera";
};

#endif // PRINTINGPLUGIN_H


