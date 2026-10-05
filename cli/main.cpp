#include "CliProtocol.h"
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QElapsedTimer>
#include <QFile>
#include <QJsonArray>
#include <QLocalSocket>
#include <QTextStream>
#include <QTimer>
#include <csignal>
#include <cstdio>

namespace {
volatile std::sig_atomic_t interrupted = 0;
void onInterrupt(int) { interrupted = 1; }
void output(const QJsonObject& event, bool json)
{
    QTextStream out(stdout);
    if (json) {
        out << CliProtocol::encode(event);
    } else {
        const QString kind = event.value("event").toString();
        if (kind == "status") {
            for (const auto& value : event.value("projects").toArray()) {
                const auto project = value.toObject();
                out << project.value("project").toString() << '\n';
                for (const auto& item : project.value("workers").toArray()) {
                    const auto worker = item.toObject();
                    out << "  thread" << worker.value("thread").toInt() << "  "
                        << worker.value("state").toString();
                    if (worker.contains("runId")) out << "  run=" << worker.value("runId").toString();
                    out << '\n';
                }
            }
        } else {
            out << kind;
            if (event.contains("runId")) out << " " << event.value("runId").toString();
            if (event.contains("state")) out << " " << event.value("state").toString();
            if (event.contains("success")) out << (event.value("success").toBool() ? " OK" : " FAILED");
            if (event.contains("message")) out << ": " << event.value("message").toString();
            out << '\n';
        }
    }
    out.flush();
}
}

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("delta-x-cli");
    QCommandLineParser parser;
    parser.setApplicationDescription(
        "Run G-code using the open Delta X Software project and its existing device connections.\n"
        "Commands: status | run FILE | stop RUN_ID | connect-robot | reset-fault\n"
        "Run waits for completion. Ctrl+C requests Stop. No automatic replay on connection loss.");
    parser.addHelpOption();
    parser.addPositionalArgument("command", "status, run, stop, connect-robot, or reset-fault");
    parser.addPositionalArgument("argument", "UTF-8 G-code file, or active CLI run ID", "[argument]");
    parser.addOption({"project", "Open project ID (see status)", "id", "project0"});
    parser.addOption({"thread", "Existing G-Script thread index", "index", "0"});
    parser.addOption({"timeout", "Run time limit in seconds; 0 waits indefinitely", "seconds", "0"});
    parser.addOption({"allow-unhomed", "Explicitly accept the GUI's existing Run Anyway Home warning"});
    parser.addOption({"confirm-safe", "Confirm E-stop, guards, robot, conveyor and tool are safe before reset-fault"});
    parser.addOption({"json", "Print newline-delimited JSON events"});
    // QCommandLineParser::process/showHelp may use a Windows message box when
    // launched with redirected handles and no console. Keep this CLI pipeable.
    if (!parser.parse(app.arguments())) {
        output({{"event", "error"}, {"message", parser.errorText()}},
               app.arguments().contains("--json"));
        return 2;
    }
    const bool helpRequested = parser.isSet("help") || parser.isSet("help-all");
    if (helpRequested || parser.positionalArguments().isEmpty()) {
        QTextStream out(stdout);
        out << parser.helpText();
        out.flush();
        return helpRequested ? 0 : 2;
    }
    const bool json = parser.isSet("json");
    const auto error = [json](const QString& message, int code) {
        output({{"event", "error"}, {"message", message}}, json);
        return code;
    };
    const auto args = parser.positionalArguments();
    const QString command = args.first();
    if (((command == "status" || command == "connect-robot" || command == "reset-fault") && args.size() != 1) ||
        ((command == "run" || command == "stop") && args.size() != 2) ||
        (command != "status" && command != "run" && command != "stop" &&
         command != "connect-robot" && command != "reset-fault"))
        return error("Expected: status | run FILE | stop RUN_ID | connect-robot | reset-fault (see --help)", 2);
    bool threadOk = false, timeoutOk = false;
    const int thread = parser.value("thread").toInt(&threadOk);
    const int timeout = parser.value("timeout").toInt(&timeoutOk);
    if (!threadOk || thread < 0 || !timeoutOk || timeout < 0 || timeout > 2147483)
        return error("Invalid thread or timeout", 2);
    QJsonObject request{{"version", 1}, {"command", command}};
    if (command == "run") {
        QFile file(args.at(1));
        if (!file.open(QIODevice::ReadOnly)) return error(file.errorString(), 2);
        if (file.size() > CliProtocol::MaxMessageBytes / 2)
            return error("G-code file exceeds the 2 MiB source limit", 2);
        QByteArray bytes = file.readAll();
        if (bytes.startsWith("\xef\xbb\xbf")) bytes.remove(0, 3);
        const QString source = QString::fromUtf8(bytes);
        if (source.toUtf8() != bytes || source.trimmed().isEmpty())
            return error("Program must be a non-empty UTF-8 text file", 2);
        request.insert("source", source);
        request.insert("project", parser.value("project"));
        request.insert("thread", thread);
        request.insert("allowUnhomed", parser.isSet("allow-unhomed"));
    } else if (command == "stop") {
        request.insert("runId", args.at(1));
    } else if (command == "connect-robot" || command == "reset-fault") {
        request.insert("project", parser.value("project"));
        if (command == "reset-fault")
            request.insert("confirmSafe", parser.isSet("confirm-safe"));
    }
    const QByteArray wire = CliProtocol::encode(request);
    if (wire.size() > CliProtocol::MaxMessageBytes)
        return error("Encoded request is too large", 2);
    QLocalSocket socket;
    socket.connectToServer(CliProtocol::serverName());
    if (!socket.waitForConnected(3000))
        return error("Cannot connect. Open Delta X Software under the same user account first. " + socket.errorString(), 3);
    socket.setReadBufferSize(CliProtocol::MaxMessageBytes + 1);
    QString runId;
    bool finished = false;
    int requestedExit = 0;
    QElapsedTimer elapsed;
    elapsed.start();
    QElapsedTimer stopWait;
    QObject::connect(&socket, &QLocalSocket::readyRead, &app, [&]() {
        if (socket.bytesAvailable() > CliProtocol::MaxMessageBytes) {
            finished = true;
            app.exit(error("Response exceeds protocol limit", 3));
            return;
        }
        while (socket.canReadLine()) {
            QJsonParseError parseError;
            const auto doc = QJsonDocument::fromJson(socket.readLine(), &parseError);
            if (parseError.error != QJsonParseError::NoError || !doc.isObject()) {
                finished = true;
                app.exit(error("Invalid response from Delta X Software", 3));
                return;
            }
            const auto event = doc.object();
            output(event, json);
            const QString type = event.value("event").toString();
            if (type == "accepted") runId = event.value("runId").toString();
            if (type == "finished" || type == "error" || type == "status" ||
                type == "stop-requested" || type == "connection-requested" ||
                type == "fault-reset") {
                finished = true;
                int code = type == "error" ? 2 : 0;
                if (type == "finished" && !event.value("success").toBool()) code = 1;
                app.exit(requestedExit ? requestedExit : code);
                return;
            }
        }
    });
    QObject::connect(&socket, &QLocalSocket::disconnected, &app, [&]() {
        if (!finished) app.exit(error("Connection lost; execution outcome is unknown. Inspect the application before retrying.", 3));
    });
    std::signal(SIGINT, onInterrupt);
    std::signal(SIGTERM, onInterrupt);
    QTimer watchdog;
    watchdog.setInterval(50);
    QObject::connect(&watchdog, &QTimer::timeout, &app, [&]() {
        if (stopWait.isValid()) {
            if (stopWait.elapsed() > 5000) {
                finished = true;
                socket.abort();
                app.exit(error("Stop was requested but completion was not confirmed. Inspect the application.", 3));
            }
            return;
        }
        const bool timedOut = timeout > 0 && elapsed.elapsed() >= qint64(timeout) * 1000;
        if (interrupted || timedOut) {
            requestedExit = interrupted ? 130 : 124;
            if (runId.isEmpty()) {
                finished = true;
                socket.abort();
                app.exit(requestedExit);
                return;
            }
            QLocalSocket stopper;
            stopper.connectToServer(CliProtocol::serverName());
            if (stopper.waitForConnected(1000)) {
                stopper.write(CliProtocol::encode({{"version", 1}, {"command", "stop"}, {"runId", runId}}));
                stopper.waitForBytesWritten(1000);
                stopper.waitForReadyRead(1000);
            }
            stopWait.start();
        } else if (runId.isEmpty() && elapsed.elapsed() > 10000) {
            finished = true;
            socket.abort();
            app.exit(error("Application did not acknowledge the request", 3));
        }
    });
    watchdog.start();
    socket.write(wire);
    return app.exec();
}
