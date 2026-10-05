#pragma once

#include <QObject>
#include <QPointer>
#include <QHash>
#include "CliServer.h"

class ProjectManager;
class GcodeScript;

class GScriptCliBridge : public QObject
{
public:
    explicit GScriptCliBridge(ProjectManager* projects, QObject* parent = nullptr,
                              const QString& serverName = QString());
    ~GScriptCliBridge() override;
private:
    struct Run {
        QPointer<GcodeScript> worker;
        QString project;
        int thread;
    };
    void handle(QLocalSocket* socket, const QJsonObject& request);
    ProjectManager* m_projects;
    QHash<QString, Run> m_runs;
    CliServer m_server;
};
