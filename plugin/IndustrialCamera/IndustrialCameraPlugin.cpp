#include "IndustrialCameraPlugin.h"

IndustrialCameraPlugin::~IndustrialCameraPlugin()
{
    // Proper cleanup
    if (pluginForm) {
        delete pluginForm;
        pluginForm = nullptr;
    }
}

QWidget *IndustrialCameraPlugin::GetUI()
{
    // Prevent memory leak - only create once
    if (!pluginForm) {
        pluginForm = new Form();
        qRegisterMetaType< cv::Mat >("cv::Mat");
        connect(pluginForm, SIGNAL(EmitEventFromUI(QString)), this, SLOT(TranferEmit(QString)));
        connect(pluginForm->CameraReaderWork, &CameraReader::CapturedImage, this, &IndustrialCameraPlugin::CapturedImage);
        connect(pluginForm->CameraReaderWork, &CameraReader::StartedCapture, this, &IndustrialCameraPlugin::StartedCapture);
        connect(pluginForm->CameraReaderWork, &CameraReader::CaptureFailed,
                this, &IndustrialCameraPlugin::CaptureError);
        connect(this, &IndustrialCameraPlugin::RequestCapture, pluginForm->CameraReaderWork, &CameraReader::ShotImage);
        connect(this, &IndustrialCameraPlugin::RequestConnect, pluginForm->CameraReaderWork, &CameraReader::ConnectCamera);
        setProperty("cameraBackendAvailable", pluginForm->HasAvailableBackend());
        setProperty("cameraBackendStatus", pluginForm->BackendStatus());
    }
    return pluginForm;
}

QString IndustrialCameraPlugin::GetName()
{
    return pluginName;
}

QString IndustrialCameraPlugin::GetTitle()
{
    return pluginTitle;
}

void IndustrialCameraPlugin::LoadSettings(QSettings *setting)
{
    if (pluginForm && setting) {
        pluginForm->LoadSettings(setting);
    }
}

void IndustrialCameraPlugin::SaveSettings(QSettings *setting)
{
    if (pluginForm && setting) {
        pluginForm->SaveSettings(setting);
    }
}

QString IndustrialCameraPlugin::id() const
{
    return pluginName;
}

QString IndustrialCameraPlugin::displayName() const
{
    return pluginTitle;
}

QString IndustrialCameraPlugin::version() const
{
    return QStringLiteral("2.0.0");
}

QStringList IndustrialCameraPlugin::capabilities() const
{
    return {QStringLiteral("camera.capture"), QStringLiteral("commands"),
            QStringLiteral("panel")};
}

void IndustrialCameraPlugin::loadSettings(QSettings& settings)
{
    LoadSettings(&settings);
}

void IndustrialCameraPlugin::saveSettings(QSettings& settings) const
{
    if (pluginForm)
        pluginForm->SaveSettings(&settings);
}

QWidget* IndustrialCameraPlugin::panel()
{
    return GetUI();
}

bool IndustrialCameraPlugin::executeCommand(const QString& command,
                                            const QVariantMap& arguments,
                                            QVariantMap* result,
                                            QString* error)
{
    if (!arguments.isEmpty()) {
        if (error)
            *error = QStringLiteral("Industrial camera commands do not accept arguments yet");
        return false;
    }
    if (!pluginForm)
        GetUI();
    if (!pluginForm) {
        if (error)
            *error = QStringLiteral("Industrial camera panel could not be initialized");
        return false;
    }
    ProcessCommand(command);
    if (result)
        result->insert(QStringLiteral("accepted"), true);
    return true;
}

void IndustrialCameraPlugin::ProcessCommand(QString cmd)
{
    if (pluginForm) {
        pluginForm->GetMessageFromOtherModule(cmd);
    }
}

void IndustrialCameraPlugin::TranferEmit(QString msg)
{
//    emit EmitCommand(msg);
}

void IndustrialCameraPlugin::StopCapture()
{
    if (pluginForm)
        pluginForm->StopCapture();
}
