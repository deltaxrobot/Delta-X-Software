#ifndef DELTAXPLUGIN_H
#define DELTAXPLUGIN_H

#include <QObject>
#include <QWidget>
#include <QString>

//! [0]
class DeltaXPlugin : public QObject
{
public:
    virtual ~DeltaXPlugin() = default;
    virtual QWidget* GetUI() = 0;
    virtual QString GetName() = 0;
    virtual QString GetTitle() = 0;

public slots:
    virtual void ProcessCommand(QString cmd) = 0;

signals:
    virtual void EmitCommand(QString cmd) = 0;

};

QT_BEGIN_NAMESPACE

#define DeltaXPlugin_iid "org.imwi.deltaxstudio"

Q_DECLARE_INTERFACE(DeltaXPlugin, DeltaXPlugin_iid)
QT_END_NAMESPACE

//! [0]
#endif
