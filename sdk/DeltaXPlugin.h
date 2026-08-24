#ifndef DELTAXPLUGIN_H
#define DELTAXPLUGIN_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <opencv2/core/core.hpp>
#include <QSettings>
#include "DeltaXPluginMetadata.h"

//! [0]
class DeltaXPlugin : public QObject
{
    Q_OBJECT
public:
    virtual ~DeltaXPlugin() = default;
    virtual QWidget* GetUI() = 0;
    virtual QString GetName() = 0;
    virtual QString GetTitle() = 0;

    virtual void LoadSettings(QSettings* setting) = 0;
    virtual void SaveSettings(QSettings* setting) = 0;

    QString ProjectName = "";

public slots:
    virtual void ProcessCommand(QString cmd) = 0;

signals:
    // ✅ Fixed: Qt signals cannot be virtual - MOC generates these
    void CapturedImage(cv::Mat mat);
    void StartedCapture();
    void RequestCapture();
    void RequestConnect(int id);
    void CaptureError(QString reason);
};

QT_BEGIN_NAMESPACE

#define DeltaXPlugin_iid DELTA_X_PLUGIN_IID

Q_DECLARE_INTERFACE(DeltaXPlugin, DeltaXPlugin_iid)
QT_END_NAMESPACE

//! [0]
#endif
