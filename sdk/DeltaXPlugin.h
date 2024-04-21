#ifndef DELTAXPLUGIN_H
#define DELTAXPLUGIN_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <opencv2/core/core.hpp>
#include <QSettings>

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
//    virtual void EmitCommand(QString cmd) = 0;
    virtual void CapturedImage(cv::Mat mat) = 0;
    virtual void StartedCapture() = 0;
    virtual void RequestCapture() = 0;
    virtual void RequestConnect(int id) = 0;
};

QT_BEGIN_NAMESPACE

#define DeltaXPlugin_iid "org.imwi.deltaxstudio"

Q_DECLARE_INTERFACE(DeltaXPlugin, DeltaXPlugin_iid)
QT_END_NAMESPACE

//! [0]
#endif
