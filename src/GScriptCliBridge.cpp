#include "GScriptCliBridge.h"
#include "CliProtocol.h"
#include "ProjectManager.h"
#include "GcodeScript.h"
#include <QJsonArray>
#include <QMetaEnum>
#include <QUuid>

GScriptCliBridge::GScriptCliBridge(ProjectManager* projects, QObject* parent, const QString& serverName)
    : QObject(parent), m_projects(projects)
{
    connect(&m_server, &CliServer::requestReceived, this, &GScriptCliBridge::handle);
    QString error;
    if (!m_server.listen(serverName.isEmpty() ? CliProtocol::serverName() : serverName, &error))
        qWarning().noquote() << "CLI:" << error;
}

void GScriptCliBridge::handle(QLocalSocket* socket, const QJsonObject& request)
{
    const auto fail = [socket](const QString& message) {
        CliServer::reply(socket, {{"event", "error"}, {"message", message}}, true);
    };
    const QString command = request.value("command").toString();
    if (command == "status") {
        QJsonArray projects;
        for (auto* project : m_projects->RobotWindows) {
            QJsonArray workers;
            for (int i = 0; i < project->GcodeScripts.size(); ++i) {
                auto* worker = project->GcodeScripts.at(i);
                const auto state = QMetaEnum::fromType<GcodeScript::ExecutionState>();
                QJsonObject entry{{"thread", i}, {"state", state.valueToKey(int(worker->State()))}};
                for (auto it = m_runs.cbegin(); it != m_runs.cend(); ++it)
                    if (it->worker == worker) entry.insert("runId", it.key());
                workers.append(entry);
            }
            projects.append(QJsonObject{{"project", project->ProjectName},
                                        {"cellState", project->cellStateName()},
                                        {"cellFaultReason", project->cellFaultReason()},
                                        {"robotConnected", project->robotConnected()},
                                        {"workers", workers}});
        }
        CliServer::reply(socket, {{"event", "status"}, {"projects", projects}}, true);
        return;
    }
    if (command == "stop") {
        const auto run = m_runs.constFind(request.value("runId").toString());
        if (run == m_runs.cend() || !run->worker) {
            fail("No active CLI run has that ID. Use status to list active runs.");
            return;
        }
        QMetaObject::invokeMethod(run->worker, "Stop", Qt::QueuedConnection);
        CliServer::reply(socket, {{"event", "stop-requested"}, {"runId", run.key()}}, true);
        return;
    }
    if (command == "connect-robot" || command == "reset-fault") {
        auto* project = m_projects->GetProject(request.value("project").toString());
        if (!project) {
            fail("Project is not open. Use status to list project IDs.");
            return;
        }
        QString error;
        if (command == "connect-robot") {
            if (!project->requestRobotAutoConnect(&error)) {
                fail(error);
                return;
            }
            CliServer::reply(socket,
                             {{"event", "connection-requested"},
                              {"project", project->ProjectName},
                              {"alreadyConnected", project->robotConnected()}}, true);
            return;
        }
        if (!request.value("confirmSafe").toBool(false)) {
            fail("reset-fault requires --confirm-safe after checking E-stop, guards and the work area");
            return;
        }
        if (!project->resetCellFault(true, &error)) {
            fail(error);
            return;
        }
        CliServer::reply(socket,
                         {{"event", "fault-reset"},
                          {"project", project->ProjectName},
                          {"cellState", project->cellStateName()}}, true);
        return;
    }
    if (command != "run") {
        fail("Unknown command");
        return;
    }
    auto* project = m_projects->GetProject(request.value("project").toString());
    if (!project) {
        fail("Project is not open. Use status to list project IDs.");
        return;
    }
    const auto threadValue = request.value("thread");
    const int thread = threadValue.toInt(-1);
    if (!threadValue.isDouble() || threadValue.toDouble() != thread ||
        thread < 0 || thread >= project->GcodeScripts.size()) {
        fail("G-Script thread does not exist in this project");
        return;
    }
    auto* worker = project->GcodeScripts.at(thread);
    for (const auto& run : m_runs) {
        if (run.worker == worker) {
            fail("G-Script thread is already reserved by a CLI run");
            return;
        }
    }
    const QString source = request.value("source").toString();
    if (source.trimmed().isEmpty()) {
        fail("Program is empty");
        return;
    }
    const QString id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    // Connections are installed before queuing execution so very short programs
    // cannot finish before the client starts listening.
    auto* session = new QObject(socket);
    connect(worker, &GcodeScript::LogMessage, session, [socket](const QString& message) {
        CliServer::reply(socket, {{"event", "log"}, {"message", message}});
    });
    connect(worker, &GcodeScript::ExecutionStateChanged, session,
            [socket](GcodeScript::ExecutionState state, const QString& message) {
        CliServer::reply(socket, {{"event", "state"},
            {"state", QMetaEnum::fromType<GcodeScript::ExecutionState>().valueToKey(int(state))},
            {"message", message}});
    });
    connect(worker, &GcodeScript::ExecutionFinished, session,
            [this, socket, id, session, worker](bool success, const QString& message) {
        m_runs.remove(id);
        disconnect(worker, nullptr, session, nullptr);
        session->deleteLater();
        CliServer::reply(socket, {{"event", "finished"}, {"runId", id},
            {"success", success}, {"message", message}}, true);
    });
    connect(worker, &QObject::destroyed, session, [this, socket, id, session]() {
        m_runs.remove(id);
        CliServer::reply(socket, {{"event", "error"}, {"message", "Project was closed"}}, true);
        session->deleteLater();
    });
    connect(socket, &QLocalSocket::disconnected, session, [this, id, session]() {
        const Run run = m_runs.take(id);
        if (run.worker) {
            disconnect(run.worker, nullptr, session, nullptr);
            QMetaObject::invokeMethod(run.worker, "Stop", Qt::QueuedConnection);
        }
        session->deleteLater();
    });
    QString error;
    if (!project->startGScript(thread, source, &error, false,
                              request.value("allowUnhomed").toBool(false))) {
        delete session;
        fail(error);
        return;
    }
    m_runs.insert(id, {worker, project->ProjectName, thread});
    CliServer::reply(socket, {{"event", "accepted"}, {"runId", id},
        {"project", project->ProjectName}, {"thread", thread}});
}

GScriptCliBridge::~GScriptCliBridge()
{
    for (const auto& run : m_runs)
        if (run.worker) QMetaObject::invokeMethod(run.worker, "Stop", Qt::QueuedConnection);
}
