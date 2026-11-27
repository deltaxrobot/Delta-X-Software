/*
* GScript - new script language for robot automation
*/

#include "GcodeScript.h"
#include "GScriptSyntax.h"
#include <atomic>
#include <QPointer>
#include <QMutexLocker>
#include <QReadLocker>
#include <QWriteLocker>
#include <QMetaEnum>
#include <QMetaMethod>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <limits>

namespace {
class GScriptEvaluationError final : public std::runtime_error
{
public:
    explicit GScriptEvaluationError(const QString& message)
        : std::runtime_error(message.toStdString()) {}
};

double finiteNumber(const QString& value, const QString& context)
{
    bool ok = false;
    const double number = value.trimmed().toDouble(&ok);
    if (!ok || !std::isfinite(number))
        throw GScriptEvaluationError(QString("%1 requires a finite number; received '%2'.")
                                         .arg(context, value));
    return number;
}

int boundedInteger(double value, int minimum, int maximum, const QString& context)
{
    if (!std::isfinite(value) || std::trunc(value) != value || value < minimum || value > maximum)
        throw GScriptEvaluationError(QString("%1 requires an integer from %2 to %3.")
                                         .arg(context).arg(minimum).arg(maximum));
    return static_cast<int>(value);
}

std::atomic<quint64> g_nextVisionRequestId{1};
QMutex g_deviceLeaseMutex;
QHash<QString, QPointer<GcodeScript>> g_deviceLeases;

quint64 nextVisionRequestId()
{
    return g_nextVisionRequestId.fetch_add(1, std::memory_order_relaxed);
}

bool isDeviceFaultResponse(const QString& response)
{
    const QString text = response.trimmed();
    return text.contains(QStringLiteral("error"), Qt::CaseInsensitive) ||
           text.startsWith(QStringLiteral("Unknown:"), Qt::CaseInsensitive) ||
           text.startsWith(QStringLiteral("Delta:EStop"), Qt::CaseInsensitive) ||
           text.compare(QStringLiteral("Delta:Stop"), Qt::CaseInsensitive) == 0 ||
           text.compare(QStringLiteral("Delta:Pause"), Qt::CaseInsensitive) == 0;
}

QString stripInlineComment(const QString& input)
{
    return GScriptSyntax::stripComment(input);
}

template <typename Transform>
QString transformUnquotedText(const QString& input, Transform transform,
                              bool preserveQuoted = true)
{
    QString result;
    int start = 0;
    for (int at = 0; at < input.size(); ++at) {
        const QChar quote = input.at(at);
        if (quote != '\'' && quote != '"')
            continue;
        result += transform(input.mid(start, at - start));
        const int end = input.indexOf(quote, at + 1);
        if (end < 0)
            return result + input.mid(at);
        result += preserveQuoted ? input.mid(at, end - at + 1)
                                 : QString(end - at + 1, QLatin1Char(' '));
        at = end;
        start = end + 1;
    }
    return result + transform(input.mid(start));
}
}
#include "CloudPointMapper.h"
#include "PluginExtensionRegistry.h"
#include "VariableManager.h"
#include "SoftwareManager.h"
#include <QStandardPaths>
#include <QDir>
#include <QDateTime>
#include <QDebug>
#include <QTimer>
#include <QRegularExpression>
#include <QPointF>

// Initialize cloud point mapper member variables
GcodeScript::GcodeScript(QObject* parent)
    : QObject(parent)
    , isRunning(false)
    , m_cloudPointMapper(nullptr)
    , m_cloudPointMapperInitialized(false)
    , returnPointerOrder(-1)
    , IsConveyorSync(false)
{
    qRegisterMetaType<GScriptDiagnostic>("GScriptDiagnostic");
    qRegisterMetaType<QList<GScriptDiagnostic>>("QList<GScriptDiagnostic>");
    qRegisterMetaType<GcodeScript::ExecutionState>("GcodeScript::ExecutionState");

    // Initialize array
    for (int i = 0; i < 20; i++) {
        returnSubProPointer[i] = -1;
    }
    
    // Initialize cloud point mapper
    initializeCloudPointMapper();
}

GcodeScript::~GcodeScript()
{
    releaseDeviceLease(transmitDeviceId);
    if (m_cloudPointMapper) {
        delete m_cloudPointMapper;
    }
}

void GcodeScript::initializeCloudPointMapper()
{
    if (!m_cloudPointMapperInitialized) {
        m_cloudPointMapper = new CloudPointMapper(this);
        m_cloudPointMapperInitialized = true;
        
        // Don't auto-import during initialization to avoid unnecessary error messages
        // User can manually import when needed via UI or GScript commands
        // if (m_cloudPointMapper) {
        //     m_cloudPointMapper->importFromVariableManager("CloudMapping");
        // }
    }
}

CloudPointMapper* GcodeScript::getCloudPointMapper()
{
    if (!m_cloudPointMapperInitialized) {
        initializeCloudPointMapper();
    }
    if (m_cloudPointMapper && m_cloudPointMapperProject != ProjectName) {
        m_cloudPointMapper->clearMapping();
        m_cloudPointMapperProject = ProjectName;
        const QString variableName = VariableManager::scopedKey(ProjectName, QStringLiteral("CloudMapping"));
        if (VariableManager::instance().containsFullKey(variableName + QStringLiteral("_mapping")))
            m_cloudPointMapper->importFromVariableManager(variableName);
    }
    return m_cloudPointMapper;
}

bool GcodeScript::isCloudPointMapperAvailable()
{
    CloudPointMapper* mapper = getCloudPointMapper();
    if (!mapper) {
        return false;
    }
    
    CloudPointMapper::MappingStats stats = mapper->getMappingStats();
    return stats.isValid && mapper->getPointCount() >= 3;
}

void GcodeScript::SetGcodeScript(QString gcode)
{
    QWriteLocker locker(&scriptMetadataLock);
    gcodeScript = gcode;
}

QString GcodeScript::GetGcodeScript()
{
    QReadLocker locker(&scriptMetadataLock);
    return gcodeScript;
}

void GcodeScript::SetProgramPath(QString path)
{
    QWriteLocker locker(&scriptMetadataLock);
    programPath = path;
    QFileInfo fileInfo(programPath);
    programName = fileInfo.fileName();
}

QString GcodeScript::GetProgramPath()
{
    QReadLocker locker(&scriptMetadataLock);
    return programPath;
}

QString GcodeScript::GetProgramName()
{
    QReadLocker locker(&scriptMetadataLock);
    return programName;
}

bool GcodeScript::IsRunning()
{
    return isRunning.load(std::memory_order_acquire);
}

GcodeScript::ExecutionState GcodeScript::State() const
{
    return executionState.load(std::memory_order_acquire);
}

QList<GScriptDiagnostic> GcodeScript::Validate(const QString& source) const
{
    return GScriptAnalyzer::analyze(source).diagnostics;
}

void GcodeScript::ExecuteGcode(QString gcodes, int startMode)
{
    if (isRunning) {
        GScriptDiagnostic diagnostic;
        diagnostic.severity = GScriptDiagnostic::Error;
        diagnostic.code = "GSR1001";
        diagnostic.message = "This program thread is already running.";
        diagnostic.hint = "Stop the active run before starting another program.";
        emit DiagnosticsReady({diagnostic});
        emit LogMessage(diagnostic.message);
        return;
    }

    // QTextEdit normalizes line endings, while files received through the CLI
    // retain Windows CRLF. Normalize once at the runtime boundary so tokens,
    // labels and subprogram names never contain a trailing carriage return.
    gcodes.replace(QStringLiteral("\r\n"), QStringLiteral("\n"));
    gcodes.replace(QLatin1Char('\r'), QLatin1Char('\n'));

    publishExecutionVariable("Failure.Line", 0);
    publishExecutionVariable("Failure.Source", QString());
    publishExecutionVariable("Failure.Device", QString());
    publishExecutionVariable("Failure.Command", QString());
    publishExecutionVariable("Failure.CallStack", QStringList());
    currentGcodeEditorCursor = 0;

    setExecutionState(ExecutionState::Validating, "Validating program");
    const GScriptAnalysisResult analysis = GScriptAnalyzer::analyze(gcodes);
    emit DiagnosticsReady(analysis.diagnostics);
    if (analysis.hasErrors()) {
        QString firstError;
        for (const GScriptDiagnostic& diagnostic : analysis.diagnostics) {
            if (diagnostic.severity == GScriptDiagnostic::Error) {
                firstError = QString("Line %1: %2")
                                 .arg(diagnostic.line)
                                 .arg(diagnostic.message);
                break;
            }
        }
        const QString message = QString("Validation failed: %1 error(s), %2 warning(s).%3")
                                    .arg(analysis.errorCount())
                                    .arg(analysis.warningCount())
                                    .arg(firstError.isEmpty()
                                             ? QString()
                                             : QString(" %1").arg(firstError));
        publishExecutionVariable("Running", false);
        publishExecutionVariable("Succeeded", false);
        publishExecutionVariable("LastError", message);
        publishExecutionVariable("FinishedAt",
                                 QDateTime::currentDateTimeUtc().toString(Qt::ISODateWithMs));
        setExecutionState(ExecutionState::Faulted, message);
        emit LogMessage(message);
        emit ExecutionFinished(false, message);
        emit Finished();
        return;
    }

    SetGcodeScript(gcodes);
    ++executionGeneration;
    isRunning = true;
    SoftwareManager::GetInstance()->ScriptStarted();
    setExecutionState(ExecutionState::Running, "Program running");
    publishExecutionVariable("Running", true);
    publishExecutionVariable("Program", GetProgramName());
    publishExecutionVariable("StartedAt",
                             QDateTime::currentDateTimeUtc().toString(Qt::ISODateWithMs));
    publishExecutionVariable("LastError", QString());
    publishExecutionVariable("Response", QString());
    publishExecutionVariable("ActiveCondition", QString());

    QList<QString> tempGcodeList = gcodes.split('\n');

    gcodeList.clear();
    gcodeNumberList.clear();
    lineNumberCacheValid = false;  // Invalidate cache when gcodeList changes
    response.clear();
    transmitMsg.clear();
    transmitDeviceId.clear();
    waitForHomePosition = false;
    pendingResponseToken++;
    expectedVisionRequestId = 0;
    expectedTrackingRequestId = 0;
    pendingClaimResult.clear();
    requireCorrelatedTrackingResponse = false;
    pendingAreaResult = false;
    pendingResponseVariable.clear();
    pendingConditionExpression.clear();
    pendingConditionMessage.clear();
    pendingConditionTimeoutMs = 0;
    pendingConditionPollMs = 20;
    pendingConditionToken = 0;
    ActiveDevice = DefaultRobot;
    
    // Clear IF block stack when starting new script
    ifBlockStack.clear();
    
    // Clear FOR loop stack when starting new script
    forLoopStack.clear();
    whileLoopStack.clear();
    switchCaseStack.clear();
    breakRequested = false;
    continueRequested = false;
    nextLoopNestingOrder = 0;
    
    // Clear function and label definitions and call stacks when starting new script
    functionDefinitions.clear();
    labelDefinitions.clear();
    callStack.clear();
    functionReturnStack.clear();
    returnPointerOrder = -1;
    std::fill(std::begin(returnSubProPointer), std::end(returnSubProPointer), -1);
    std::fill(std::begin(subprogramFrames), std::end(subprogramFrames), SubprogramFrame{});

    if (startMode == BEGIN)
    {
        gcodeOrder = 0;
    }
    else
    {
        gcodeOrder = currentGcodeEditorCursor;
    }

    for (int i = 0; i < tempGcodeList.size(); i++)
    {
        QString line = tempGcodeList.at(i);

        // Revert to original simple processing
        line = DeleteExcessSpace(line);

        QList<QString> pairs = line.split(' ');
        if (pairs.count() > 1)
        {
            if (pairs[0] != "")
            {
                if (pairs[0].at(0) == 'N')
                {
                    int id = -1;
                    id = pairs[0].mid(1).toInt();

                    gcodeNumberList.append(id);
                }
            }
        }

        gcodeList.push_back(line);
    }

    tempGcodeList.clear();

    // Pre-scan to collect all function definitions before execution
    preprocessGcodeScript();

    TransmitNextGcode();
}

void GcodeScript::GetResponse(QString deviceId, QString response)
{
    if (!isRunning || State() != ExecutionState::WaitingForDevice || deviceId != transmitDeviceId ||
        (requireCorrelatedTrackingResponse && deviceId.startsWith("tracking")))
        return;

    if (deviceId == transmitDeviceId && deviceId.startsWith("vision"))
    {
        const QStringList parts = response.split(':');
        if ((response.startsWith("FrameReady:") || response.startsWith("VisionError:")) &&
            parts.size() >= 2)
        {
            bool ok = false;
            const quint64 responseRequestId = parts.at(1).toULongLong(&ok);
            if (!ok || responseRequestId != expectedVisionRequestId)
                return; // A preview or another script's request may share visionN.

            if (response.startsWith("VisionError:")) {
                const QString message = QString("Vision request %1 failed: %2")
                                            .arg(responseRequestId)
                                            .arg(parts.mid(2).join(':'));
                saveRuntimeVariable("Response", response);
                saveRuntimeVariable("LastError", message);
                emit LogMessage(message);
                expectedVisionRequestId = 0;
                finishExecution(true, message, true);
                return;
            }
        }
        else
        {
            return; // Never unblock a vision wait with an uncorrelated response.
        }
    }

    if (deviceId == transmitDeviceId && response.startsWith("TrackingFault:"))
    {
        saveRuntimeVariable("Response", response);
        const QString message = QString("Tracking health fault: %1 (%2).")
                                    .arg(response, deviceId);
        saveRuntimeVariable("LastError", message);
        emit LogMessage(message);
        finishExecution(true, message, true);
        return;
    }

    if (deviceId == transmitDeviceId &&
        (response == "CompleteRejected" || response == "ReleaseRejected"))
    {
        saveRuntimeVariable("Response", response);
        const QString message = QString("Tracking ownership operation failed: %1 (%2).")
                                    .arg(response, deviceId);
        saveRuntimeVariable("LastError", message);
        emit LogMessage(message);
        finishExecution(true, message, true);
        return;
    }

    if (deviceId == transmitDeviceId && isDeviceFaultResponse(response))
    {
        const QString message = QString("Device %1 rejected '%2': %3")
                                    .arg(deviceId, transmitMsg, response.trimmed());
        faultExecution(message, true);
        return;
    }

    if (checkExclution(response))
        return;

    // Gate progression after homing: wait until Position data is received
    if (waitForHomePosition && deviceId == transmitDeviceId)
    {
        // Heuristic: Position response contains multiple comma-separated values
        if (response.count(',') >= 2)
        {
            // Position received; clear gate and proceed
            waitForHomePosition = false;
        }
        else
        {
            // Ignore intermediate responses while waiting for Position
            return;
        }
    }

    processResponse(response);
    if (deviceId == transmitDeviceId)
    {
        // Invalidate the timeout immediately. The next statement may be local
        // and must not inherit a completed device wait.
        pendingResponseToken++;
        expectedVisionRequestId = 0;
        expectedTrackingRequestId = 0;
        pendingClaimResult.clear();
        requireCorrelatedTrackingResponse = false;
        pendingAreaResult = false;
        this->response = response;
        saveRuntimeVariable("Response", response);
        publishExecutionVariable("Response", response);
        if (!pendingResponseVariable.isEmpty())
            saveVariable(pendingResponseVariable, response);
        pendingResponseVariable.clear();
        releaseDeviceLease(deviceId);
        setExecutionState(ExecutionState::Running, "Device response received");
        TransmitNextGcode();
    }
}

void GcodeScript::GetTrackingResponse(quint64 requestId, QString deviceId,
                                       QString response, QVariantMap result)
{
    if (!isRunning || State() != ExecutionState::WaitingForDevice ||
        !requireCorrelatedTrackingResponse || requestId == 0 ||
        requestId != expectedTrackingRequestId || deviceId != transmitDeviceId)
        return;
    if (!pendingClaimResult.isEmpty()) {
        if (pendingAreaResult) {
            VariableManager::instance().removeVarScoped(ProjectName, pendingClaimResult);
            VariableManager::instance().updateObjectSnapshot(ProjectName, pendingClaimResult,
                result.take("__Objects").value<QVector<ObjectInfo>>());
        }
        QHash<QString, QVariant> values;
        for (auto field = result.cbegin(); field != result.cend(); ++field)
            values.insert(pendingClaimResult + '.' + field.key(), field.value());
        VariableManager::instance().updateBatchScoped(ProjectName, values,
                                                       VariableManager::Persistence::Runtime);
    }
    expectedTrackingRequestId = 0;
    pendingClaimResult.clear();
    requireCorrelatedTrackingResponse = false;
    pendingAreaResult = false;
    GetResponse(deviceId, response);
}

void GcodeScript::SendMsgToDevice(QString deviceId, QString msg)
{
    beginDeviceRequest(deviceId, msg, 120000);
}

void GcodeScript::TransmitNextGcode()
{
    if (!isRunning)
        return;

    const ExecutionState currentState = executionState.load(std::memory_order_acquire);
    if (currentState == ExecutionState::WaitingForDevice ||
        currentState == ExecutionState::WaitingForTimer)
        setExecutionState(ExecutionState::Running, "Program running");

    if (gcodeOrder >= gcodeList.size())
    {
        finishExecution(false);

        return;
    }

    QElapsedTimer batchTimer;
    batchTimer.start();
    int statementsExecuted = 0;
    while (true)
    {
        currentLine = gcodeList.at(gcodeOrder);
        publishExecutionVariable("CurrentLine", gcodeOrder + 1);
        publishExecutionVariable("CurrentSource", currentLine);
        bool isGcode = true;

        if (currentLine == "")
        {
            isGcode = false;
            gcodeOrder += 1;
        }
        else
        {
            currentLine = GScriptSyntax::withoutLineNumber(currentLine);
            isGcode = findExeGcodeAndTransmit();
        }

        // The last instruction may still be awaiting its asynchronous result.
        // Only its completion callback may finish the program in that case.
        const ExecutionState state = executionState.load(std::memory_order_acquire);
        if (!isRunning || state == ExecutionState::WaitingForDevice ||
            state == ExecutionState::WaitingForTimer ||
            state == ExecutionState::WaitingForCondition)
            break;

        if (gcodeOrder >= gcodeList.size())
        {
            finishExecution(false);

            break;
        }

        if (isGcode == true)
        {
            break;
        }

        // Local loops must let queued Stop requests and telemetry reach this
        // worker. A continuation belongs to this run, never a later restart.
        if (++statementsExecuted >= 64 || batchTimer.elapsed() >= 5) {
            const quint64 generation = executionGeneration;
            QTimer::singleShot(0, this, [this, generation]() {
                if (isRunning && executionGeneration == generation &&
                    State() == ExecutionState::Running)
                    TransmitNextGcode();
            });
            break;
        }
    }
}

void GcodeScript::ExecuteFunction(QString functionName, QStringList paras)
{
    // Ensure functions are pre-scanned
    if (functionDefinitions.isEmpty())
    {
        preprocessGcodeScript();
    }

    // Normalize function name for lookup
    QString normalizedName = functionName;
    if (normalizedName.startsWith("#"))
        normalizedName = normalizedName.mid(1);
    normalizedName = normalizedName.toUpper();

    // If function not found, try to pre-scan again (in case script changed)
    if (!functionDefinitions.contains(normalizedName))
    {
        preprocessGcodeScript();
    }

    // Call function if exists
    if (functionDefinitions.contains(normalizedName))
    {
        callFunction(normalizedName, paras);
    }
}

void GcodeScript::Stop()
{
    if (!isRunning) {
        setExecutionState(ExecutionState::Idle, "Ready");
        return;
    }
    setExecutionState(ExecutionState::Stopping, "Stopping program");
    finishExecution(true, "GScript execution stopped.");
}

void GcodeScript::setExecutionState(ExecutionState state, const QString& message)
{
    executionState.store(state, std::memory_order_release);
    const QMetaEnum stateMeta = QMetaEnum::fromType<ExecutionState>();
    publishExecutionVariable("State", QString::fromLatin1(stateMeta.valueToKey(static_cast<int>(state))));
    publishExecutionVariable("StateMessage", message);
    emit ExecutionStateChanged(state, message);
}

void GcodeScript::finishExecution(bool abortActiveMotion, const QString& detail,
                                  bool faulted)
{
    if (!isRunning)
        return;

    const QString activeDeviceId = transmitDeviceId;
    const QString activeMsg = transmitMsg;
    QString reason = detail;
    if (faulted) {
        const int sourceLine = currentGcodeEditorCursor + 1;
        const QString source = sourceLine > 0 && sourceLine <= gcodeList.size()
            ? gcodeList.at(sourceLine - 1) : currentLine;
        QStringList context;
        for (const CallFrame& frame : callStack)
            context.append(QString("%1 (called at line %2)")
                               .arg(frame.functionName).arg(frame.callLine));
        for (int at = 0; at <= returnPointerOrder; ++at) {
            const int callAt = returnSubProPointer[at];
            if (callAt >= 0 && callAt < gcodeList.size())
                context.append(QString("%1 (line %2)").arg(gcodeList.at(callAt)).arg(callAt + 1));
        }
        publishExecutionVariable("Failure.Line", sourceLine);
        publishExecutionVariable("Failure.Source", source);
        publishExecutionVariable("Failure.Device", activeDeviceId);
        publishExecutionVariable("Failure.Command", activeMsg);
        publishExecutionVariable("Failure.CallStack", context);
        reason = QString("Line %1: %2").arg(sourceLine).arg(detail);
        if (!activeDeviceId.isEmpty())
            reason += QString(" Device: %1; command: %2.").arg(activeDeviceId, activeMsg);
        if (!context.isEmpty())
            reason += QString(" Call stack: %1.").arg(context.join(" -> "));
        publishExecutionVariable("LastError", reason);
        saveRuntimeVariable("LastError", reason);
        GScriptDiagnostic diagnostic;
        diagnostic.severity = GScriptDiagnostic::Error;
        diagnostic.code = QStringLiteral("GSR1002");
        diagnostic.line = sourceLine;
        diagnostic.message = reason;
        emit DiagnosticsReady({diagnostic});
    }

    isRunning = false;
    ++executionGeneration;
    pendingResponseToken++;
    pendingConditionToken = 0;
    pendingConditionExpression.clear();
    pendingConditionMessage.clear();
    expectedVisionRequestId = 0;
    expectedTrackingRequestId = 0;
    pendingClaimResult.clear();
    requireCorrelatedTrackingResponse = false;
    pendingAreaResult = false;
    waitForHomePosition = false;
    response.clear();
    transmitMsg.clear();
    transmitDeviceId.clear();

    if (abortActiveMotion && !activeDeviceId.isEmpty())
        requestActiveDeviceStop(activeDeviceId, activeMsg);
    releaseDeviceLease(activeDeviceId);

    SoftwareManager::GetInstance()->ScriptFinished();

    gcodeList.clear();
    gcodeNumberList.clear();
    gcodeOrder = 0;
    currentLine.clear();
    lineNumberCacheValid = false;

    ifBlockStack.clear();
    forLoopStack.clear();
    whileLoopStack.clear();
    switchCaseStack.clear();
    breakRequested = false;
    continueRequested = false;

    functionDefinitions.clear();
    labelDefinitions.clear();
    callStack.clear();
    functionReturnStack.clear();
    returnPointerOrder = -1;
    std::fill(std::begin(returnSubProPointer), std::end(returnSubProPointer), -1);
    std::fill(std::begin(subprogramFrames), std::end(subprogramFrames), SubprogramFrame{});

    if (!reason.isEmpty())
        emit LogMessage(reason);

    const bool userStopped = reason == QStringLiteral("GScript execution stopped.");
    const bool success = !faulted && !userStopped;
    publishExecutionVariable("Running", false);
    publishExecutionVariable("Succeeded", success);
    publishExecutionVariable("ActiveCondition", QString());
    publishExecutionVariable("FinishedAt",
                             QDateTime::currentDateTimeUtc().toString(Qt::ISODateWithMs));
    if (faulted)
        setExecutionState(ExecutionState::Faulted, reason);
    else if (userStopped)
        setExecutionState(ExecutionState::Idle, reason);
    else
        setExecutionState(ExecutionState::Completed,
                          reason.isEmpty() ? QStringLiteral("Program completed") : reason);

    emit ExecutionFinished(success, reason);
    emit Finished();
}

void GcodeScript::requestActiveDeviceStop(const QString& deviceId, const QString& msg)
{
    const QString normalizedDeviceId = deviceId.trimmed();
    const QString normalizedMsg = msg.trimmed().toUpper();

    if (QRegularExpression("^robot\\d+$", QRegularExpression::CaseInsensitiveOption).match(normalizedDeviceId).hasMatch())
    {
        emit SendGcodeToDevice(normalizedDeviceId, "M84");
        return;
    }

    if (QRegularExpression("^slider\\d+$", QRegularExpression::CaseInsensitiveOption).match(normalizedDeviceId).hasMatch())
    {
        emit SendGcodeToDevice(normalizedDeviceId, "M323");
        return;
    }

    if (QRegularExpression("^conveyor\\d+$", QRegularExpression::CaseInsensitiveOption).match(normalizedDeviceId).hasMatch())
    {
        const QRegularExpression channelRegex("C(\\d+)");
        const QRegularExpressionMatch channelMatch = channelRegex.match(normalizedMsg);
        const QString channel = channelMatch.hasMatch() ? channelMatch.captured(1) : QString();

        if (normalizedMsg.startsWith("M402") && !channel.isEmpty())
        {
            emit SendGcodeToDevice(normalizedDeviceId, QString("M402 C%1:0").arg(channel));
            return;
        }

        if (normalizedMsg.startsWith("M401") && !channel.isEmpty())
        {
            emit SendGcodeToDevice(normalizedDeviceId, QString("M401 C%1:0").arg(channel));
            return;
        }

        if (normalizedMsg.startsWith("M313"))
        {
            emit SendGcodeToDevice(normalizedDeviceId, "M313 0");
            return;
        }

        emit SendGcodeToDevice(normalizedDeviceId, "M311 0");
    }
}

void GcodeScript::startPendingResponseTimeout(const QString& deviceId, const QString& msg, int timeoutMs)
{
    setExecutionState(ExecutionState::WaitingForDevice,
                      QString("Waiting for %1").arg(deviceId));
    const quint64 expectedToken = pendingResponseToken;
    QTimer::singleShot(timeoutMs, this, [this, deviceId, msg, expectedToken]() {
        if (!isRunning)
            return;

        if (pendingResponseToken != expectedToken)
            return;

        if (transmitDeviceId != deviceId || transmitMsg != msg)
            return;

        const QString timeoutMessage =
            QString("GScript timed out waiting for %1 to respond to '%2'.").arg(deviceId, msg);

        response = "Timeout";
        saveRuntimeVariable("Response", response);
        saveRuntimeVariable("LastError", timeoutMessage);
        publishExecutionVariable("Response", response);
        publishExecutionVariable("LastError", timeoutMessage);
        emit LogMessage(timeoutMessage);
        finishExecution(true, "GScript execution stopped after a device response timeout.", true);
    });
}

bool GcodeScript::beginDeviceRequest(const QString& deviceId, const QString& msg,
                                     int timeoutMs, const QString& responseVariable)
{
    const QString normalizedDevice = deviceId.trimmed().toLower();
    const QString normalizedMessage = msg.trimmed();
    static const QRegularExpression devicePattern(
        QStringLiteral("^(robot|conveyor|encoder|slider|device)\\d+$"),
        QRegularExpression::CaseInsensitiveOption);

    const bool pluginDevice =
        PluginExtensionRegistry::instance().hasDevice(normalizedDevice);
    if ((!devicePattern.match(normalizedDevice).hasMatch() && !pluginDevice) ||
        normalizedMessage.isEmpty()) {
        faultExecution(QString("Invalid device request: device='%1', command='%2'.")
                           .arg(deviceId, msg));
        return false;
    }

    QString busyOwnerId;
    {
        QMutexLocker locker(&g_deviceLeaseMutex);
        const QPointer<GcodeScript> owner = g_deviceLeases.value(normalizedDevice);
        if (owner && owner != this)
            busyOwnerId = owner->ID;
        else
            g_deviceLeases.insert(normalizedDevice, this);
    }
    if (!busyOwnerId.isEmpty()) {
        faultExecution(QString("Device %1 is busy in G-Script %2.")
                           .arg(normalizedDevice, busyOwnerId));
        return false;
    }

    transmitDeviceId = normalizedDevice;
    transmitMsg = normalizedMessage;
    pendingResponseVariable = cleanedVarName(responseVariable);
    pendingResponseToken++;
    publishExecutionVariable("ActiveDevice", transmitDeviceId);
    publishExecutionVariable("ActiveCommand", transmitMsg);
    setExecutionState(ExecutionState::WaitingForDevice,
                      QString("Waiting for %1").arg(transmitDeviceId));
    startPendingResponseTimeout(transmitDeviceId, transmitMsg,
                                qBound(10, timeoutMs, 86400000));
    emit SendGcodeToDevice(transmitDeviceId, transmitMsg);
    return true;
}

void GcodeScript::releaseDeviceLease(const QString& deviceId)
{
    const QString normalizedDevice = deviceId.trimmed().toLower();
    if (normalizedDevice.isEmpty())
        return;
    QMutexLocker locker(&g_deviceLeaseMutex);
    if (g_deviceLeases.value(normalizedDevice) == this)
        g_deviceLeases.remove(normalizedDevice);
}

bool GcodeScript::isExplicitDeviceToken(const QString& token) const
{
    static const QRegularExpression devicePattern(
        QStringLiteral("^(robot|conveyor|encoder|slider|device)\\d+$"),
        QRegularExpression::CaseInsensitiveOption);
    return devicePattern.match(token.trimmed()).hasMatch() ||
           PluginExtensionRegistry::instance().hasDevice(token.trimmed());
}

void GcodeScript::publishExecutionVariable(const QString& name, const QVariant& value)
{
    VariableManager::instance().updateVarScoped(
        ProjectName, QString("GScript.%1.%2").arg(ID, name), value,
        VariableManager::Persistence::Runtime);
}

void GcodeScript::faultExecution(const QString& message, bool abortActiveMotion)
{
    saveRuntimeVariable("LastError", message);
    publishExecutionVariable("LastError", message);
    finishExecution(abortActiveMotion, message, true);
}

void GcodeScript::pollPendingCondition()
{
    if (!isRunning || pendingConditionToken == 0 ||
        pendingConditionToken != pendingResponseToken)
        return;

    double value;
    try {
        value = finiteNumber(calculateExpressions(pendingConditionExpression), "waitUntil condition");
    } catch (const GScriptEvaluationError& error) {
        faultExecution(QString::fromUtf8(error.what()));
        return;
    }
    if (value != 0.0) {
        pendingConditionToken = 0;
        pendingConditionExpression.clear();
        pendingConditionMessage.clear();
        publishExecutionVariable("ActiveCondition", QString());
        setExecutionState(ExecutionState::Running, QStringLiteral("Program running"));
        TransmitNextGcode();
        return;
    }

    if (pendingConditionTimer.isValid() &&
        pendingConditionTimer.elapsed() >= pendingConditionTimeoutMs) {
        const QString message = pendingConditionMessage.isEmpty()
            ? QString("Condition timed out after %1 ms: %2")
                  .arg(pendingConditionTimeoutMs)
                  .arg(pendingConditionExpression)
            : pendingConditionMessage;
        pendingConditionToken = 0;
        publishExecutionVariable("ActiveCondition", QString());
        faultExecution(message);
        return;
    }

    const quint64 expectedToken = pendingConditionToken;
    QTimer::singleShot(pendingConditionPollMs, this, [this, expectedToken]() {
        if (pendingConditionToken != expectedToken)
            return;
        pollPendingCondition();
    });
}

void GcodeScript::ReceivedGcode(QString gcode)
{
    ExecuteGcode(gcode, BEGIN);
}

void GcodeScript::prepareCurrentLine()
{
    // Normalize syntax only: quoted commands, messages and identifiers are data.
    const QString source = currentLine;
    currentLine = transformUnquotedText(source, [this](QString fragment) {
        currentLine = fragment.replace('\t', ' ');
        // A quoted RHS starts a separate fragment, including compact #Name="...".
        currentLine.replace(QRegularExpression("(#[A-Za-z0-9_][A-Za-z0-9_.]*)\\s*=(?!=)\\s*"),
                            QStringLiteral("\\1 = "));
        normalizeOperators();
        return formatSpaces(currentLine);
    });
}

bool GcodeScript::shouldSkipLine()
{
    currentLine = stripInlineComment(currentLine).trimmed();
    if (currentLine.isEmpty()) {
        gcodeOrder++;
        return true;
    }
    return false;
}

void GcodeScript::collapseGcodeLine()
{
    // An inline branch evaluates its condition first; its selected statement
    // will enter this dispatcher separately with its original brackets intact.
    if (!GScriptSyntax::inlineStatement(currentLine).isEmpty())
        return;
    // Canonical primitives evaluate their own arguments; waitUntil also retains
    // its unevaluated condition for subsequent polls and boolean short-circuiting.
    const auto macro = GScriptSyntax::parseMacroCall(currentLine);
    if (macro.valid && (GScriptSyntax::findPrimitive(macro.target) ||
                       PluginExtensionRegistry::instance().hasGScriptPrimitive(macro.target)))
        return;

    const QString command = GScriptSyntax::command(currentLine);
    const bool devicePayload = isExplicitDeviceToken(command) ||
        QRegularExpression("^[GM]\\d+$").match(command).hasMatch();

    QChar quote;
    for (int at = 0; at < currentLine.size(); ++at) {
        const QChar ch = currentLine.at(at);
        if (!quote.isNull()) {
            if (ch == quote)
                quote = QChar();
            continue;
        }
        if (ch == '\'' || ch == '"') {
            quote = ch;
            continue;
        }
        if (ch != '[')
            continue;
        const int openBracIndex = at;
        int closeBracIndex = findClosingBracket(openBracIndex);
        if (closeBracIndex < 0) {
            faultExecution("Unclosed bracket in runtime expression.");
            return;
        }
        QString expressInBracket = currentLine.mid(openBracIndex, closeBracIndex - openBracIndex + 1);
        const QString resultInBracket = calculateExpressions(expressInBracket);
        if (devicePayload)
            finiteNumber(resultInBracket, "G-code bracket expression");
        currentLine.replace(openBracIndex, expressInBracket.size(), resultInBracket);
        at += resultInBracket.size() - 1;
    }
}

int GcodeScript::findClosingBracket(int openIndex)
{
    int subBracNum = 1;
    QChar quote;
    for (int i = openIndex + 1; i < currentLine.length(); i++) {
        const QChar ch = currentLine.at(i);
        if (!quote.isNull()) {
            if (ch == quote)
                quote = QChar();
            continue;
        }
        if (ch == '\'' || ch == '"') {
            quote = ch;
            continue;
        }
        if (currentLine.at(i) == '[') subBracNum++;
        if (currentLine.at(i) == ']') {
            subBracNum--;
            if (subBracNum == 0) return i;
        }
    }
    return -1; // or throw an exception if unmatched bracket is an error
}

void GcodeScript::normalizeOperators()
{
    // Handle variable assignments first
    // Find variable assignments starting with # and containing =
    if (currentLine.contains('#') && currentLine.contains('=')) {
        // Use simple string replacement for variable assignments
        QRegularExpression varAssignRegex("(#[a-zA-Z_][a-zA-Z0-9_.]*)=([^\\s].*)");
        currentLine.replace(varAssignRegex, "\\1 = \\2");
    }
    
    // Comprehensive normalization of all operators in the entire line
    // Handle ALL cases of missing spaces around operators
    
    // 1. Handle comparison operators first (longer operators first to avoid conflicts)
    currentLine.replace(QRegularExpression("([^\\s])<=([^\\s])"), "\\1 <= \\2");  // both missing
    currentLine.replace(QRegularExpression("([^\\s])<=\\s"), "\\1 <= ");          // missing before
    currentLine.replace(QRegularExpression("\\s<=([^\\s])"), " <= \\1");          // missing after
    
    currentLine.replace(QRegularExpression("([^\\s])>=([^\\s])"), "\\1 >= \\2");
    currentLine.replace(QRegularExpression("([^\\s])>=\\s"), "\\1 >= ");
    currentLine.replace(QRegularExpression("\\s>=([^\\s])"), " >= \\1");
    
    currentLine.replace(QRegularExpression("([^\\s])!=([^\\s])"), "\\1 != \\2");
    currentLine.replace(QRegularExpression("([^\\s])!=\\s"), "\\1 != ");
    currentLine.replace(QRegularExpression("\\s!=([^\\s])"), " != \\1");
    
    currentLine.replace(QRegularExpression("([^\\s])==([^\\s])"), "\\1 == \\2");
    currentLine.replace(QRegularExpression("([^\\s])==\\s"), "\\1 == ");
    currentLine.replace(QRegularExpression("\\s==([^\\s])"), " == \\1");
    
    // 2. Handle arithmetic operators
    currentLine.replace(QRegularExpression("([^\\s])\\*([^\\s])"), "\\1 * \\2");
    currentLine.replace(QRegularExpression("([^\\s])\\*\\s"), "\\1 * ");
    currentLine.replace(QRegularExpression("\\s\\*([^\\s])"), " * \\1");
    
    currentLine.replace(QRegularExpression("([^\\s])/([^\\s])"), "\\1 / \\2");
    currentLine.replace(QRegularExpression("([^\\s])/\\s"), "\\1 / ");
    currentLine.replace(QRegularExpression("\\s/([^\\s])"), " / \\1");
    
    currentLine.replace(QRegularExpression("([^\\s])%([^\\s])"), "\\1 % \\2");
    currentLine.replace(QRegularExpression("([^\\s])%\\s"), "\\1 % ");
    currentLine.replace(QRegularExpression("\\s%([^\\s])"), " % \\1");
    
    currentLine.replace(QRegularExpression("([^\\s])\\+([^\\s])"), "\\1 + \\2");
    currentLine.replace(QRegularExpression("([^\\s])\\+\\s"), "\\1 + ");
    currentLine.replace(QRegularExpression("\\s\\+([^\\s])"), " + \\1");
    
    // 3. Handle subtraction carefully - avoid breaking negative numbers and G-code coordinates
    // Only add spaces if it's clearly a subtraction operation (not a negative number or G-code coordinate)
    // Don't add spaces for G-code coordinates like X-10, Y-20, Z-430, etc.
    // Use negative lookahead to avoid matching single letter followed by minus and digit
    currentLine.replace(QRegularExpression("(?<![A-Z])([a-zA-Z0-9_\\.\\]])\\-(?![0-9])([a-zA-Z0-9_\\.\\#])"), "\\1 - \\2");
    currentLine.replace(QRegularExpression("(?<![A-Z])([a-zA-Z0-9_\\.\\]])\\-\\s"), "\\1 - ");
    currentLine.replace(QRegularExpression("\\s\\-(?![0-9])([a-zA-Z0-9_\\.\\#])"), " - \\1");
    
    // 4. Handle single < and > (after handling <= and >=)
    currentLine.replace(QRegularExpression("([^\\s<])(<)([^\\s=])"), "\\1 \\2 \\3");
    currentLine.replace(QRegularExpression("([^\\s<])(<)\\s"), "\\1 \\2 ");
    currentLine.replace(QRegularExpression("\\s(<)([^\\s=])"), " \\1 \\2");
    
    currentLine.replace(QRegularExpression("([^\\s>])(>)([^\\s=])"), "\\1 \\2 \\3");
    currentLine.replace(QRegularExpression("([^\\s>])(>)\\s"), "\\1 \\2 ");
    currentLine.replace(QRegularExpression("\\s(>)([^\\s=])"), " \\1 \\2");
    
    // Clean up multiple spaces that might be created
    while (currentLine.contains("  ")) {
        currentLine.replace("  ", " ");
    }
}

void GcodeScript::normalizeExpressionOperators(QString& expression)
{
    // This method normalizes operators specifically for expressions in brackets [...]
    // It handles ALL cases of missing spaces around operators comprehensively
    
    // Remove the brackets first to work with the content
    if (expression.startsWith('[') && expression.endsWith(']')) {
        expression = expression.mid(1, expression.length() - 2);
    }
    
    // Comprehensive normalization of all operators
    // Handle each operator type to ensure spaces before AND after
    
    // 1. Handle comparison operators first (longer operators first to avoid conflicts)
    expression.replace(QRegularExpression("([^\\s])<=([^\\s])"), "\\1 <= \\2");  // both missing
    expression.replace(QRegularExpression("([^\\s])<=\\s"), "\\1 <= ");          // missing before
    expression.replace(QRegularExpression("\\s<=([^\\s])"), " <= \\1");          // missing after
    
    expression.replace(QRegularExpression("([^\\s])>=([^\\s])"), "\\1 >= \\2");
    expression.replace(QRegularExpression("([^\\s])>=\\s"), "\\1 >= ");
    expression.replace(QRegularExpression("\\s>=([^\\s])"), " >= \\1");
    
    expression.replace(QRegularExpression("([^\\s])!=([^\\s])"), "\\1 != \\2");
    expression.replace(QRegularExpression("([^\\s])!=\\s"), "\\1 != ");
    expression.replace(QRegularExpression("\\s!=([^\\s])"), " != \\1");
    
    expression.replace(QRegularExpression("([^\\s=])=([^\\s=])"), "\\1 = \\2");
    expression.replace(QRegularExpression("([^\\s=])=\\s"), "\\1 = ");
    expression.replace(QRegularExpression("\\s=([^\\s=])"), " = \\1");
    
    expression.replace(QRegularExpression("([^\\s])\\*([^\\s])"), "\\1 * \\2");
    expression.replace(QRegularExpression("([^\\s])\\*\\s"), "\\1 * ");
    expression.replace(QRegularExpression("\\s\\*([^\\s])"), " * \\1");
    
    expression.replace(QRegularExpression("([^\\s])/([^\\s])"), "\\1 / \\2");
    expression.replace(QRegularExpression("([^\\s])/\\s"), "\\1 / ");
    expression.replace(QRegularExpression("\\s/([^\\s])"), " / \\1");
    
    expression.replace(QRegularExpression("([^\\s])%([^\\s])"), "\\1 % \\2");
    expression.replace(QRegularExpression("([^\\s])%\\s"), "\\1 % ");
    expression.replace(QRegularExpression("\\s%([^\\s])"), " % \\1");
    
    expression.replace(QRegularExpression("([^\\s])\\+([^\\s])"), "\\1 + \\2");
    expression.replace(QRegularExpression("([^\\s])\\+\\s"), "\\1 + ");
    expression.replace(QRegularExpression("\\s\\+([^\\s])"), " + \\1");
    
    // 2. Handle subtraction carefully - avoid breaking negative numbers and G-code coordinates
    // Only add spaces if it's clearly a subtraction operation (not a negative number or G-code coordinate)
    // Use negative lookahead to avoid matching single letter followed by minus and digit
    expression.replace(QRegularExpression("(?<![A-Z])([a-zA-Z0-9_\\.\\]])\\-(?![0-9])([a-zA-Z0-9_\\.\\#])"), "\\1 - \\2");
    expression.replace(QRegularExpression("(?<![A-Z])([a-zA-Z0-9_\\.\\]])\\-\\s"), "\\1 - ");
    expression.replace(QRegularExpression("\\s\\-(?![0-9])([a-zA-Z0-9_\\.\\#])"), " - \\1");
    
    // 3. Handle single < and > (after handling <= and >=)
    expression.replace(QRegularExpression("([^\\s<])(<)([^\\s=])"), "\\1 \\2 \\3");
    expression.replace(QRegularExpression("([^\\s<])(<)\\s"), "\\1 \\2 ");
    expression.replace(QRegularExpression("\\s(<)([^\\s=])"), " \\1 \\2");
    
    expression.replace(QRegularExpression("([^\\s>])(>)([^\\s=])"), "\\1 \\2 \\3");
    expression.replace(QRegularExpression("([^\\s>])(>)\\s"), "\\1 \\2 ");
    expression.replace(QRegularExpression("\\s(>)([^\\s=])"), " \\1 \\2");
    
    // Clean up multiple spaces that might be created
    while (expression.contains("  ")) {
        expression.replace("  ", " ");
    }
    
    // Put the brackets back
    expression = "[" + expression + "]";
}

float GcodeScript::GetResultOfMathFunction(QString expression)
{
    if (expression.isEmpty())
        return NULL_NUMBER;

    if (expression.isEmpty() || expression.at(0) != '#')
        return NULL_NUMBER;

    int p1 = expression.indexOf('(');
    int p2 = expression.lastIndexOf(')');

    if (p1 == -1 && p2 == -1)
        return NULL_NUMBER;

    QString functionName = expression.mid(1, p1 - 1);
    QString value = expression.mid(p1 + 1,  p2 - p1 - 1);
    QString cleanValue = value.replace(" ", "");  // Create a normalized copy for parsing.
    QStringList values = cleanValue.split(',');

    // Handle a function with zero or one argument and no comma.
    if (value.indexOf(',') == -1 && !value.isEmpty())
    {
        values.clear();
        values.append(cleanValue);
    }

    values.append("0");
    values.append("0");

    for (int i = 0; i < values.size(); i++)
    {
        if (!values.at(i).isEmpty())
        {
            if (!values.at(i).isEmpty() && values.at(i).at(0) == '#')
            {
                QString val = getValueAsString(values.at(i));
                values.replace(i, val);
            }
        }
    }

    // Built-in math functions
    if (functionName.toLower() == "sin")
    {
        return sin((values[0].toFloat()/180) * M_PI);
    }

    if (functionName.toLower() == "cos")
    {
        return cos((values[0].toFloat()/180) * M_PI);
    }

    if (functionName.toLower() == "tan")
    {
        return tan((values[0].toFloat()/180) * M_PI);
    }

    if (functionName.toLower() == "atan")
    {
        return atan(values[0].toFloat()) * 180 / M_PI;
    }

    if (functionName.toLower() == "atan2")
    {
        return atan2(values[0].toFloat(), values.at(1).toFloat()) * 180 / M_PI;
    }

    if (functionName.toLower() == "sqrt")
    {
        return sqrt(values[0].toFloat());
    }

    if (functionName.toLower() == "abs")
    {
        return fabs(values[0].toFloat());
    }

    if (functionName.toLower() == "round")
    {
        return round(values[0].toFloat());
    }

    if (functionName.toLower() == "floor")
    {
        return floor(values[0].toFloat());
    }

    if (functionName.toLower() == "ceil")
    {
        return ceil(values[0].toFloat());
    }

    if (functionName.toLower() == "min")
    {
        return qMin(values[0].toFloat(), values[1].toFloat());
    }

    if (functionName.toLower() == "max")
    {
        return qMax(values[0].toFloat(), values[1].toFloat());
    }

    if (functionName.toLower() == "pow")
    {
        return pow(values[0].toFloat(), values[1].toFloat());
    }

    if (functionName.toLower() == "log")
    {
        return log(values[0].toFloat());
    }

    if (functionName.toLower() == "log10")
    {
        return log10(values[0].toFloat());
    }

    if (functionName.toLower() == "exp")
    {
        return exp(values[0].toFloat());
    }

    // ======== CLOUD POINT MAPPING FUNCTIONS ========

    // Add calibration point: #cloudPointAddCalibration(imageX, imageY, imageZ, realX, realY, realZ, confidence, label)
    if (functionName.toLower() == "cloudpointaddcalibration")
    {
        return cloudPointAddCalibration(
            values[0].toFloat(),  // imageX
            values[1].toFloat(),  // imageY  
            values[2].toFloat(),  // imageZ
            values[3].toFloat(),  // realX
            values[4].toFloat(),  // realY
            values[5].toFloat(),  // realZ
            values.size() > 6 ? values[6].toFloat() : 1.0f,  // confidence
            values.size() > 7 ? values[7] : ""  // label
        );
    }

    // Transform functions: #cloudPointTransformX(imageX, imageY, imageZ, method)
    if (functionName.toLower() == "cloudpointtransformx")
    {
        return cloudPointTransformX(
            values[0].toFloat(),  // imageX
            values[1].toFloat(),  // imageY
            values[2].toFloat(),  // imageZ
            values.size() > 3 ? values[3].toInt() : 1  // method
        );
    }

    if (functionName.toLower() == "cloudpointtransformy")
    {
        return cloudPointTransformY(
            values[0].toFloat(),  // imageX
            values[1].toFloat(),  // imageY
            values[2].toFloat(),  // imageZ
            values.size() > 3 ? values[3].toInt() : 1  // method
        );
    }

    if (functionName.toLower() == "cloudpointtransformz")
    {
        return cloudPointTransformZ(
            values[0].toFloat(),  // imageX
            values[1].toFloat(),  // imageY
            values[2].toFloat(),  // imageZ
            values.size() > 3 ? values[3].toInt() : 1  // method
        );
    }

    // Confidence and error functions
    if (functionName.toLower() == "cloudpointgetconfidence")
    {
        return cloudPointGetConfidence(
            values[0].toFloat(),  // imageX
            values[1].toFloat(),  // imageY
            values[2].toFloat(),  // imageZ
            values.size() > 3 ? values[3].toInt() : 1  // method
        );
    }

    if (functionName.toLower() == "cloudpointgeterror")
    {
        return cloudPointGetError(
            values[0].toFloat(),  // imageX
            values[1].toFloat(),  // imageY
            values[2].toFloat(),  // imageZ
            values.size() > 3 ? values[3].toInt() : 1  // method
        );
    }

    // Mapping information functions
    if (functionName.toLower() == "cloudpointgetcount")
    {
        return cloudPointGetCount();
    }

    if (functionName.toLower() == "cloudpointisvalid")
    {
        return cloudPointIsValid();
    }

    if (functionName.toLower() == "cloudpointclear")
    {
        return cloudPointClear();
    }

    if (functionName.toLower() == "cloudpointbuildgrid")
    {
        return cloudPointBuildGrid(
            values.size() > 0 ? values[0].toFloat() : 10.0f  // resolution
        );
    }

    if (functionName.toLower() == "cloudpointvalidate")
    {
        return cloudPointValidate(
            values.size() > 0 ? values[0].toFloat() : 0.2f  // validationRatio
        );
    }

    if (functionName.toLower() == "cloudpointsave")
    {
        return cloudPointSave(
            values.size() > 0 ? values[0] : ""  // filename
        );
    }

    if (functionName.toLower() == "cloudpointload")
    {
        return cloudPointLoad(
            values.size() > 0 ? values[0] : ""  // filename
        );
    }

    if (functionName.toLower() == "cloudpointexport")
    {
        return cloudPointExport(
            values.size() > 0 ? values[0] : "CloudMapping"  // variableName
        );
    }

    if (functionName.toLower() == "cloudpointimport")
    {
        return cloudPointImport(
            values.size() > 0 ? values[0] : "CloudMapping"  // variableName
        );
    }

    if (functionName.toLower() == "cloudpointremove")
    {
        return cloudPointRemove(
            values[0].toInt()  // index
        );
    }

    if (functionName.toLower() == "cloudpointupdate")
    {
        return cloudPointUpdate(
            values[0].toInt(),    // index
            values[1].toFloat(),  // imageX
            values[2].toFloat(),  // imageY
            values[3].toFloat(),  // imageZ
            values[4].toFloat(),  // realX
            values[5].toFloat(),  // realY
            values[6].toFloat(),  // realZ
            values.size() > 7 ? values[7].toFloat() : 1.0f  // confidence
        );
    }

    // Get calibration point data functions
    if (functionName.toLower() == "cloudpointgetimagex")
    {
        return cloudPointGetImageX(values[0].toInt());
    }

    if (functionName.toLower() == "cloudpointgetimagey")
    {
        return cloudPointGetImageY(values[0].toInt());
    }

    if (functionName.toLower() == "cloudpointgetimagez")
    {
        return cloudPointGetImageZ(values[0].toInt());
    }

    if (functionName.toLower() == "cloudpointgetrealx")
    {
        return cloudPointGetRealX(values[0].toInt());
    }

    if (functionName.toLower() == "cloudpointgetrealy")
    {
        return cloudPointGetRealY(values[0].toInt());
    }

    if (functionName.toLower() == "cloudpointgetrealz")
    {
        return cloudPointGetRealZ(values[0].toInt());
    }

    if (functionName.toLower() == "cloudpointgetpointconfidence")
    {
        return cloudPointGetPointConfidence(values[0].toInt());
    }

    if (functionName.toLower() == "cloudpointgetpointerror")
    {
        return cloudPointGetPointError(values[0].toInt());
    }

    // ======== OBJECT MANAGEMENT FUNCTIONS ========

    // Set object picked: #setObjectPicked(index) or #setObjectPicked(listName, index)
    if (functionName.toLower() == "setobjectpicked")
    {
        if (values.size() == 1) {
            // #setObjectPicked(#PickableObjects.[#i]) uses the list name from context.
            // Keep "PickableObjects" as the compatibility default.
            return setObjectPickedByIndex("PickableObjects", values[0].toInt());
        } else if (values.size() >= 2) {
            // #setObjectPicked("Objects", #PickableObjects.[#i])
            return setObjectPickedByIndex(values[0], values[1].toInt());
        }
        return 0.0f;
    }

    // Get object index by UID: #getObjectIndex(listName, uid)  
    if (functionName.toLower() == "getobjectindex")
    {
        return getObjectIndex(
            values.size() > 0 ? values[0] : "Objects",  // listName
            values.size() > 1 ? values[1].toInt() : -1  // uid
        );
    }

    return NULL_NUMBER;
}

// ======== CLOUD POINT MAPPING FUNCTIONS IMPLEMENTATION ========

float GcodeScript::cloudPointAddCalibration(float imageX, float imageY, float imageZ, float realX, float realY, float realZ, float confidence, QString label)
{
    CloudPointMapper* mapper = getCloudPointMapper();
    if (!mapper) {
        return -1.0f;
    }
    
    QVector3D imageCoord(imageX, imageY, imageZ);
    QVector3D realCoord(realX, realY, realZ);
    
    int index = mapper->addCalibrationPoint(imageCoord, realCoord, confidence, label);
    
    // Auto-export to variables after adding point
    if (index >= 0) {
        mapper->exportToVariableManager(
            VariableManager::scopedKey(ProjectName, QStringLiteral("CloudMapping")));
    }
    
    return static_cast<float>(index);
}

float GcodeScript::cloudPointTransformX(float imageX, float imageY, float imageZ, int method)
{
    CloudPointMapper* mapper = getCloudPointMapper();
    if (!mapper) {
        return NULL_NUMBER;
    }
    
    QVector3D imageCoord(imageX, imageY, imageZ);
    CloudPointMapper::InterpolationMethod interpMethod = static_cast<CloudPointMapper::InterpolationMethod>(method);
    
    CloudPointMapper::MappingResult result = mapper->transformImageToReal(imageCoord, interpMethod);
    
    if (result.isValid) {
        return result.transformedPoint.x();
    }
    
    return NULL_NUMBER;
}

float GcodeScript::cloudPointTransformY(float imageX, float imageY, float imageZ, int method)
{
    CloudPointMapper* mapper = getCloudPointMapper();
    if (!mapper) {
        return NULL_NUMBER;
    }
    
    QVector3D imageCoord(imageX, imageY, imageZ);
    CloudPointMapper::InterpolationMethod interpMethod = static_cast<CloudPointMapper::InterpolationMethod>(method);
    
    CloudPointMapper::MappingResult result = mapper->transformImageToReal(imageCoord, interpMethod);
    
    if (result.isValid) {
        return result.transformedPoint.y();
    }
    
    return NULL_NUMBER;
}

float GcodeScript::cloudPointTransformZ(float imageX, float imageY, float imageZ, int method)
{
    CloudPointMapper* mapper = getCloudPointMapper();
    if (!mapper) {
        return NULL_NUMBER;
    }
    
    QVector3D imageCoord(imageX, imageY, imageZ);
    CloudPointMapper::InterpolationMethod interpMethod = static_cast<CloudPointMapper::InterpolationMethod>(method);
    
    CloudPointMapper::MappingResult result = mapper->transformImageToReal(imageCoord, interpMethod);
    
    if (result.isValid) {
        return result.transformedPoint.z();
    }
    
    return NULL_NUMBER;
}

float GcodeScript::cloudPointGetConfidence(float imageX, float imageY, float imageZ, int method)
{
    CloudPointMapper* mapper = getCloudPointMapper();
    if (!mapper) {
        return 0.0f;
    }
    
    QVector3D imageCoord(imageX, imageY, imageZ);
    CloudPointMapper::InterpolationMethod interpMethod = static_cast<CloudPointMapper::InterpolationMethod>(method);
    
    CloudPointMapper::MappingResult result = mapper->transformImageToReal(imageCoord, interpMethod);
    
    if (result.isValid) {
        return result.confidence;
    }
    
    return 0.0f;
}

float GcodeScript::cloudPointGetError(float imageX, float imageY, float imageZ, int method)
{
    CloudPointMapper* mapper = getCloudPointMapper();
    if (!mapper) {
        return 999.0f;
    }
    
    QVector3D imageCoord(imageX, imageY, imageZ);
    CloudPointMapper::InterpolationMethod interpMethod = static_cast<CloudPointMapper::InterpolationMethod>(method);
    
    CloudPointMapper::MappingResult result = mapper->transformImageToReal(imageCoord, interpMethod);
    
    if (result.isValid) {
        return result.estimatedError;
    }
    
    return 999.0f;
}

QString GcodeScript::cloudPointGetStats()
{
    CloudPointMapper* mapper = getCloudPointMapper();
    if (!mapper) {
        return "Cloud mapping not available";
    }
    
    CloudPointMapper::MappingStats stats = mapper->getMappingStats();
    
    QString statsText;
    statsText += QString("Reference pairs: %1, ").arg(stats.totalPoints);
    statsText += QString("Mean residual: %1 mm, ").arg(stats.averageError, 0, 'f', 2);
    statsText += QString("Maximum residual: %1 mm, ").arg(stats.maxError, 0, 'f', 2);
    statsText += QString("Image-area coverage: %1%, ").arg(stats.coverage, 0, 'f', 1);
    statsText += QString("Validation: %1").arg(stats.isValid ? "Passed" : "Not passed");
    
    return statsText;
}

float GcodeScript::cloudPointGetCount()
{
    CloudPointMapper* mapper = getCloudPointMapper();
    if (!mapper) {
        return 0.0f;
    }
    
    return static_cast<float>(mapper->getPointCount());
}

float GcodeScript::cloudPointIsValid()
{
    CloudPointMapper* mapper = getCloudPointMapper();
    if (!mapper) {
        return 0.0f;
    }
    
    CloudPointMapper::MappingStats stats = mapper->getMappingStats();
    return stats.isValid ? 1.0f : 0.0f;
}

float GcodeScript::cloudPointClear()
{
    CloudPointMapper* mapper = getCloudPointMapper();
    if (!mapper) {
        return 0.0f;
    }
    
    mapper->clearMapping();
    return 1.0f;
}

float GcodeScript::cloudPointBuildGrid(float resolution)
{
    CloudPointMapper* mapper = getCloudPointMapper();
    if (!mapper) {
        return 0.0f;
    }
    
    bool success = mapper->buildMappingGrid(resolution);
    
    if (success) {
        // Auto-export to variables after building grid
        mapper->exportToVariableManager(
            VariableManager::scopedKey(ProjectName, QStringLiteral("CloudMapping")));
    }
    
    return success ? 1.0f : 0.0f;
}

float GcodeScript::cloudPointValidate(float validationRatio)
{
    CloudPointMapper* mapper = getCloudPointMapper();
    if (!mapper) {
        return 999.0f;
    }
    
    CloudPointMapper::MappingStats stats = mapper->validateMapping(validationRatio);
    return stats.averageError;
}

float GcodeScript::cloudPointSave(QString filename)
{
    CloudPointMapper* mapper = getCloudPointMapper();
    if (!mapper) {
        return 0.0f;
    }
    
    if (filename.isEmpty()) {
        // Generate default filename
        QString defaultPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
        QDir().mkpath(defaultPath + "/CloudPointMappings");
        filename = defaultPath + "/CloudPointMappings/mapping_" + QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".json";
    }
    
    bool success = mapper->saveToFile(filename);
    return success ? 1.0f : 0.0f;
}

float GcodeScript::cloudPointLoad(QString filename)
{
    CloudPointMapper* mapper = getCloudPointMapper();
    if (!mapper) {
        return 0.0f;
    }
    
    if (filename.isEmpty()) {
        return 0.0f;
    }
    
    bool success = mapper->loadFromFile(filename);
    
    if (success) {
        // Auto-export to variables after loading
        mapper->exportToVariableManager(
            VariableManager::scopedKey(ProjectName, QStringLiteral("CloudMapping")));
    }
    
    return success ? 1.0f : 0.0f;
}

float GcodeScript::cloudPointExport(QString variableName)
{
    CloudPointMapper* mapper = getCloudPointMapper();
    if (!mapper) {
        return 0.0f;
    }
    
    if (variableName.isEmpty()) {
        variableName = "CloudMapping";
    }
    
    bool success = mapper->exportToVariableManager(
        VariableManager::scopedKey(ProjectName, variableName));
    return success ? 1.0f : 0.0f;
}

float GcodeScript::cloudPointImport(QString variableName)
{
    CloudPointMapper* mapper = getCloudPointMapper();
    if (!mapper) {
        return 0.0f;
    }
    
    if (variableName.isEmpty()) {
        variableName = "CloudMapping";
    }
    
    bool success = mapper->importFromVariableManager(
        VariableManager::scopedKey(ProjectName, variableName));
    return success ? 1.0f : 0.0f;
}

float GcodeScript::cloudPointRemove(int index)
{
    CloudPointMapper* mapper = getCloudPointMapper();
    if (!mapper) {
        return 0.0f;
    }
    
    bool success = mapper->removeCalibrationPoint(index);
    
    if (success) {
        // Auto-export to variables after removing point
        mapper->exportToVariableManager(
            VariableManager::scopedKey(ProjectName, QStringLiteral("CloudMapping")));
    }
    
    return success ? 1.0f : 0.0f;
}

float GcodeScript::cloudPointUpdate(int index, float imageX, float imageY, float imageZ, float realX, float realY, float realZ, float confidence)
{
    CloudPointMapper* mapper = getCloudPointMapper();
    if (!mapper) {
        return 0.0f;
    }
    
    QVector3D imageCoord(imageX, imageY, imageZ);
    QVector3D realCoord(realX, realY, realZ);
    
    bool success = mapper->updateCalibrationPoint(index, imageCoord, realCoord, confidence);
    
    if (success) {
        // Auto-export to variables after updating point
        mapper->exportToVariableManager(
            VariableManager::scopedKey(ProjectName, QStringLiteral("CloudMapping")));
    }
    
    return success ? 1.0f : 0.0f;
}

float GcodeScript::cloudPointGetImageX(int index)
{
    CloudPointMapper* mapper = getCloudPointMapper();
    if (!mapper || index < 0 || index >= mapper->getPointCount()) {
        return NULL_NUMBER;
    }
    
    const CloudPointMapper::CalibrationPoint& point = mapper->getCalibrationPoint(index);
    return point.imageCoord.x();
}

float GcodeScript::cloudPointGetImageY(int index)
{
    CloudPointMapper* mapper = getCloudPointMapper();
    if (!mapper || index < 0 || index >= mapper->getPointCount()) {
        return NULL_NUMBER;
    }
    
    const CloudPointMapper::CalibrationPoint& point = mapper->getCalibrationPoint(index);
    return point.imageCoord.y();
}

float GcodeScript::cloudPointGetImageZ(int index)
{
    CloudPointMapper* mapper = getCloudPointMapper();
    if (!mapper || index < 0 || index >= mapper->getPointCount()) {
        return NULL_NUMBER;
    }
    
    const CloudPointMapper::CalibrationPoint& point = mapper->getCalibrationPoint(index);
    return point.imageCoord.z();
}

float GcodeScript::cloudPointGetRealX(int index)
{
    CloudPointMapper* mapper = getCloudPointMapper();
    if (!mapper || index < 0 || index >= mapper->getPointCount()) {
        return NULL_NUMBER;
    }
    
    const CloudPointMapper::CalibrationPoint& point = mapper->getCalibrationPoint(index);
    return point.realCoord.x();
}

float GcodeScript::cloudPointGetRealY(int index)
{
    CloudPointMapper* mapper = getCloudPointMapper();
    if (!mapper || index < 0 || index >= mapper->getPointCount()) {
        return NULL_NUMBER;
    }
    
    const CloudPointMapper::CalibrationPoint& point = mapper->getCalibrationPoint(index);
    return point.realCoord.y();
}

float GcodeScript::cloudPointGetRealZ(int index)
{
    CloudPointMapper* mapper = getCloudPointMapper();
    if (!mapper || index < 0 || index >= mapper->getPointCount()) {
        return NULL_NUMBER;
    }
    
    const CloudPointMapper::CalibrationPoint& point = mapper->getCalibrationPoint(index);
    return point.realCoord.z();
}

float GcodeScript::cloudPointGetPointConfidence(int index)
{
    CloudPointMapper* mapper = getCloudPointMapper();
    if (!mapper || index < 0 || index >= mapper->getPointCount()) {
        return 0.0f;
    }
    
    const CloudPointMapper::CalibrationPoint& point = mapper->getCalibrationPoint(index);
    return point.confidence;
}

float GcodeScript::cloudPointGetPointError(int index)
{
    CloudPointMapper* mapper = getCloudPointMapper();
    if (!mapper || index < 0 || index >= mapper->getPointCount()) {
        return 999.0f;
    }
    
    const CloudPointMapper::CalibrationPoint& point = mapper->getCalibrationPoint(index);
    return point.error;
}

QString GcodeScript::cloudPointGetLabel(int index)
{
    CloudPointMapper* mapper = getCloudPointMapper();
    if (!mapper || index < 0 || index >= mapper->getPointCount()) {
        return "";
    }
    
    const CloudPointMapper::CalibrationPoint& point = mapper->getCalibrationPoint(index);
    return point.label;
}

bool GcodeScript::isGlobalVariable(QString name)
{
    if (name.isNull())
        return false;

    if (name.length() > 6)
    {
        if (name.indexOf("#GLOBAL") == 0)
            return true;
    }

    return false;
}

bool GcodeScript::isConveyorGcode(QString gcode)
{
    QString conveyorGcodes = "M310 M311 M312 M313";
    QString prefix = gcode.trimmed().section(' ', 0, 0).toUpper();
    if (conveyorGcodes.split(' ').contains(prefix))
        return true;
    return false;
}

bool GcodeScript::isSlidingGcode(QString gcode)
{
    QString conveyorGcodes = "M320 M321 M322 M323";
    QString prefix = gcode.trimmed().section(' ', 0, 0).toUpper();
    if (conveyorGcodes.split(' ').contains(prefix))
        return true;
    return false;
}

bool GcodeScript::isEncoderGcode(QString gcode)
{
    QString encoderGcodes = "M316 M317 M318 M319 M422";
    QString prefix = gcode.trimmed().section(' ', 0, 0).toUpper();
    if (encoderGcodes.split(' ').contains(prefix))
        return true;
    return false;
}

bool GcodeScript::isMovingGcode(QString gcode)
{
    QString movingGcodes = "G01 G00 G1 G0 G02 G03";
    QString prefix = gcode.trimmed().section(' ', 0, 0).toUpper();
    if (movingGcodes.split(' ').contains(prefix))
        return true;
    return false;
}

bool GcodeScript::findExeGcodeAndTransmit()
{
    try {
        return executeCurrentStatement();
    } catch (const GScriptEvaluationError& error) {
        faultExecution(QString::fromUtf8(error.what()), true);
        return true;
    }
}

bool GcodeScript::executeCurrentStatement()
{
    currentGcodeEditorCursor = gcodeOrder;

    if (elapsedTimer.restart() > 50 && gcodeList.count() > 1)
        emit Moved(currentGcodeEditorCursor);

    prepareCurrentLine();
    
    if (shouldSkipLine()) return false;
    collapseGcodeLine();
    if (!isRunning)
        return true;

//    processVARIABLE();

    //-------------- Find macro ------------------------

    // Cache string operations for better performance
    QStringList valuePairs = currentLine.split(' ', Qt::SkipEmptyParts);
    QString transmitGcode = currentLine;

    QString shortcutGcode;
    if (tryGenerateMoveShortcut(valuePairs, shortcutGcode)) {
        currentLine = shortcutGcode;
        valuePairs = currentLine.split(' ', Qt::SkipEmptyParts);
        transmitGcode = shortcutGcode;
    }

    const int valuePairsSize = valuePairs.size();

    if (valuePairsSize > 1 && isExplicitDeviceToken(valuePairs.first())) {
        handleSENT_TO_DEVICE(valuePairs, 0);
        return true;
    }

    for (int i = 0; i < valuePairsSize; i++)
    {
        // Skip empty tokens (already handled by Qt::SkipEmptyParts above)
        const QString& currentToken = valuePairs[i];  // Use reference to avoid copy
        const QString currentCommand = currentToken.toUpper();

        //------------ VARIABLE ------------

        // #100 = 2
        // #100 = #100 + 2
        // #100 = #101 - #102

        if (!currentToken.isEmpty() && currentToken[0] == '#' && valuePairsSize > (i + 2))
        {
            if (valuePairs[i + 1] == "=")
            {
                QString rightExpression = currentLine.mid(currentLine.indexOf('=') + 1).trimmed();
                
                // Try treat right side as a function call first
                QStringList arguments;
                QString functionName = parseFunctionCall(rightExpression, arguments);
                if (!functionName.isEmpty())
                {
                    if (!functionDefinitions.contains(functionName))
                    {
                        preprocessGcodeScript();
                    }
                    if (functionDefinitions.contains(functionName))
                    {
                        // Handle function call with return value assignment
                        QString varName = currentToken.mid(1); // Remove #
                        callFunction(functionName, arguments, varName);
                        return false;
                    }
                }
                
                // Handle regular variable assignment
                if(valuePairs[i + 2].contains(".Map("))
                {
                    if (!rightExpression.isEmpty() && rightExpression[0] == '#')
                    {
                        QString matrix;
                        QString point;

                        int mapIndex = rightExpression.indexOf(".Map(");
                        int pointIndex = rightExpression.indexOf('(', mapIndex);
                        int pointIndex2 = rightExpression.indexOf(')', pointIndex);

                        if (pointIndex != -1)
                        {
                            matrix = rightExpression.mid(0, mapIndex);
                            point = rightExpression.mid(pointIndex + 1, pointIndex2 - pointIndex - 1);
                        }

                        if (matrix != "" && point != "")
                        {
                            QString matrixName = matrix;
                            QString pointName = point;
                            QStringList paras = pointName.split(',');
                            QVariant matrixVar = getValueAsQVariant(matrixName);
                            QPointF point;

                            // Robustly parse Map arguments: support variables and numeric expressions
                            QStringList args = splitArgsRespectingParens(pointName);
                            if (args.size() >= 2)
                            {
                                // Evaluate each component separately to allow '#var', literals, or expressions
                                QString xs = calculateExpressions(args[0]).trimmed();
                                QString ys = calculateExpressions(args[1]).trimmed();
                                point.setX(xs.toFloat());
                                point.setY(ys.toFloat());
                            }
                            else if (!pointName.isEmpty() && pointName[0] == '#')
                            {
                                if (pointName.contains("."))
                                {
                                    bool result;
                                    pointName.split('.')[1].toInt(&result);
                                    if (result == true)
                                    {
                                        point.setX(getValueAsQVariant(pointName + ".X").toFloat());
                                        point.setY(getValueAsQVariant(pointName + ".Y").toFloat());
                                    }
                                    else
                                    {
                                        // Try direct scalar variables
                                        point.setX(getValueAsQVariant(pointName).toFloat());
                                        point.setY(0.0);
                                    }
                                }
                                else
                                {
                                    QVariant pv = getValueAsQVariant(pointName);
                                    if (pv.canConvert<QPointF>())
                                        point = pv.value<QPointF>();
                                    else
                                    {
                                        // Fallback: try separate .X/.Y
                                        point.setX(getValueAsQVariant(pointName + ".X").toFloat());
                                        point.setY(getValueAsQVariant(pointName + ".Y").toFloat());
                                    }
                                }
                            }
                            else if (paras.count() > 1)
                            {
                                point.setX(calculateExpressions(paras[0]).toFloat());
                                point.setY(calculateExpressions(paras[1]).toFloat());
                            }
                            if (matrixVar.canConvert<QTransform>())
                            {
                                QTransform matrix = matrixVar.value<QTransform>();

                                point = matrix.map(point);

                                QString varName = currentToken.mid(1);
                                saveVariable(varName, point);

                                gcodeOrder++;
                                return false;
                            }
                            else if (matrixVar.canConvert<QMatrix>())
                            {
                                QMatrix matrix = matrixVar.value<QMatrix>();

                                point = matrix.map(point);

                                QString varName = currentToken.mid(1);
                                saveVariable(varName, point);

                                gcodeOrder++;
                                return false;
                            }
                            else if (matrixVar.canConvert<std::vector<double>>()) {
                                std::vector<double> matrixArray = matrixVar.value<std::vector<double>>();
                                if (matrixArray.size() == 9) {
                                    cv::Mat transformMatrix = cv::Mat(matrixArray).reshape(1, 3);
                                    // Convert QPointF to cv::Point2f.
                                    cv::Point2f cvInputPoint(point.x(), point.y());

                                    // Build the input point array.
                                    std::vector<cv::Point2f> inputPoints;
                                    inputPoints.push_back(cvInputPoint);

                                    // Allocate the output point array.
                                    std::vector<cv::Point2f> outputPoints;

                                    // Apply the perspective transformation.
                                    cv::perspectiveTransform(inputPoints, outputPoints, transformMatrix);

                                    // Retrieve the transformed point.
                                    cv::Point2f cvOutputPoint = outputPoints[0];

                                    // Convert cv::Point2f back to QPointF.
                                    QPointF outputPoint(cvOutputPoint.x, cvOutputPoint.y);

                                    QString varName = currentToken.mid(1);
                                    saveVariable(varName, outputPoint);

                                    gcodeOrder++;
                                    return false;
                                }
                            }
                            else if (matrixVar.type() == QVariant::String) {
                                // Try to parse "m11,m12,m21,m22,dx,dy"
                                QString s = matrixVar.toString().trimmed();
                                QStringList parts = s.split(',');
                                if (parts.size() == 6) {
                                    bool ok[6] = {false,false,false,false,false,false};
                                    double a = parts[0].toDouble(&ok[0]);
                                    double b = parts[1].toDouble(&ok[1]);
                                    double c = parts[2].toDouble(&ok[2]);
                                    double d = parts[3].toDouble(&ok[3]);
                                    double tx= parts[4].toDouble(&ok[4]);
                                    double ty= parts[5].toDouble(&ok[5]);
                                    if (ok[0]&&ok[1]&&ok[2]&&ok[3]&&ok[4]&&ok[5]) {
                                        QTransform matrix(a,b,0,
                                                          c,d,0,
                                                          tx,ty,1);
                                        point = matrix.map(point);

                                        QString varName = currentToken.mid(1);
                                        saveVariable(varName, point);

                                        gcodeOrder++;
                                        return false;
                                    }
                                }
                            }
                        }
                    }
                }
                if (rightExpression.startsWith("#GetObjectInArea", Qt::CaseInsensitive))
                {
                    const auto area = QRegularExpression("^#GetObjectInArea\\s*\\((.*)\\)$",
                        QRegularExpression::CaseInsensitiveOption).match(rightExpression);
                    if (!area.hasMatch())
                        throw GScriptEvaluationError("Malformed GetObjectInArea call.");
                    const QStringList args = GScriptSyntax::splitArguments(area.captured(1));
                    if (args.size() != 3)
                        throw GScriptEvaluationError("GetObjectInArea requires tracking ID, axis minimum and axis maximum.");
                    const int trackingId = boundedInteger(finiteNumber(calculateExpressions(args[0]), "Tracking ID"),
                        0, std::numeric_limits<int>::max(), "Tracking ID");
                    const auto lower = QRegularExpression("^([XY])_MIN\\s*=\\s*(.+)$",
                        QRegularExpression::CaseInsensitiveOption).match(args[1]);
                    const auto upper = QRegularExpression("^([XY])_MAX\\s*=\\s*(.+)$",
                        QRegularExpression::CaseInsensitiveOption).match(args[2]);
                    if (!lower.hasMatch() || !upper.hasMatch() ||
                        lower.captured(1).compare(upper.captured(1), Qt::CaseInsensitive) != 0)
                        throw GScriptEvaluationError("GetObjectInArea requires matching X_MIN/X_MAX or Y_MIN/Y_MAX bounds.");
                    const double minimum = finiteNumber(calculateExpressions(lower.captured(2)), "Area minimum");
                    const double maximum = finiteNumber(calculateExpressions(upper.captured(2)), "Area maximum");
                    if (minimum > maximum || std::abs(minimum) > std::numeric_limits<float>::max() ||
                        std::abs(maximum) > std::numeric_limits<float>::max())
                        throw GScriptEvaluationError("GetObjectInArea bounds are invalid.");
                    const QString target = currentToken;
                    const bool isX = lower.captured(1).compare("X", Qt::CaseInsensitive) == 0;
                    transmitDeviceId = QString("tracking%1").arg(trackingId);
                    transmitMsg = currentLine;
                    ++pendingResponseToken;
                    expectedTrackingRequestId = nextVisionRequestId();
                    pendingClaimResult = cleanedVarName(target);
                    pendingAreaResult = true;
                    requireCorrelatedTrackingResponse = isSignalConnected(
                        QMetaMethod::fromSignal(&GcodeScript::GetObjectsCorrelatedRequest));
                    gcodeOrder++;
                    startPendingResponseTimeout(transmitDeviceId, transmitMsg, 1500);
                    if (requireCorrelatedTrackingResponse)
                        emit GetObjectsCorrelatedRequest(expectedTrackingRequestId, trackingId, target, minimum, maximum, isX);
                    else
                        emit GetObjectsRequest(trackingId, target, minimum, maximum, isX);
                    return true;
                }
                else
                {
                    if (currentLine.contains("IsPicked"))
                    {
                        emit ChangeExternalVariable(currentLine);
                    }
                    return handleVARIABLE(valuePairs, i);

                }

            }

        }

        //------------ GOTO -----------

        if (currentCommand == "GOTO" && valuePairsSize > (i + 1))
        {
            return handleGOTO(valuePairs, i);
        }

        // --------------- JUMP (named label) ---------------------
        if (currentCommand == "JUMP" && valuePairsSize > (i + 1))
        {
            return handleJUMP(valuePairs, i);
        }

        // --------------- LABEL (no-op at runtime) ---------------------
        if (currentCommand == "LABEL")
        {
            gcodeOrder++;
            return false;
        }

        // --------------- IF-ELIF-ELSE-ENDIF ---------------------
        if (currentCommand == "IF")
        {
            return handleIF(valuePairs, i);
        }
        
        // --------------- ELIF ---------------------
        if (currentCommand == "ELIF")
        {
            return handleELIF(valuePairs, i);
        }
        
        // --------------- ELSE ---------------------
        if (currentCommand == "ELSE")
        {
            return handleELSE(valuePairs, i);
        }
        
        // --------------- ENDIF ---------------------
        if (currentCommand == "ENDIF")
        {
            return handleENDIF(valuePairs, i);
        }
        
        // --------------- FOR LOOPS ---------------------
        if (currentCommand == "FOR" && valuePairsSize > (i + 1))
        {
            return handleFOR(valuePairs, i);
        }
        
        // --------------- ENDFOR ---------------------
        if (currentCommand == "ENDFOR")
        {
            return handleENDFOR(valuePairs, i);
        }

        if (currentCommand == "WHILE")
            return handleWHILE(valuePairs, i);

        if (currentCommand == "ENDWHILE")
            return handleENDWHILE(valuePairs, i);

        if (currentCommand == "BREAK")
            return handleBREAK();

        if (currentCommand == "CONTINUE")
            return handleCONTINUE();

        if (currentCommand == "SWITCH")
            return handleSWITCH(valuePairs, i);

        if (currentCommand == "CASE")
            return handleCASE(valuePairs, i);

        if (currentCommand == "DEFAULT")
            return handleDEFAULT();

        if (currentCommand == "ENDSWITCH")
            return handleENDSWITCH();
        
        // --------------- FUNCTION DECLARATION ---------------------
        if (currentCommand == "FUNCTION" && valuePairsSize > (i + 1))
        {
            return handleFUNCTION(valuePairs, i);
        }
        
        // --------------- ENDFUNCTION ---------------------
        if (currentCommand == "ENDFUNCTION")
        {
            return handleENDFUNCTION(valuePairs, i);
        }
        
        // --------------- RETURN ---------------------
        if (currentCommand == "RETURN")
        {
            return handleRETURN(valuePairs, i);
        }

        if (currentCommand == "LOCAL")
            return handleLOCAL(valuePairs, i);

        // --------------- DEFINE SUBPROGRAM ------

        // N15 O2000
        // ....
        // N45 M99

        if (!currentCommand.isEmpty() && currentCommand[0] == 'O')
        {
            return handleDEFINE_SUBPROGRAM(valuePairs, i);
        }

        // --------------- CALL SUBPROGRAM --------

        // N50 M98 P2000



        if (currentCommand == "M98" && valuePairsSize > (i + 1))
        {
            const auto call = GScriptSyntax::parseMacroCall(currentLine);
            if (call.valid) {
                const QString functionName = call.target;
                const QStringList paramList = call.arguments;
                if (const auto* primitive = GScriptSyntax::findPrimitive(functionName)) {
                    if (call.parenthesized || !primitive->legacyBare) {
                        if (paramList.size() < primitive->minimumArguments ||
                            paramList.size() > primitive->maximumArguments)
                            throw GScriptEvaluationError(QString("%1 expects %2 to %3 arguments; received %4.")
                                .arg(functionName).arg(primitive->minimumArguments)
                                .arg(primitive->maximumArguments).arg(paramList.size()));
                    }
                }

                auto identifierParameter = [](QString value) {
                    value = value.trimmed();
                    if (value.size() >= 2 &&
                        ((value.startsWith('"') && value.endsWith('"')) ||
                         (value.startsWith('\'') && value.endsWith('\'')))) {
                        value = value.mid(1, value.size() - 2);
                    }
                    if (value.startsWith('#'))
                        value.remove(0, 1);
                    return value.trimmed();
                };

                auto textParameter = [this, &identifierParameter](QString value) {
                    value = value.trimmed();
                    if (value.size() >= 2 &&
                        ((value.startsWith('"') && value.endsWith('"')) ||
                         (value.startsWith('\'') && value.endsWith('\'')))) {
                        return value.mid(1, value.size() - 2);
                    }
                    if (value.startsWith('#')) {
                        // Use the expression resolver so vector/point members
                        // such as #Position.X are printable too.
                        return calculateExpressions(value).trimmed();
                    }
                    return value;
                };

                auto numericParameter = [this](const QString& value, double) {
                    return finiteNumber(calculateExpressions(value), "Primitive argument");
                };

                auto integerParameter = [&numericParameter](const QString& value, int minimum,
                                                            int maximum, const QString& name) {
                    return boundedInteger(numericParameter(value, 0), minimum, maximum, name);
                };

                if (functionName == "send" || functionName == "sendgcode")
                {
                    if (paramList.size() < 2 || paramList.size() > 4) {
                        faultExecution("send requires: deviceId, command[, responseVariable[, timeoutMs]].");
                        return true;
                    }

                    const QString deviceId = textParameter(paramList[0]);
                    const QString command = textParameter(paramList[1]);
                    const QString responseVariable = paramList.size() > 2
                        ? identifierParameter(paramList[2]) : QString();
                    const int timeoutMs = paramList.size() > 3
                        ? integerParameter(paramList[3], 1, 86400000, "Device timeout") : 120000;
                    gcodeOrder++;
                    beginDeviceRequest(deviceId, command, timeoutMs, responseVariable);
                    return true;
                }

                if (functionName == "assert")
                {
                    if (paramList.isEmpty() || paramList.size() > 2) {
                        faultExecution("assert requires: condition[, message].");
                        return true;
                    }
                    const bool passed = !qFuzzyIsNull(
                        static_cast<float>(numericParameter(paramList[0], 0.0)));
                    if (!passed) {
                        const QString message = paramList.size() > 1
                            ? textParameter(paramList[1]) : QStringLiteral("G-Script assertion failed.");
                        faultExecution(message.isEmpty()
                                           ? QStringLiteral("G-Script assertion failed.")
                                           : message,
                                       true);
                        return true;
                    }
                    gcodeOrder++;
                    return false;
                }

                if (functionName == "waituntil")
                {
                    if (paramList.size() < 2 || paramList.size() > 4) {
                        faultExecution("waitUntil requires: condition, timeoutMs[, pollMs[, message]].");
                        return true;
                    }

                    pendingConditionExpression = paramList[0].trimmed();
                    pendingConditionTimeoutMs = integerParameter(paramList[1], 1, 86400000, "waitUntil timeout");
                    pendingConditionPollMs = paramList.size() > 2
                        ? qBound(5, integerParameter(paramList[2], 1, 86400000, "waitUntil poll"), 1000)
                        : 20;
                    pendingConditionMessage = paramList.size() > 3
                        ? textParameter(paramList[3]) : QString();
                    pendingConditionToken = ++pendingResponseToken;
                    pendingConditionTimer.restart();
                    publishExecutionVariable("ActiveCondition", pendingConditionExpression);
                    setExecutionState(
                        ExecutionState::WaitingForCondition,
                        QString("Waiting for condition (timeout %1 ms)")
                            .arg(pendingConditionTimeoutMs));
                    gcodeOrder++;
                    QTimer::singleShot(0, this, &GcodeScript::pollPendingCondition);
                    return true;
                }

                // Unified handling: M98 PupdateTracking / PupdateTracking(0)
                if (GScriptSyntax::findPrimitive(functionName) &&
                    GScriptSyntax::findPrimitive(functionName)->name == "updatetracking")
                {
                    int trackingId = 0;
                    if (!paramList.isEmpty()) {
                        trackingId = integerParameter(paramList.first(), 0, std::numeric_limits<int>::max(), "Tracking ID");
                    } else {
                        // Support numeric suffix: PupdateTracking0
                        QRegularExpression rx("^updatetracking(\\d+)$");
                        QRegularExpressionMatch mm = rx.match(functionName);
                        if (mm.hasMatch()) trackingId = boundedInteger(finiteNumber(mm.captured(1), "Tracking ID"),
                            0, std::numeric_limits<int>::max(), "Tracking ID");
                    }

                    transmitDeviceId = QString("tracking") + QString::number(trackingId);
                    transmitMsg = "M98 PupdateTracking";
                    pendingResponseToken++;
                    expectedTrackingRequestId = nextVisionRequestId();
                    requireCorrelatedTrackingResponse = isSignalConnected(
                        QMetaMethod::fromSignal(&GcodeScript::UpdateTrackingCorrelatedRequest));
                    gcodeOrder++;
                    startPendingResponseTimeout(transmitDeviceId, transmitMsg, 1500);
                    if (requireCorrelatedTrackingResponse)
                        emit UpdateTrackingCorrelatedRequest(expectedTrackingRequestId, trackingId);
                    else
                        emit UpdateTrackingRequest(trackingId);
                    return true;
                }

                // Unified handling: M98 PcaptureAndDetect / PcaptureAndDetect(0)
                if (GScriptSyntax::findPrimitive(functionName) &&
                    GScriptSyntax::findPrimitive(functionName)->name == "captureanddetect")
                {
                    int trackingId = 0;
                    if (!paramList.isEmpty()) {
                        trackingId = integerParameter(paramList.first(), 0, std::numeric_limits<int>::max(), "Tracking ID");
                    } else {
                        const auto suffix = QRegularExpression("^captureanddetect(\\d+)$").match(functionName);
                        if (suffix.hasMatch())
                            trackingId = boundedInteger(finiteNumber(suffix.captured(1), "Tracking ID"),
                                0, std::numeric_limits<int>::max(), "Tracking ID");
                    }

                    // Per-run routing state; it must not survive an application restart.
                    saveRuntimeVariable("Camera.TrackingID", trackingId);

                    transmitDeviceId = QString("vision") + QString::number(trackingId);
                    transmitMsg = "M98 PcaptureAndDetect";
                    pendingResponseToken++;
                    expectedVisionRequestId = nextVisionRequestId();
                    gcodeOrder++;
                    startPendingResponseTimeout(transmitDeviceId, transmitMsg, 5000);
                    emit CaptureAndDetectRequest(expectedVisionRequestId, trackingId);
                    return true;
                }

                // M98 PclaimObject(trackingId, resultName, owner,
                //                      minX, maxX, minY, maxY[, type[, leaseMs]])
                if (functionName == "claimobject")
                {
                    if (paramList.size() < 7) {
                        emit LogMessage("claimObject requires: trackingId, resultName, owner, minX, maxX, minY, maxY[, type[, leaseMs]].");
                        finishExecution(true, "Invalid claimObject parameters.", true);
                        return true;
                    }

                    const int trackingId = integerParameter(paramList[0], 0, std::numeric_limits<int>::max(), "Tracking ID");
                    const QString resultName = identifierParameter(paramList[1]);
                    const QString owner = textParameter(paramList[2]);
                    const float minX = static_cast<float>(numericParameter(paramList[3], 0));
                    const float maxX = static_cast<float>(numericParameter(paramList[4], 0));
                    const float minY = static_cast<float>(numericParameter(paramList[5], 0));
                    const float maxY = static_cast<float>(numericParameter(paramList[6], 0));
                    const int typeFilter = paramList.size() > 7
                        ? integerParameter(paramList[7], -1, std::numeric_limits<int>::max(), "Type filter") : -1;
                    const int leaseMs = paramList.size() > 8
                        ? integerParameter(paramList[8], 1, 86400000, "Claim lease") : 30000;
                    if (minX > maxX || minY > maxY || !std::isfinite(minX) || !std::isfinite(maxX) ||
                        !std::isfinite(minY) || !std::isfinite(maxY) || owner.isEmpty() || resultName.isEmpty())
                        throw GScriptEvaluationError("Invalid claim bounds, result variable, or owner.");

                    transmitDeviceId = QString("tracking%1:%2").arg(trackingId).arg(owner);
                    transmitMsg = "M98 PclaimObject";
                    pendingResponseToken++;
                    expectedTrackingRequestId = nextVisionRequestId();
                    pendingClaimResult = resultName;
                    requireCorrelatedTrackingResponse = isSignalConnected(
                        QMetaMethod::fromSignal(&GcodeScript::ClaimObjectCorrelatedRequest));
                    gcodeOrder++;
                    startPendingResponseTimeout(transmitDeviceId, transmitMsg, 1500);
                    if (requireCorrelatedTrackingResponse)
                        emit ClaimObjectCorrelatedRequest(expectedTrackingRequestId, trackingId, resultName, owner,
                                                          minX, maxX, minY, maxY, typeFilter, leaseMs);
                    else
                        emit ClaimObjectRequest(trackingId, resultName, owner,
                                                minX, maxX, minY, maxY, typeFilter, leaseMs);
                    return true;
                }

                // M98 PreleaseObject(trackingId, uid, owner)
                if (functionName == "releaseobject")
                {
                    if (paramList.size() < 3) {
                        emit LogMessage("releaseObject requires: trackingId, uid, owner.");
                        finishExecution(true, "Invalid releaseObject parameters.", true);
                        return true;
                    }

                    const int trackingId = integerParameter(paramList[0], 0, std::numeric_limits<int>::max(), "Tracking ID");
                    const int uid = integerParameter(paramList[1], 0, std::numeric_limits<int>::max(), "Object UID");
                    const QString owner = textParameter(paramList[2]);

                    transmitDeviceId = QString("tracking%1:%2").arg(trackingId).arg(owner);
                    transmitMsg = "M98 PreleaseObject";
                    pendingResponseToken++;
                    expectedTrackingRequestId = nextVisionRequestId();
                    requireCorrelatedTrackingResponse = isSignalConnected(
                        QMetaMethod::fromSignal(&GcodeScript::ReleaseObjectCorrelatedRequest));
                    gcodeOrder++;
                    startPendingResponseTimeout(transmitDeviceId, transmitMsg, 1500);
                    if (requireCorrelatedTrackingResponse)
                        emit ReleaseObjectCorrelatedRequest(expectedTrackingRequestId, trackingId, uid, owner);
                    else
                        emit ReleaseObjectRequest(trackingId, uid, owner);
                    return true;
                }

                // M98 PcompleteObject(trackingId, uid, owner)
                if (functionName == "completeobject")
                {
                    if (paramList.size() < 3) {
                        emit LogMessage("completeObject requires: trackingId, uid, owner.");
                        finishExecution(true, "Invalid completeObject parameters.", true);
                        return true;
                    }

                    const int trackingId = integerParameter(paramList[0], 0, std::numeric_limits<int>::max(), "Tracking ID");
                    const int uid = integerParameter(paramList[1], 0, std::numeric_limits<int>::max(), "Object UID");
                    const QString owner = textParameter(paramList[2]);

                    transmitDeviceId = QString("tracking%1:%2").arg(trackingId).arg(owner);
                    transmitMsg = "M98 PcompleteObject";
                    pendingResponseToken++;
                    expectedTrackingRequestId = nextVisionRequestId();
                    requireCorrelatedTrackingResponse = isSignalConnected(
                        QMetaMethod::fromSignal(&GcodeScript::CompleteObjectCorrelatedRequest));
                    gcodeOrder++;
                    startPendingResponseTimeout(transmitDeviceId, transmitMsg, 1500);
                    if (requireCorrelatedTrackingResponse)
                        emit CompleteObjectCorrelatedRequest(expectedTrackingRequestId, trackingId, uid, owner);
                    else
                        emit CompleteObjectRequest(trackingId, uid, owner);
                    return true;
                }

                if (functionName == "delay")
                {
                    if (paramList.size() != 1) {
                        emit LogMessage("delay requires exactly one duration in milliseconds.");
                        finishExecution(true, "Invalid delay parameters.", true);
                        return true;
                    }

                    const int delayMs = integerParameter(paramList.first(), 0, 86400000, "Delay duration");
                    gcodeOrder++;
                    const quint64 delayToken = ++pendingResponseToken;
                    setExecutionState(ExecutionState::WaitingForTimer,
                                      QString("Delay %1 ms").arg(delayMs));
                    QTimer::singleShot(delayMs, this, [this, delayToken]() {
                        if (!isRunning || pendingResponseToken != delayToken)
                            return;
                        setExecutionState(ExecutionState::Running, "Program running");
                        TransmitNextGcode();
                    });
                    return true;
                }

                if (functionName == "addobject")
                {                    
                    QString listName = identifierParameter(paramList.at(0));
                    QStringList objectInfo;
                    for (int argument = 1; argument < paramList.size(); ++argument) {
                        const double value = numericParameter(paramList[argument], 0);
                        if (std::abs(value) > std::numeric_limits<float>::max())
                            throw GScriptEvaluationError("Object argument exceeds the supported coordinate range.");
                        objectInfo.append(QString::number(value, 'g', 12));
                    }
                    QList<QStringList> objects;
                    objects.append(objectInfo);

                    emit AddObject(listName, objects);
                    gcodeOrder++;
                    return false;
                }

                if (functionName == "pausecamera" || functionName == "capturecamera" ||
                    functionName == "resumecamera" || functionName == "deletefirstobject" ||
                    functionName == "syncconveyor" || functionName == "stopsyncconveyor") {
                    if (functionName == "pausecamera") emit PauseCamera();
                    else if (functionName == "capturecamera") emit CaptureCamera();
                    else if (functionName == "resumecamera") emit ResumeCamera();
                    else if (functionName == "deletefirstobject") emit DeleteObject(0);
                    else IsConveyorSync = functionName == "syncconveyor";
                    ++gcodeOrder;
                    return false;
                }

                if (functionName == "clearobjects" && currentLine.contains('(')) {
                    if (paramList.size() != 1) {
                        faultExecution("clearObjects requires exactly one list name.");
                        return true;
                    }
                    emit DeleteAllObjects(identifierParameter(paramList.first()));
                    ++gcodeOrder;
                    return false;
                }
                if (functionName == "logmessage" && currentLine.contains('(')) {
                    if (paramList.size() != 1) {
                        faultExecution("logMessage requires exactly one message.");
                        return true;
                    }
                    emit LogMessage(textParameter(paramList.first()));
                    ++gcodeOrder;
                    return false;
                }
                if (functionName == "deleteobject" && currentLine.contains('(')) {
                    if (paramList.size() != 1) {
                        faultExecution("deleteObject requires exactly one object index.");
                        return true;
                    }
                    emit DeleteObject(integerParameter(paramList.first(), 0, std::numeric_limits<int>::max(), "Object index"));
                    ++gcodeOrder;
                    return false;
                }

                PluginExtensionRegistry& extensions =
                    PluginExtensionRegistry::instance();
                if (extensions.hasGScriptPrimitive(functionName)) {
                    PluginGScriptPrimitive descriptor;
                    for (const PluginGScriptPrimitive& candidate :
                         extensions.gscriptPrimitives()) {
                        if (candidate.name == functionName) {
                            descriptor = candidate;
                            break;
                        }
                    }
                    if (paramList.size() < descriptor.minimumArguments ||
                        paramList.size() > descriptor.maximumArguments) {
                        faultExecution(
                            QString("Plugin primitive %1 expects %2 to %3 arguments; received %4.")
                                .arg(functionName)
                                .arg(descriptor.minimumArguments)
                                .arg(descriptor.maximumArguments)
                                .arg(paramList.size()),
                            true);
                        return true;
                    }

                    QString resultVariable;
                    QVariantList arguments;
                    for (int argumentIndex = 0;
                         argumentIndex < paramList.size(); ++argumentIndex) {
                        const QString raw = paramList.at(argumentIndex).trimmed();
                        if (argumentIndex == descriptor.resultArgument) {
                            resultVariable = identifierParameter(raw);
                            static const QRegularExpression resultVariablePattern(
                                QStringLiteral("^[A-Za-z_][A-Za-z0-9_.]*$"));
                            if (!resultVariablePattern.match(resultVariable).hasMatch()) {
                                faultExecution(
                                    QString("Plugin primitive %1 requires a result variable at argument %2.")
                                        .arg(functionName)
                                        .arg(argumentIndex + 1));
                                return true;
                            }
                            continue;
                        }

                        if (raw.size() >= 2 &&
                            ((raw.startsWith('"') && raw.endsWith('"')) ||
                             (raw.startsWith('\'') && raw.endsWith('\'')))) {
                            arguments.append(raw.mid(1, raw.size() - 2));
                        } else if (raw.startsWith('#')) {
                            arguments.append(getValueAsQVariant(raw));
                        } else {
                            bool numeric = false;
                            const QString evaluated = calculateExpressions(raw).trimmed();
                            const double number = evaluated.toDouble(&numeric);
                            arguments.append(numeric ? QVariant(number) : QVariant(raw));
                        }
                    }

                    QVariant result;
                    QString error;
                    if (!extensions.executeGScriptPrimitive(
                            functionName, arguments, &result, &error)) {
                        faultExecution(
                            QString("Plugin primitive %1 failed: %2")
                                .arg(functionName,
                                     error.isEmpty()
                                         ? QStringLiteral("unknown plugin error")
                                         : error),
                            true);
                        return true;
                    }
                    if (!resultVariable.isEmpty())
                        saveVariable(resultVariable, result);
                    gcodeOrder++;
                    return false;
                }
            }

            if (call.valid)
            {
                QString subProName = call.target;

                // PclearObjects = P_clear_object = PClearObject = ...

                if (subProName == "clearobjects")
                {
                    // M98 PclearObjects listName
                    if (valuePairs.size() > (i + 2))
                    {
                        QString listName = valuePairs[i + 2];
                        emit DeleteAllObjects(listName);
                    }
                    else
                    {
                        emit DeleteAllObjects();
                    }
                    gcodeOrder++;
                    return false;
                }

                if (subProName == "deletefirstobject")
                {
                    emit DeleteObject(0);
                    gcodeOrder++;
                    return false;
                }

                if (subProName == "deleteobject")
                {
                    int pos1 = subProName.indexOf("(") + 1;
                    int pos2 = subProName.lastIndexOf(")");
                    int value = subProName.mid(pos1, pos2 - pos1).toInt();

                    emit DeleteObject(value);
                    gcodeOrder++;
                    return false;
                }

                if (subProName == "pausecamera")
                {
                    emit PauseCamera();
                    gcodeOrder++;
                    return false;
                }

                if (subProName == "capturecamera")
                {
                    emit CaptureCamera();
                    gcodeOrder++;
                    return false;
                }

                if (subProName == "resumecamera")
                {
                    emit ResumeCamera();
                    gcodeOrder++;
                    return false;
                }
                
                if (subProName == "logmessage")
                {
                    // M98 PlogMessage("Hello World")
                    // M98 PlogMessage "Hello World"
                    
                    QString message;
                    
                    // Find the message part
                    int startIndex = currentLine.indexOf("logmessage", 0, Qt::CaseInsensitive);
                    if (startIndex != -1) {
                        QString remaining = currentLine.mid(startIndex + 10).trimmed(); // Skip "logmessage"
                        
                        // Handle different formats
                        if (remaining.startsWith("(") && remaining.endsWith(")")) {
                            // Format: PlogMessage("message")
                            message = remaining.mid(1, remaining.length() - 2);
                        } else if (remaining.startsWith("\"") && remaining.endsWith("\"")) {
                            // Format: PlogMessage "message"
                            message = remaining.mid(1, remaining.length() - 2);
                        } else {
                            // Format: PlogMessage message
                            message = remaining;
                        }
                    }
                    
                    // If we have remaining parameters, append them
                    if (valuePairs.size() > (i + 2)) {
                        for (int j = i + 2; j < valuePairs.size(); j++) {
                            if (!message.isEmpty()) message += " ";
                            message += valuePairs[j];
                        }
                    }
                    
                    emit LogMessage(message);
                    gcodeOrder++;
                    return false;
                }

                if (subProName == "syncconveyor")
                {
                    IsConveyorSync = true;
                    gcodeOrder++;
                    return false;
                }

                if (subProName == "stopsyncconveyor")
                {
                    IsConveyorSync = false;
                    gcodeOrder++;
                    return false;
                }

                if (subProName == "delay")
                {
                    int pos1 = subProName.indexOf("(") + 1;
                    int pos2 = subProName.lastIndexOf(")");
                    QString valueS = subProName.mid(pos1, pos2 - pos1);

                    const unsigned long delayMs = valueS.toULong();
                    gcodeOrder++;
                    const quint64 delayToken = ++pendingResponseToken;
                    setExecutionState(ExecutionState::WaitingForTimer,
                                      QString("Delay %1 ms").arg(delayMs));
                    QTimer::singleShot(delayMs, this, [this, delayToken]() {
                        if (!isRunning || pendingResponseToken != delayToken)
                            return;
                        setExecutionState(ExecutionState::Running, "Program running");
                        TransmitNextGcode();
                    });
                    return true;
                }

                // P_update_tracking = Pupdatetracking = PupdateTracking = P_updateTracking(0)
                if (subProName == "updatetracking")
                {
                    QString valueS = "0";
                    if (subProName.contains("("))
                    {
                        int pos1 = subProName.indexOf("(") + 1;
                        int pos2 = subProName.lastIndexOf(")");
                        valueS = subProName.mid(pos1, pos2 - pos1);
                    }
                    else
                    {
                        int pos = subProName.indexOf("tracking") + 8;
                        if (pos < subProName.count())
                        {
                            valueS = subProName.mid(pos);
                        }
                    }

                    transmitDeviceId = QString("tracking") + valueS;
                    transmitMsg = "M98 PupdateTracking";
                    pendingResponseToken++;
                    emit UpdateTrackingRequest(valueS.toInt());
                    startPendingResponseTimeout(transmitDeviceId, transmitMsg, 1500);

                    gcodeOrder++;
                    return true;
                }

                // P_capture_and_detect = Pcaptureanddetect = PcaptureAndDetect
                if (subProName == "captureanddetect")
                {
                    // Optional parameter: captureanddetect(n)
                    int trackingId = 0;
                    if (subProName.contains("("))
                    {
                        int pos1 = subProName.indexOf("(") + 1;
                        int pos2 = subProName.lastIndexOf(")");
                        trackingId = subProName.mid(pos1, pos2 - pos1).toInt();
                    }

                    // Per-run routing state; it must not survive an application restart.
                    saveRuntimeVariable("Camera.TrackingID", trackingId);

                    transmitDeviceId = QString("vision") + QString::number(trackingId);
                    transmitMsg = "M98 PcaptureAndDetect";
                    pendingResponseToken++;
                    expectedVisionRequestId = nextVisionRequestId();
                    emit CaptureAndDetectRequest(expectedVisionRequestId, trackingId);
                    startPendingResponseTimeout(transmitDeviceId, transmitMsg, 5000);

                    gcodeOrder++;
                    return true;
                }

                //QString funcName = "sendExternalMCU";

                if (subProName == "send")
                {
                    int pos1 = subProName.indexOf("\"") + 1;
                    int pos2 = subProName.lastIndexOf("\"");
                    QString msg = subProName.mid(pos1, pos2 - pos1);

                    pos1 = subProName.indexOf("send") + 4;
                    pos2 = subProName.indexOf('(');
                    QString deviceName = subProName.mid(pos1, pos2 - pos1);

                    SendMsgToDevice(deviceName, msg);

                    gcodeOrder++;
                    return false;
                }


                if (subProName == "sendgcode")
                {
                    int pos1 = subProName.indexOf("\"") + 1;
                    int pos2 = subProName.lastIndexOf("\"");
                    QString msg = subProName.mid(pos1, pos2 - pos1);

                    pos1 = subProName.indexOf("sendGcode") + 4;
                    pos2 = subProName.indexOf('(');
                    QString deviceName = subProName.mid(pos1, pos2 - pos1);

                    SendMsgToDevice(deviceName, msg);

                    gcodeOrder++;
                    return true;
                }

                for (int order = 0; order < gcodeList.size(); order++)
                {
                    QString candidate = gcodeList.at(order).trimmed();
                    candidate.remove(QRegularExpression("^N\\d+\\s+",
                        QRegularExpression::CaseInsensitiveOption));
                    const QString candidateToken = candidate.section(
                        QRegularExpression("\\s+"), 0, 0).remove('_').toLower();
                    if (candidateToken == QString("o") + subProName)
                    {
                        if (returnPointerOrder + 1 >= 20) {
                            faultExecution("Subprogram call depth exceeds the limit of 20.");
                            return true;
                        }
                        returnPointerOrder++;
                        returnSubProPointer[returnPointerOrder] = gcodeOrder;
                        SubprogramFrame& frame = subprogramFrames[returnPointerOrder];
                        frame.ifDepth = ifBlockStack.size();
                        frame.forDepth = forLoopStack.size();
                        frame.whileDepth = whileLoopStack.size();
                        frame.switchDepth = switchCaseStack.size();
                        frame.functionDepth = callStack.size();

                        gcodeOrder = order + 1;

                        //TransmitNextGcode();

                        return false;
                    }
                }

                faultExecution(QString("Undefined M98 macro or subprogram: P%1.")
                                   .arg(subProName), true);
                return true;
            }

            if (!valuePairs[i + 1].isEmpty() && valuePairs[i + 1].at(0) == 'F')
            {
                QString subProName = valuePairs[i + 1].mid(1);
            }
        }

        if (currentCommand == "M99")
        {
            if (returnPointerOrder < 0) {
                faultExecution("M99 has no active subprogram call.");
                return true;
            }
            const SubprogramFrame frame = subprogramFrames[returnPointerOrder];
            if (callStack.size() != frame.functionDepth) {
                faultExecution("M99 cannot return across a function call boundary.");
                return true;
            }
            while (ifBlockStack.size() > frame.ifDepth)
                ifBlockStack.pop();
            while (forLoopStack.size() > frame.forDepth)
                forLoopStack.pop();
            while (whileLoopStack.size() > frame.whileDepth)
                whileLoopStack.pop();
            while (switchCaseStack.size() > frame.switchDepth)
                switchCaseStack.pop();
            gcodeOrder = returnSubProPointer[returnPointerOrder] + 1;
            returnSubProPointer[returnPointerOrder] = -1;
            subprogramFrames[returnPointerOrder] = SubprogramFrame{};
            returnPointerOrder--;
            return false;
        }

        if (currentCommand == "SYNC")
        {
            QString target = valuePairs[i + 1];
            if (target.contains("robot") && valuePairs.count() > i + 2)
            {
                QString vector = "";
                for (int j = i + 2; j < valuePairs.count(); j++)
                {
                    vector += valuePairs.at(j);
                }

                if (vector.at(0) == '#')
                {
                    QVector3D val = getValueAsQVariant(vector).value<QVector3D>();
                    vector = QString("(%1, %2, %3)")
                            .arg(val.x())
                            .arg(val.y())
                            .arg(val.z());
                }

                SendMsgToDevice(target, QString("SYNC ") + vector);

                gcodeOrder++;

                return true;
            }
        }

        if (currentCommand == "SELECT")
        {
            const QString selectedDevice = valuePairs[i + 1].trimmed().toLower();
            if (selectedDevice.contains("robot"))
                DefaultRobot = selectedDevice;
            else if (selectedDevice.contains("conveyor"))
                DefaultConveyor = selectedDevice;
            else if (selectedDevice.contains("encoder"))
                DefaultEncoder = selectedDevice;
            else if (selectedDevice.contains("slider"))
                DefaultSlider = selectedDevice;
            else if (selectedDevice.contains("device"))
                DefaultDevice = selectedDevice;
            ActiveDevice = selectedDevice;
            publishExecutionVariable("SelectedDevice", ActiveDevice);

            gcodeOrder++;

            return false;
        }

        //device0 msg;

        for (int j = 0; j < deviceNames.count(); j++)
        {
            if (currentToken.contains(deviceNames[j]))
            {
                handleSENT_TO_DEVICE(valuePairs, 0);
                return true;
            }
        }
    } // End of main for loop
    
    // Check for standalone function calls
    if (isFunctionCall(currentLine))
    {
        QStringList arguments;
        QString functionName = parseFunctionCall(currentLine, arguments);
        
        if (!functionName.isEmpty() && functionDefinitions.contains(functionName))
        {
            callFunction(functionName, arguments);
            return false;
        }
        else
        {
            faultExecution(QString("Undefined function call: %1.").arg(functionName));
            return true;
        }
    }

    // Check for function call assignment: #var = functionName(args)
    if (currentLine.contains("=") && !currentLine.contains("IF") && !currentLine.contains("FOR"))
    {
        QStringList parts = currentLine.split('=');
        if (parts.size() == 2)
        {
            QString leftPart = parts[0].trimmed();
            QString rightPart = parts[1].trimmed();
            
            // Try parse as function call regardless of spacing
            QStringList arguments;
            QString functionName = parseFunctionCall(rightPart, arguments);
            if (!functionName.isEmpty())
            {
                if (!functionDefinitions.contains(functionName))
                    preprocessGcodeScript();
                if (functionDefinitions.contains(functionName))
                {
                    if (leftPart.startsWith("#"))
                        leftPart = leftPart.mid(1);
                    callFunction(functionName, arguments, leftPart);
                    return false;
                }
            }
        }
    }
    
    // Check for simple function call (standalone)
    {
        QStringList arguments;
        QString functionName = parseFunctionCall(currentLine, arguments);
        if (!functionName.isEmpty())
        {
            if (!functionDefinitions.contains(functionName))
                preprocessGcodeScript();
            if (functionDefinitions.contains(functionName))
            {
                callFunction(functionName, arguments);
                return false;
            }
            else
            {
                // Not a known function: treat as normal line
            }
        }
    }

    return handleGCODE(transmitGcode);
}

void GcodeScript::processVARIABLE()
{
    QList<QChar> endCharList = {']', '=', '+', '-', '*', '/', '^', '%', ' ', '\n'};

    QString varName = "";
    bool isImporting = false;
    QString newLine = "";

    for (int i = 0; i < currentLine.length(); i++)
    {
        if (i < currentLine.length() && currentLine[i] == '#')
            isImporting = true;
        if (i < currentLine.length() - 1)
        {
            if (endCharList.contains(currentLine[i + 1]))
            {
                isImporting = false;
                QVariant varValue = getValueAsQVariant(varName);

            }
            else if (currentLine[i + 1] == '(')
            {
                QString paraLine = currentLine.mid(i + 1, currentLine.indexOf(')') - i);
                QStringList paras = paraLine.split(',');

                processFUNCTION(varName, paras);
            }
        }

        if (isImporting == true && i < currentLine.length())
            varName += currentLine[i];
        else if (i < currentLine.length())
            newLine += currentLine[i];
    }

    currentLine = newLine;
}

QString GcodeScript::processFUNCTION(QString funcName, QStringList paras)
{
    return "";
}

bool GcodeScript::handleGOTO(QList<QString> valuePairs, int i)
{
    bool isNumber;
    int goID = valuePairs[i + 1].toInt(&isNumber, 10);

    if (isNumber) {
        return handleGOTO_Optimized(goID);  // Use optimized O(1) version
    }

    return false;
}

bool GcodeScript::handleIF(QList<QString> valuePairs, int i)
{
    // Extract condition between IF and THEN (if present)
    QString upperLine = GScriptSyntax::maskStringsAndComments(currentLine).toUpper();
    int ifPos = upperLine.indexOf("IF");
    int thenPos = QRegularExpression("\\bTHEN\\b").match(upperLine, ifPos + 2).capturedStart();
    QString conditionStr;
    if (ifPos != -1 && thenPos != -1)
        conditionStr = currentLine.mid(ifPos + 2, thenPos - (ifPos + 2)).trimmed();
    else if (ifPos != -1)
        conditionStr = currentLine.mid(ifPos + 2).trimmed();
    else
        conditionStr = valuePairs.size() > i + 1 ? valuePairs[i + 1] : "";

    bool conditionResult = finiteNumber(calculateExpressions(conditionStr), "IF condition") != 0;
    
    // Check if there's a single-line THEN statement
    QString statement;
    if (thenPos != -1)
        statement = currentLine.mid(thenPos + 4).trimmed();
    
    // Create new IF block state
    IfBlockState newBlock(conditionResult, conditionResult, gcodeOrder);
    ifBlockStack.push(newBlock);
    
    if (!statement.isEmpty())
    {
        // Single-line IF THEN statement (backward compatibility)
        if (conditionResult)
        {
            currentLine = statement;
            ifBlockStack.pop(); // Remove the IF block as it's completed
            return findExeGcodeAndTransmit();
        }
        else
        {
            // A single-line IF is complete even when its condition is false.
            ifBlockStack.pop();
            gcodeOrder++;
            return false;
        }
    }
    else
    {
        // Multi-line IF block
        if (!conditionResult)
        {
            // Skip to next ELIF, ELSE, or ENDIF
            skipToNextConditional();
        }
        else
        {
            // Continue to next line to execute IF block
            gcodeOrder++;
        }
        return false;
    }
}

bool GcodeScript::handleVARIABLE(QList<QString> valuePairs, int i)
{

    QString varName = valuePairs.at(i).mid(1);
    QString expression = currentLine.mid(currentLine.indexOf("=") + 2);
    QString trimmedStr = expression;

    const QString literal = expression.trimmed();
    if (literal.size() >= 2 &&
        ((literal.startsWith('"') && literal.endsWith('"')) ||
         (literal.startsWith('\'') && literal.endsWith('\'')))) {
        saveVariable(varName, literal.mid(1, literal.size() - 2));
        gcodeOrder++;
        return false;
    }

    trimmedStr = trimmedStr.replace(" ", "");
    QRegularExpression rx("\\((-?\\d+(?:\\.\\d+)?),(-?\\d+(?:\\.\\d+)?),?(-?\\d+(?:\\.\\d+)?)?\\)");
    QRegularExpressionMatch match = rx.match(trimmedStr);

    // TODO: Preserve a consistent link between the two point representations.
    if (trimmedStr.startsWith("(") && match.hasMatch())
    {
        QString x = match.captured(1);
        QString y = match.captured(2);
        QString z = match.captured(3);

//        saveVariable(varName + ".X", calculateExpressions(x));
//        saveVariable(varName + ".Y", calculateExpressions(y));



        if (!z.isEmpty()) {
//            saveVariable(varName + ".Z", calculateExpressions(z));
            saveVariable(varName, QVector3D(calculateExpressions(x).toFloat(), calculateExpressions(y).toFloat(), calculateExpressions(z).toFloat()));
        }
        else
        {
            saveVariable(varName, QPointF(calculateExpressions(x).toFloat(), calculateExpressions(y).toFloat()));
        }
    }
    else
    {
        QString newVarValue = calculateExpressions(expression);

        saveVariable(varName, newVarValue);
    }

    gcodeOrder++;
    return false;
}

bool GcodeScript::handleDEFINE_SUBPROGRAM(QList<QString> valuePairs, int i)
{
    Q_UNUSED(valuePairs)
    Q_UNUSED(i)
    const int endLine = GScriptSyntax::findSubprogramEnd(gcodeList, gcodeOrder);
    if (endLine < 0) {
        faultExecution("Subprogram definition requires a top-level standalone M99 terminator.");
        return true;
    }
    gcodeOrder = endLine + 1;
    return false;
}

bool GcodeScript::handleGCODE(QString transmitGcode)
{
    // If homing (G28) is requested, set gate to wait for Position response
    {
        QString t = transmitGcode.trimmed().toUpper();
        if (t.startsWith("G28")) {
            waitForHomePosition = true;
        }
    }
    if (isConveyorGcode(transmitGcode))
    {
        gcodeOrder++;
        SendMsgToDevice(DefaultConveyor, transmitGcode);
        return true;
    }

    else if (isSlidingGcode(transmitGcode))
    {
        gcodeOrder++;
        SendMsgToDevice(DefaultSlider, transmitGcode);
        return true;
    }

    else if (isEncoderGcode(transmitGcode))
    {
        gcodeOrder++;
        SendMsgToDevice(DefaultEncoder, transmitGcode);
        return true;
    }
    else
    {
        SendMsgToDevice(ActiveDevice.isEmpty() ? DefaultRobot : ActiveDevice, transmitGcode);
        gcodeOrder += 1;
        return true;
    }

    false;
}

void GcodeScript::handleSENT_TO_DEVICE(QList<QString> valuePairs, int i)
{
    if (valuePairs.size() <= i + 1) {
        faultExecution("Explicit device command requires a command payload.");
        return;
    }
    QString msg = valuePairs[i + 1];

    QString deviceName = valuePairs.at(i).trimmed().toLower();
    for (int j = i + 2; j < valuePairs.count(); j++)
    {
        msg += QString(" ") + valuePairs[j];
    }

    if (deviceName.contains("robot"))
        DefaultRobot = deviceName;
    else if (deviceName.contains("conveyor"))
        DefaultConveyor = deviceName;
    else if (deviceName.contains("encoder"))
        DefaultEncoder = deviceName;
    else if (deviceName.contains("slider"))
        DefaultSlider = deviceName;
    else if (deviceName.contains("device"))
        DefaultDevice = deviceName;

    ActiveDevice = deviceName;

    SendMsgToDevice(deviceName, msg);

    gcodeOrder++;
}

QString GcodeScript::calculateExpressions2(QString expression)
{
    expression.replace(" ", "");

    int startIndex = 0;
    while ((startIndex = expression.lastIndexOf("[", startIndex)) != -1) {
        int endIndex = expression.indexOf("]", startIndex);
        if (startIndex != -1 && endIndex != -1) {
            QString subExpression = expression.mid(startIndex + 1, endIndex - startIndex - 1);
            QString result = calculateExpressions(subExpression);
            expression.replace(startIndex, endIndex - startIndex + 1, result);
        }
    }

    startIndex = 0;
    while ((startIndex = expression.lastIndexOf("(", startIndex)) != -1) {
        int endIndex = expression.indexOf(")", startIndex);
        if (startIndex != -1 && endIndex != -1) {
            QString subExpression = expression.mid(startIndex + 1, endIndex - startIndex - 1);
            QString result = calculateExpressions(subExpression);
            expression.replace(startIndex, endIndex - startIndex + 1, result);
        }
    }

    QStringList operators = {">=", "<=", "==", "!=", ">", "<", "*", "/", "%", "+", "-", "AND", "OR", "XOR"};

    while (true) {
        int operatorIndex = -1;
        int operatorPosition = -1;

        for (const QStringList &operatorGroup : {operators.mid(6, 3), operators.mid(9, 2), operators.mid(0, 6), operators.mid(11, 3)}) {
            for (const QString &op : operatorGroup) {
                QRegularExpression opRegex("\\b" + QRegularExpression::escape(op) + "\\b");
                int index = expression.indexOf(opRegex);
                if (index != -1 && (operatorPosition == -1 || index < operatorPosition)) {
                    operatorPosition = index;
                    operatorIndex = operators.indexOf(op);
                }
            }
            if (operatorIndex > -1) {
                break;
            }
        }

        if (operatorIndex == -1) {
            break;
        }

        QString value1S = expression.left(operatorPosition).trimmed();
        QString value2S = expression.right(expression.size() - operatorPosition - operators[operatorIndex].size()).trimmed();

        value1S = getValueAsString(value1S);
        value2S = getValueAsString(value2S);

        float value1 = value1S.toFloat();
        float value2 = value2S.toFloat();
        float result;

        switch (operatorIndex) {
            case 0: // ">="
                result = value1 >= value2;
                break;
            case 1: // "<="
                result = value1 <= value2;
                break;
            case 2: // "=="
                if (value1S.startsWith("\"") && value1S.endsWith("\"")) {
                    result = value1S == value2S;
                } else {
                    result = value1 == value2;
                }
                break;
            case 3: // "!="
                result = value1 != value2;
                break;
            case 4: // ">"
                result = value1 > value2;
                break;
            case 5: // "<"
                result = value1 < value2;
                break;
            case 6: // "*"
                result = value1 * value2;
                break;
            case 7: // "/"
                if (value2 != 0) {
                    result = value1 / value2;
                } else {
                    result = 0;
                }
                break;
            case 8: // "%"
                if (value2 != 0) {
                    result = static_cast<int>(value1) % static_cast<int>(value2);
                } else {
                    result = 0;
                }
                break;
            case 9: // "+"
                result = value1 + value2;
                break;
            case 10: // "-"
                result = value1 - value2;
                break;
            case 11: // "AND"
                result = value1 * value2;
                result = (result > 0) ? 1 : 0;
                break;
            case 12: // "OR"
                result = value1 + value2;
                result = (result > 0) ? 1 : 0;
                break;
            case 13: // "XOR"
                value1 = (value1 > 0) ? 1 : 0;
                value2 = (value2 > 0) ? 1 : 0;
                result = (value1 != value2) ? 1 : 0;
                break;
        }

        QString resultString = QString::number(result);
        expression.replace(0, expression.size(), resultString);
    }

    return expression;
}


QString GcodeScript::calculateExpressions(QString expression)
{
    expression = expression.trimmed();
    if (expression.isEmpty())
        throw GScriptEvaluationError("Expression is empty or has a missing operand.");
    QStack<QChar> delimiters;
    QChar expressionQuote;
    for (const QChar ch : expression) {
        if (!expressionQuote.isNull()) {
            if (ch == expressionQuote) expressionQuote = QChar();
            continue;
        }
        if (ch == '\'' || ch == '"') { expressionQuote = ch; continue; }
        if (ch == '(' || ch == '[') delimiters.push(ch);
        else if (ch == ')' || ch == ']') {
            if (delimiters.isEmpty() || delimiters.pop() != (ch == ')' ? '(' : '['))
                throw GScriptEvaluationError("Expression has mismatched delimiters.");
        }
    }
    if (!delimiters.isEmpty() || !expressionQuote.isNull())
        throw GScriptEvaluationError("Expression has an unclosed delimiter or string.");
    // Split on the lowest-precedence top-level operator. Choosing the rightmost
    // operator at each precedence makes subtraction/division left-associative.
    // Parentheses, function arguments, quoted strings and brackets stay intact.
    const QList<QStringList> precedence = {
        {"OR", "||"}, {"XOR", "^^"}, {"AND", "&&"},
        {"==", "!=", "<=", ">=", "EQ", "NE", "LE", "GE", "LT", "GT", "<", ">"},
        {"+", "-"}, {"*", "/", "%"}, {"^"}
    };
    for (const auto& operators : precedence) {
        int depth = 0, split = -1;
        QChar quote;
        QString operation;
        for (int at = 0; at < expression.size(); ++at) {
            const QChar ch = expression.at(at);
            if (!quote.isNull()) { if (ch == quote) quote = QChar(); continue; }
            if (ch == '\'' || ch == '"') { quote = ch; continue; }
            if (ch == '(' || ch == '[') { ++depth; continue; }
            if (ch == ')' || ch == ']') { --depth; continue; }
            if (depth != 0) continue;
            for (const QString& op : operators) {
                if (expression.mid(at, op.size()).compare(op, Qt::CaseInsensitive) != 0) continue;
                if (op.at(0).isLetter() &&
                    (at == 0 || !expression.at(at - 1).isSpace() ||
                     at + op.size() == expression.size() || !expression.at(at + op.size()).isSpace())) continue;
                if ((op == "<" || op == ">") && expression.mid(at + 1, 1) == "=") continue;
                const QString left = expression.left(at).trimmed();
                if (left.isEmpty()) continue;
                if ((op == "-" || op == "+") &&
                    (QString("+-*/%^<>=,").contains(left.back()) ||
                     ((left.back() == 'e' || left.back() == 'E') && left.size() > 1 && left.at(left.size() - 2).isDigit()))) continue;
                split = at;
                operation = op;
                at += op.size() - 1;
                break;
            }
            if (operation == "^") break; // Exponentiation is right-associative.
        }
        if (split < 0) continue;
        QString left = calculateExpressions(expression.left(split));
        // Boolean guards do not evaluate an unreachable right-hand expression.
        if ((operation == "OR" || operation == "||") && finiteNumber(left, "OR") != 0)
            return QStringLiteral("1");
        if ((operation == "AND" || operation == "&&") && finiteNumber(left, "AND") == 0)
            return QStringLiteral("0");
        QString right = calculateExpressions(expression.mid(split + operation.size()));
        bool leftNumeric = false, rightNumeric = false;
        const double a = left.toDouble(&leftNumeric), b = right.toDouble(&rightNumeric);
        const bool equality = operation == "==" || operation == "EQ" || operation == "!=" || operation == "NE";
        if (!equality && (!leftNumeric || !rightNumeric || !std::isfinite(a) || !std::isfinite(b)))
            throw GScriptEvaluationError(QString("Operator %1 requires finite numeric operands.").arg(operation));
        const bool equal = leftNumeric && rightNumeric ? a == b : left == right;
        double result = 0;
        if (operation == "OR" || operation == "||") result = a != 0 || b != 0;
        else if (operation == "XOR" || operation == "^^") result = (a != 0) != (b != 0);
        else if (operation == "AND" || operation == "&&") result = a != 0 && b != 0;
        else if (operation == "==" || operation == "EQ") result = equal;
        else if (operation == "!=" || operation == "NE") result = !equal;
        else if (operation == "<" || operation == "LT") result = a < b;
        else if (operation == ">" || operation == "GT") result = a > b;
        else if (operation == "<=" || operation == "LE") result = a <= b;
        else if (operation == ">=" || operation == "GE") result = a >= b;
        else if (operation == "+") result = a + b;
        else if (operation == "-") result = a - b;
        else if (operation == "*") result = a * b;
        else if (operation == "/" || operation == "%") {
            if (b == 0)
                throw GScriptEvaluationError("Division or modulo by zero.");
            result = operation == "/" ? a / b : std::fmod(a, b);
        }
        else if (operation == "^") result = std::pow(a, b);
        if (!std::isfinite(result))
            throw GScriptEvaluationError("Expression produced a non-finite result.");
        return QString::number(result, 'g', 12);
    }
    // Atoms and fully enclosed groups are evaluated after binary operators.
    if (expression.size() >= 2 &&
        ((expression.front() == '"' && expression.back() == '"') ||
         (expression.front() == '\'' && expression.back() == '\'')))
    {
        if (expression.indexOf(expression.front(), 1) != expression.size() - 1)
            throw GScriptEvaluationError("Unexpected text after a string literal.");
        return expression.mid(1, expression.size() - 2);
    }
    if (expression.size() >= 2 &&
        ((expression.front() == '[' && expression.back() == ']') ||
         (expression.front() == '(' && expression.back() == ')')))
        return calculateExpressions(expression.mid(1, expression.size() - 2));
    if (expression.startsWith('-') || expression.startsWith('+')) {
        bool numeric = false;
        expression.toDouble(&numeric);
        if (!numeric) {
            const double value = finiteNumber(calculateExpressions(expression.mid(1)), "Unary operator");
            return QString::number(expression.startsWith('-') ? -value : value, 'g', 12);
        }
    }
    bool numeric = false;
    const double literal = expression.toDouble(&numeric);
    if (numeric) {
        if (!std::isfinite(literal))
            throw GScriptEvaluationError("Numeric literal is not finite.");
        return expression;
    }
    static const QRegularExpression atom("^(?:#[A-Za-z0-9_][A-Za-z0-9_.]*|[A-Za-z_][A-Za-z0-9_.]*)$");
    static const QRegularExpression function("^#?[A-Za-z_][A-Za-z0-9_]*\\s*\\(.*\\)$");
    if (!atom.match(expression).hasMatch() && !function.match(expression).hasMatch())
        throw GScriptEvaluationError(QString("Malformed expression '%1'.").arg(expression));
    const QString value = getValueAsString(expression);
    bool valueNumeric = false;
    const double resolved = value.toDouble(&valueNumeric);
    if (valueNumeric && !std::isfinite(resolved))
        throw GScriptEvaluationError("Variable or function resolved to a non-finite value.");
    return value;
}

// Performance optimization: Build cache of line numbers for O(1) GOTO lookups
void GcodeScript::buildLineNumberCache()
{
    if (lineNumberCacheValid) return;  // Already built
    
    lineNumberCache.clear();
    for (int i = 0; i < gcodeList.size(); i++) {
        const QStringList tokens = gcodeList[i].split(' ', Qt::SkipEmptyParts);
        if (!tokens.isEmpty() && tokens[0].startsWith('N')) {
            bool ok;
            int lineNum = tokens[0].mid(1).toInt(&ok);
            if (ok) {
                lineNumberCache[lineNum] = i;
            }
        }
    }
    lineNumberCacheValid = true;
}

// Optimized GOTO handler using cached line numbers - O(1) instead of O(n)
bool GcodeScript::handleGOTO_Optimized(int goID)
{
    buildLineNumberCache();  // Ensure cache is built
    
    auto it = lineNumberCache.find(goID);
    if (it != lineNumberCache.end()) {
        gcodeOrder = it.value();
        return false;
    }
    return false;  // Line not found
}

QString GcodeScript::getLeftWord(QString s, int pos)
{
    if (pos < 0)
        return "0";

    if (pos > s.length() - 1)
        return "0";

    QString word;

    while (1)
    {
        if (s[pos] != ' ')
        {
            pos--;
            if (pos < 0)
            {
                return "0";
            }
        }
        else
        {
            break;
        }
    }

    for (int index = pos; index >= 0; index--)
    {
        if (s[index] != ' ')
        {
            word.insert(0, s[index]);
        }
        else if (word.length() > 0)
        {
            break;
        }
    }

    return word;
}

QString GcodeScript::getRightWord(QString s, int pos)
{
    if (pos < 0)
        return "0";

    if (pos > s.length() - 1)
        return "0";

    QString word;

    while (1)
    {
        if (s[pos] != ' ')
        {
            pos++;
            if (pos == s.length())
            {
                return "0";
            }
        }
        else
        {
            break;
        }
    }

    for (int index = pos + 1; index < s.length(); index++)
    {
        if (s[index] != ' ')
        {
            word += s[index];
        }
        else if (word.length() > 0)
        {
            break;
        }
    }

    return word;
}

QString GcodeScript::deleteSpaces(QString s)
{
    while (s.indexOf(' ') > -1)
    {
        s.replace(" ", "");
    }
    return s;
}

QString GcodeScript::formatSpaces(QString s)
{
    QRegularExpression opRegExp("(?<!\\S)(\\+|\\*|\\/|\\%|\\(|\\)|\\^)(?!\\S)");
    s.replace(opRegExp, " \\1 ");

    return s;
}

bool GcodeScript::handleJUMP(QList<QString> valuePairs, int i)
{
    // Expect: JUMP labelName
    if (valuePairs.size() <= i + 1)
        return false;

    QString label = valuePairs[i + 1].trimmed();
    if (label.startsWith('#')) label = label.mid(1);
    label = label.toUpper();

    // Ensure labels are preprocessed
    if (labelDefinitions.isEmpty())
    {
        preprocessGcodeScript();
    }

    if (labelDefinitions.contains(label))
    {
        // Jump to the line after the label marker
        gcodeOrder = labelDefinitions.value(label) + 1;
        return false;
    }
    else
    {
        // Try rescanning once more in case script changed
        preprocessGcodeScript();
        if (labelDefinitions.contains(label))
        {
            gcodeOrder = labelDefinitions.value(label) + 1;
            return false;
        }
        // Label not found: skip line
        gcodeOrder++;
        return false;
    }
}

// Split a comma-separated argument list while respecting (), [], quotes
QStringList GcodeScript::splitArgsRespectingParens(const QString& s)
{
    return GScriptSyntax::splitArguments(s);
}

QString GcodeScript::cleanedVarName(const QString& name) const
{
    QString n = name;
    if (n.startsWith('#')) n = n.mid(1);
    return n.trimmed();
}

bool GcodeScript::tryGenerateMoveShortcut(const QStringList& tokens, QString& outGcode)
{
    if (tokens.isEmpty()) {
        return false;
    }

    QString command = tokens[0].trimmed().toUpper();
    if (command != "MOVE" && command != "MOVETO") {
        return false;
    }
    if (tokens.size() < 2) {
        return false;
    }

    QVector3D target;
    if (!resolvePointReference(tokens[1], target)) {
        return false;
    }

    double feedValue = -1.0;
    for (int i = 2; i < tokens.size(); ++i) {
        QString token = tokens[i].trimmed();
        if (token.isEmpty()) {
            continue;
        }
        if (token.startsWith(';')) {
            break;
        }
        if (token.startsWith("F", Qt::CaseInsensitive)) {
            QString feedExpr = token.mid(1).trimmed();
            if (feedExpr.isEmpty() && i + 1 < tokens.size()) {
                feedExpr = tokens[++i].trimmed();
            }
            if (!feedExpr.isEmpty()) {
                feedExpr.remove('[').remove(']');
                QString evaluated = calculateExpressions(feedExpr);
                bool ok = false;
                double value = evaluated.toDouble(&ok);
                if (ok && value > 0) {
                    feedValue = value;
                }
            }
        }
    }

    QString gcode = QString("G01 X%1 Y%2 Z%3")
                        .arg(target.x(), 0, 'f', 3)
                        .arg(target.y(), 0, 'f', 3)
                        .arg(target.z(), 0, 'f', 3);
    if (feedValue > 0) {
        gcode += QString(" F%1").arg(feedValue, 0, 'f', 3);
    }

    outGcode = gcode;
    return true;
}

bool GcodeScript::resolvePointReference(const QString& token, QVector3D& outVec) const
{
    QString trimmed = token.trimmed();
    if (trimmed.isEmpty()) {
        return false;
    }

    if (trimmed.startsWith('#')) {
        QString varName = cleanedVarName(trimmed);
        QVariant value = VariableManager::instance().getVarScoped(ProjectName, varName, QVariant());
        return variantToVector3D(value, outVec);
    }

    return parseVectorString(trimmed, outVec);
}

bool GcodeScript::variantToVector3D(const QVariant& value, QVector3D& outVec) const
{
    if (!value.isValid()) {
        return false;
    }

    if (value.canConvert<QVector3D>()) {
        outVec = value.value<QVector3D>();
        return true;
    }

    if (value.canConvert<QPointF>()) {
        QPointF point = value.toPointF();
        outVec = QVector3D(point.x(), point.y(), 0.0f);
        return true;
    }

    if (value.canConvert<QString>()) {
        return parseVectorString(value.toString(), outVec);
    }

    if (value.type() == QVariant::List) {
        QVariantList list = value.toList();
        if (list.size() >= 3) {
            bool okX = false, okY = false, okZ = false;
            double x = list[0].toDouble(&okX);
            double y = list[1].toDouble(&okY);
            double z = list[2].toDouble(&okZ);
            if (okX && okY && okZ) {
                outVec = QVector3D(x, y, z);
                return true;
            }
        }
    }

    return false;
}

bool GcodeScript::parseVectorString(const QString& text, QVector3D& outVec) const
{
    QString cleaned = text.trimmed();
    if (cleaned.startsWith("(") && cleaned.endsWith(")")) {
        cleaned = cleaned.mid(1, cleaned.length() - 2);
    }

    QStringList parts = cleaned.split(QRegularExpression("[,\\s]+"), Qt::SkipEmptyParts);
    if (parts.size() < 3) {
        return false;
    }

    bool okX = false, okY = false, okZ = false;
    double x = parts[0].toDouble(&okX);
    double y = parts[1].toDouble(&okY);
    double z = parts[2].toDouble(&okZ);
    if (okX && okY && okZ) {
        outVec = QVector3D(x, y, z);
        return true;
    }

    return false;
}

// Advanced whitespace normalization for better performance and cleaner parsing
QString GcodeScript::normalizeWhitespace(const QString& line)
{
    // Temporarily disabled - using simple processing instead
    return line;
}

// Preprocess entire gcode script: collect all FUNCTION definitions for later lookup
void GcodeScript::preprocessGcodeScript()
{
    functionDefinitions.clear();
    labelDefinitions.clear();

    for (int order = 0; order < gcodeList.size(); order++)
    {
        QString line = gcodeList[order].trimmed();
        if (line.isEmpty() || line.startsWith(';'))
            continue;

        line = stripInlineComment(line).trimmed();

        QStringList tokens = line.split(' ', Qt::SkipEmptyParts);
        if (tokens.isEmpty())
            continue;

        QString firstToken = tokens[0].toUpper();
        // Skip line numbers like N10
        if (firstToken.startsWith("N") && firstToken.length() > 1)
        {
            if (tokens.size() > 1)
                firstToken = tokens[1].toUpper();
            else
                continue;
        }

        if (firstToken == "FUNCTION")
        {
            // Derive function name and parameters similarly to handleFUNCTION
            QString functionName;
            QStringList parameters;

            // Case 1: FUNCTION functionName or FUNCTION functionName(params)
            if (tokens.size() >= 2)
            {
                functionName = tokens[1];
                // Trim any parameter tail if present in the same token
                int parIdx = functionName.indexOf('(');
                if (parIdx != -1)
                    functionName = functionName.left(parIdx).trimmed();
            }

            // Case 2: Parameters located elsewhere in the line
            if (line.contains('('))
            {
                int openParen = line.indexOf('(');
                int closeParen = line.lastIndexOf(')');
                if (openParen != -1 && closeParen != -1 && closeParen > openParen)
                {
                    // If functionName not yet set with parentheses part, extract before '('
                    if (functionName.isEmpty())
                    {
                        // Find token immediately before '('
                        int nameEnd = openParen;
                        int nameStart = line.lastIndexOf(' ', nameEnd - 1);
                        if (nameStart == -1) nameStart = 0; else nameStart += 1;
                        functionName = line.mid(nameStart, nameEnd - nameStart).trimmed();
                    }

                    QString paramStr = line.mid(openParen + 1, closeParen - openParen - 1).trimmed();
                    if (!paramStr.isEmpty())
                    {
                        const QStringList paramTokens = splitArgsRespectingParens(paramStr);
                        for (QString p : paramTokens)
                        {
                            p = p.trimmed();
                            if (p.startsWith('#')) p = p.mid(1);
                            if (!p.isEmpty()) parameters.append(p);
                        }
                    }
                }
            }

            if (functionName.startsWith('#')) functionName = functionName.mid(1);
            functionName = functionName.toUpper();

            if (!functionName.isEmpty())
            {
                // find matching ENDFUNCTION line
                int endLine = -1;
                for (int i = order + 1; i < gcodeList.size(); ++i) {
                    QString l = gcodeList[i].trimmed();
                    if (l.startsWith(';')) continue;
                    if (GScriptSyntax::command(GScriptSyntax::stripComment(l)) == "ENDFUNCTION") { endLine = i; break; }
                }
                SimpleFunctionDef newFunction(functionName, parameters, order, endLine);
                functionDefinitions[functionName] = newFunction;
            }
        }
        else if (firstToken == "LABEL")
        {
            // LABEL name
            if (tokens.size() >= 2)
            {
                QString name = tokens[1].trimmed();
                if (name.startsWith('#')) name = name.mid(1);
                name = name.toUpper();
                if (!name.isEmpty())
                {
                    labelDefinitions[name] = order;
                }
            }
        }
    }
}

// Evaluate built-in math functions and supported helpers with full expression args
float GcodeScript::EvaluateFunctionToFloat(QString expression)
{
    if (expression.isEmpty()) return NULL_NUMBER;

    int p1 = expression.indexOf('(');
    int p2 = expression.lastIndexOf(')');
    if (p1 == -1 || p2 == -1 || p2 <= p1) return NULL_NUMBER;

    int nameStart = (expression.at(0) == '#') ? 1 : 0;
    QString functionName = expression.mid(nameStart, p1 - nameStart).trimmed();
    QString argsStr = expression.mid(p1 + 1,  p2 - p1 - 1);

    QStringList values;
    if (!argsStr.trimmed().isEmpty())
        values = splitArgsRespectingParens(argsStr);
    const QString fname = functionName.toLower();
    static const QHash<QString, QPair<int, int>> arities = {
        {"sin", {1, 1}}, {"cos", {1, 1}}, {"tan", {1, 1}}, {"atan", {1, 1}},
        {"atan2", {2, 2}}, {"sqrt", {1, 1}}, {"abs", {1, 1}}, {"round", {1, 1}},
        {"floor", {1, 1}}, {"ceil", {1, 1}}, {"min", {2, 2}}, {"max", {2, 2}},
        {"pow", {2, 2}}, {"log", {1, 1}}, {"log10", {1, 1}}, {"exp", {1, 1}},
        {"cloudpointaddcalibration", {6, 8}}, {"cloudpointtransformx", {3, 4}},
        {"cloudpointtransformy", {3, 4}}, {"cloudpointtransformz", {3, 4}},
        {"cloudpointgetconfidence", {3, 4}}, {"cloudpointgeterror", {3, 4}},
        {"cloudpointgetcount", {0, 0}}, {"cloudpointisvalid", {0, 0}},
        {"cloudpointclear", {0, 0}}, {"cloudpointbuildgrid", {0, 1}},
        {"cloudpointvalidate", {0, 1}}, {"cloudpointsave", {0, 1}},
        {"cloudpointload", {0, 1}}, {"cloudpointexport", {0, 1}},
        {"cloudpointimport", {0, 1}}, {"cloudpointremove", {1, 1}},
        {"cloudpointupdate", {7, 8}}, {"cloudpointgetimagex", {1, 1}},
        {"cloudpointgetimagey", {1, 1}}, {"cloudpointgetimagez", {1, 1}},
        {"cloudpointgetrealx", {1, 1}}, {"cloudpointgetrealy", {1, 1}},
        {"cloudpointgetrealz", {1, 1}}, {"cloudpointgetpointconfidence", {1, 1}},
        {"cloudpointgetpointerror", {1, 1}}
    };
    if (!arities.contains(fname))
        throw GScriptEvaluationError(QString("Unknown expression function '%1'.").arg(functionName));
    const auto arity = arities.value(fname);
    if (values.size() < arity.first || values.size() > arity.second)
        throw GScriptEvaluationError(QString("Function %1 expects %2 to %3 arguments; received %4.")
                                         .arg(functionName).arg(arity.first).arg(arity.second).arg(values.size()));
    const int suppliedCount = values.size();
    for (int i = 0; i < suppliedCount; ++i) {
        values[i] = calculateExpressions(values.at(i).trimmed());
        const bool textArgument = fname == "cloudpointsave" || fname == "cloudpointload" ||
            fname == "cloudpointexport" || fname == "cloudpointimport" ||
            (fname == "cloudpointaddcalibration" && i == 7);
        if (!textArgument) {
            const double number = finiteNumber(values[i], functionName);
            if (std::abs(number) > std::numeric_limits<float>::max())
                throw GScriptEvaluationError(QString("Argument exceeds the numeric range of %1.").arg(functionName));
        }
    }
    values.append("0");
    values.append("0");

    if (fname == "sin") return sin((values[0].toFloat()/180) * M_PI);
    if (fname == "cos") return cos((values[0].toFloat()/180) * M_PI);
    if (fname == "tan") return tan((values[0].toFloat()/180) * M_PI);
    if (fname == "atan") return atan(values[0].toFloat()) * 180 / M_PI;
    if (fname == "atan2") return atan2(values[0].toFloat(), values.at(1).toFloat()) * 180 / M_PI;
    if (fname == "sqrt") return sqrt(values[0].toFloat());
    if (fname == "abs") return fabs(values[0].toFloat());
    if (fname == "round") return round(values[0].toFloat());
    if (fname == "floor") return floor(values[0].toFloat());
    if (fname == "ceil") return ceil(values[0].toFloat());
    if (fname == "min") return qMin(values[0].toFloat(), values[1].toFloat());
    if (fname == "max") return qMax(values[0].toFloat(), values[1].toFloat());
    if (fname == "pow") return pow(values[0].toFloat(), values[1].toFloat());
    if (fname == "log") return log(values[0].toFloat());
    if (fname == "log10") return log10(values[0].toFloat());
    if (fname == "exp") return exp(values[0].toFloat());

    // Cloud mapping helpers: mirror existing GetResultOfMathFunction support
    if (fname == "cloudpointaddcalibration")
        return cloudPointAddCalibration(values[0].toFloat(), values[1].toFloat(), values[2].toFloat(), values[3].toFloat(), values[4].toFloat(), values[5].toFloat(), suppliedCount>6?values[6].toFloat():1.0f, suppliedCount>7?values[7]:"");
    if (fname == "cloudpointtransformx")
        return cloudPointTransformX(values[0].toFloat(), values[1].toFloat(), values[2].toFloat(), suppliedCount>3?values[3].toInt():1);
    if (fname == "cloudpointtransformy")
        return cloudPointTransformY(values[0].toFloat(), values[1].toFloat(), values[2].toFloat(), suppliedCount>3?values[3].toInt():1);
    if (fname == "cloudpointtransformz")
        return cloudPointTransformZ(values[0].toFloat(), values[1].toFloat(), values[2].toFloat(), suppliedCount>3?values[3].toInt():1);
    if (fname == "cloudpointgetconfidence")
        return cloudPointGetConfidence(values[0].toFloat(), values[1].toFloat(), values[2].toFloat(), suppliedCount>3?values[3].toInt():1);
    if (fname == "cloudpointgeterror")
        return cloudPointGetError(values[0].toFloat(), values[1].toFloat(), values[2].toFloat(), suppliedCount>3?values[3].toInt():1);
    if (fname == "cloudpointgetcount") return cloudPointGetCount();
    if (fname == "cloudpointisvalid") return cloudPointIsValid();
    if (fname == "cloudpointclear") return cloudPointClear();
    if (fname == "cloudpointbuildgrid") return cloudPointBuildGrid(suppliedCount>0?values[0].toFloat():10.0f);
    if (fname == "cloudpointvalidate") return cloudPointValidate(suppliedCount>0?values[0].toFloat():0.2f);
    if (fname == "cloudpointsave") return cloudPointSave(suppliedCount>0?values[0]:"");
    if (fname == "cloudpointload") return cloudPointLoad(suppliedCount>0?values[0]:"");
    if (fname == "cloudpointexport") return cloudPointExport(suppliedCount>0?values[0]:"CloudMapping");
    if (fname == "cloudpointimport") return cloudPointImport(suppliedCount>0?values[0]:"CloudMapping");
    if (fname == "cloudpointremove") return cloudPointRemove(values[0].toInt());
    if (fname == "cloudpointupdate") return cloudPointUpdate(values[0].toInt(), values[1].toFloat(), values[2].toFloat(), values[3].toFloat(), values[4].toFloat(), values[5].toFloat(), values[6].toFloat(), suppliedCount>7?values[7].toFloat():1.0f);
    if (fname == "cloudpointgetimagex") return cloudPointGetImageX(values[0].toInt());
    if (fname == "cloudpointgetimagey") return cloudPointGetImageY(values[0].toInt());
    if (fname == "cloudpointgetimagez") return cloudPointGetImageZ(values[0].toInt());
    if (fname == "cloudpointgetrealx") return cloudPointGetRealX(values[0].toInt());
    if (fname == "cloudpointgetrealy") return cloudPointGetRealY(values[0].toInt());
    if (fname == "cloudpointgetrealz") return cloudPointGetRealZ(values[0].toInt());
    if (fname == "cloudpointgetpointconfidence") return cloudPointGetPointConfidence(values[0].toInt());
    if (fname == "cloudpointgetpointerror") return cloudPointGetPointError(values[0].toInt());

    return NULL_NUMBER;
}

bool GcodeScript::isNotNegative(QString s)
{
    bool isNumeric = false;
    s.toDouble(&isNumeric);

    return !isNumeric;
}

QString GcodeScript::getValueAsString(QString name)
{
    // Prefer function-local variables (simple names only)
    {
        QString localKey = name;
        localKey.replace("#", "");
        localKey = localKey.trimmed();
        if (!localKey.contains('.') && !callStack.isEmpty()) {
            if (callStack.top().locals.contains(localKey)) {
                QVariant v = callStack.top().locals.value(localKey);
                emit CatchVariable2(localKey, v);
                return v.toString();
            }
        }
    }
    
    if (name.contains('(') && name.contains(')'))
    {
        float result = EvaluateFunctionToFloat(name);
        if (!std::isfinite(result))
            throw GScriptEvaluationError(QString("Function produced a non-finite result: %1.").arg(name));
        if (result != NULL_NUMBER)
        {
            return QString::number(result);
        }
    }

    name = name.replace("#", "");

    QString fullName = name;

    fullName = fullName.replace(" ", "");

    if (fullName.endsWith(".X", Qt::CaseInsensitive) ||
        fullName.endsWith(".Y", Qt::CaseInsensitive) ||
        fullName.endsWith(".Z", Qt::CaseInsensitive))
    {
        QString baseName = fullName.left(fullName.length() - 2);
        QVariant var = getValueAsQVariant(baseName);

        // Support QVector3D for .X/.Y/.Z
        if (var.canConvert<QVector3D>())
        {
            QVector3D v = var.value<QVector3D>();
            emit CatchVariable2(baseName, var);

            if (fullName.endsWith(".X", Qt::CaseInsensitive))
            {
                return QString::number(v.x());
            }
            if (fullName.endsWith(".Y", Qt::CaseInsensitive))
            {
                return QString::number(v.y());
            }
            // .Z
            return QString::number(v.z());
        }

        // Backward-compatible: QPointF supports .X/.Y
        if (var.canConvert<QPointF>())
        {
            QPointF p = var.value<QPointF>();
            emit CatchVariable2(baseName, var);

            if (fullName.endsWith(".X", Qt::CaseInsensitive))
            {
                return QString::number(p.x());
            }
            if (fullName.endsWith(".Y", Qt::CaseInsensitive))
            {
                return QString::number(p.y());
            }
            // .Z on QPointF defaults to 0
            return QString::number(0.0f);
        }
    }

    if (VariableManager::instance().containsFullKeyScoped(ProjectName, fullName))
    {
        QVariant var = VariableManager::instance().getVarScoped(ProjectName, fullName);
        emit CatchVariable2(name, var);
        return var.toString();
    }
    else
    {
        return name;
    }
}

QVariant GcodeScript::getValueAsQVariant(QString key)
{
    // Prefer function-local variables (simple names only)
    {
        QString localKey = key;
        localKey.replace("#", "");
        localKey = localKey.trimmed();
        if (!localKey.contains('.') && !callStack.isEmpty()) {
            if (callStack.top().locals.contains(localKey)) {
                QVariant v = callStack.top().locals.value(localKey);
                emit CatchVariable2(localKey, v);
                return v;
            }
        }
    }
    key = key.replace("#", "");
//    name = name.replace("_", ".");

    QString fullName = key;

    fullName = fullName.replace(" ", "");

    return VariableManager::instance().getVarScoped(ProjectName, fullName);
}

void GcodeScript::updateVariables(QString str)
{
    QStringList pairs = str.split(';');

    foreach(QString pair, pairs)
    {
        QStringList map = pair.split("=");

        if (map.count() != 2)
        {
            continue;
        }

        saveVariable(map[0], map[1]);

    }
}

void GcodeScript::saveVariable(QString name, QString value)
{
//    name = name.replace("_", ".");

    name = cleanedVarName(name);
    if (!name.contains('.') && !callStack.isEmpty() && callStack.top().locals.contains(name)) {
        callStack.top().locals[name] = value;
        emit CatchVariable2(name, value);
        return;
    }

    emit CatchVariable2(name, value);

    VariableManager::instance().updateVarScoped(ProjectName, name, value);
}

void GcodeScript::saveVariable(QString name, QVariant value)
{
    name = cleanedVarName(name);
    if (!name.contains('.') && !callStack.isEmpty() && callStack.top().locals.contains(name)) {
        callStack.top().locals[name] = value;
        emit CatchVariable2(name, value);
        return;
    }
    emit CatchVariable2(name, value);

    VariableManager::instance().updateVarScoped(ProjectName, name, value);
}

void GcodeScript::saveRuntimeVariable(const QString& name, const QVariant& value)
{
    emit CatchVariable2(name, value);
    VariableManager::instance().updateVarScoped(
        ProjectName, name, value, VariableManager::Persistence::Runtime);
}

void GcodeScript::processResponse(QString response)
{
    QRegularExpression pattern("^I\\d+\\sV\\d+$");

    QRegularExpressionMatch match = pattern.match(response);
    if (match.hasMatch())
    {
        QString value1 = response.split(' ')[0];
        QString value2 = response.split(' ')[1].split('V')[1];
        saveVariable(value1, value2);
    }
    else
    {

    }
}

bool GcodeScript::checkExclution(QString response)
{
    // Normalize
    const QString r = response.trimmed();

    // 1) Ignore empty and echo responses
    if (r.isEmpty() || r == transmitMsg)
        return true;

    // 2) If homing gate is active, ignore intermediate responses until Position data arrives
    if (waitForHomePosition)
    {
        // Position response is typically comma-separated values
        if (r.count(',') < 2)
            return true; // ignore until Position
    }

    // 3) Common OK ack should not be excluded
    if (r.compare("ok", Qt::CaseInsensitive) == 0)
        return false;

    // 4) Generic error handling: block progression on error messages
    if (r.contains("error", Qt::CaseInsensitive))
    {
        saveRuntimeVariable("LastError", r);
        return true; // do not proceed automatically on errors
    }

    // Default: do not exclude
    return false;
}

bool GcodeScript::handleELIF(QList<QString> valuePairs, int i)
{
    if (ifBlockStack.isEmpty())
    {
        // ELIF without IF - error, skip line
        gcodeOrder++;
        return false;
    }
    
    IfBlockState& currentBlock = ifBlockStack.top();
    
    // If any previous condition was met, skip this ELIF
    if (currentBlock.conditionMet)
    {
        skipToNextConditional();
        return false;
    }
    
    // Evaluate ELIF condition (between ELIF and THEN if present)
    QString upperLine = GScriptSyntax::maskStringsAndComments(currentLine).toUpper();
    int elifPos = upperLine.indexOf("ELIF");
    int thenPos = QRegularExpression("\\bTHEN\\b").match(upperLine, elifPos + 4).capturedStart();
    QString conditionStr;
    if (elifPos != -1 && thenPos != -1)
        conditionStr = currentLine.mid(elifPos + 4, thenPos - (elifPos + 4)).trimmed();
    else if (elifPos != -1)
        conditionStr = currentLine.mid(elifPos + 4).trimmed();
    else
        conditionStr = valuePairs.size() > i + 1 ? valuePairs[i + 1] : "";
    bool conditionResult = finiteNumber(calculateExpressions(conditionStr), "ELIF condition") != 0;
    
    // Single-line THEN statement extraction
    QString statement;
    if (thenPos != -1)
        statement = currentLine.mid(thenPos + 4).trimmed();
    
    if (!statement.isEmpty())
    {
        // Single-line ELIF THEN statement
        if (conditionResult)
        {
            currentBlock.conditionMet = true;
            currentBlock.insideBlock = true;
            currentLine = statement;
            return findExeGcodeAndTransmit();
        }
        else
        {
            gcodeOrder++;
            return false;
        }
    }
    else
    {
        // Multi-line ELIF block
        if (conditionResult)
        {
            currentBlock.conditionMet = true;
            currentBlock.insideBlock = true;
            gcodeOrder++;
        }
        else
        {
            skipToNextConditional();
        }
        return false;
    }
}

bool GcodeScript::handleELSE(QList<QString> valuePairs, int i)
{
    if (ifBlockStack.isEmpty())
    {
        // ELSE without IF - error, skip line
        gcodeOrder++;
        return false;
    }
    
    IfBlockState& currentBlock = ifBlockStack.top();
    
    // Check if there's a single-line ELSE statement
    QString statement = GScriptSyntax::inlineStatement(currentLine);
    
    if (!statement.isEmpty())
    {
        // Single-line ELSE statement
        if (!currentBlock.conditionMet)
        {
            currentBlock.conditionMet = true;
            currentBlock.insideBlock = true;
            currentLine = statement;
            return findExeGcodeAndTransmit();
        }
        else
        {
            gcodeOrder++;
            return false;
        }
    }
    else
    {
        // Multi-line ELSE block
        if (!currentBlock.conditionMet)
        {
            currentBlock.conditionMet = true;
            currentBlock.insideBlock = true;
            gcodeOrder++;
        }
        else
        {
            // Skip to ENDIF
            skipToNextConditional();
        }
        return false;
    }
}

bool GcodeScript::handleENDIF(QList<QString> valuePairs, int i)
{
    if (ifBlockStack.isEmpty())
    {
        // ENDIF without IF - error, skip line
        gcodeOrder++;
        return false;
    }
    
    // Pop the current IF block
    ifBlockStack.pop();
    gcodeOrder++;
    return false;
}

void GcodeScript::skipToNextConditional()
{
    int nestedLevel = 1;
    int originalOrder = gcodeOrder;
    
    for (int i = gcodeOrder + 1; i < gcodeList.size(); i++)
    {
        QString line = gcodeList[i].trimmed();
        if (line.isEmpty() || line.startsWith(";"))
            continue;
            
        QStringList tokens = line.split(' ', Qt::SkipEmptyParts);
        if (tokens.isEmpty())
            continue;
            
        QString firstToken = tokens[0].toUpper();
        
        // Skip line numbers (N10, N20, etc.)
        if (firstToken.startsWith("N") && firstToken.length() > 1)
        {
            if (tokens.size() > 1)
            {
                firstToken = tokens[1].toUpper();
            }
            else
            {
                continue;
            }
        }
        
        if (firstToken == "IF")
        {
            nestedLevel++;
        }
        else if (firstToken == "ENDIF")
        {
            nestedLevel--;
            if (nestedLevel == 0)
            {
                gcodeOrder = i;
                return;
            }
        }
        else if (nestedLevel == 1 && (firstToken == "ELIF" || firstToken == "ELSE"))
        {
            gcodeOrder = i;
            return;
        }
    }
    
    // If we reach here, no matching conditional found
    gcodeOrder = gcodeList.size();
}

bool GcodeScript::handleFOR(QList<QString> valuePairs, int i)
{
    if (valuePairs.size() < (i + 2))
        return false;
    
    // Check for FOREACH syntax: FOR EACH item IN list
    if (valuePairs[i + 1].toUpper() == "EACH" && valuePairs.size() >= (i + 5))
    {
        if (valuePairs[i + 3].toUpper() == "IN")
        {
            QString counterVar = valuePairs[i + 2];
            QString listName = valuePairs[i + 4];
            
            // Remove # from variable name if present
            if (counterVar.startsWith("#"))
                counterVar = counterVar.mid(1);
            if (listName.startsWith("#"))
                listName = listName.mid(1);
                
            // Find ENDFOR line
            int endForLine = findEndForLine(gcodeOrder);
            if (endForLine == -1)
            {
                // ENDFOR not found - skip this FOR
                gcodeOrder++;
                return false;
            }
            
            // Create FOREACH loop state
            ForLoopState newLoop(FOREACH_FOR, counterVar, listName, gcodeOrder);
            newLoop.endForLine = endForLine;
            newLoop.nestingOrder = ++nextLoopNestingOrder;
            newLoop.ifDepth = ifBlockStack.size();
            newLoop.switchDepth = switchCaseStack.size();
            forLoopStack.push(newLoop);
            
            // Start first iteration
            return executeForLoopIteration();
        }
    }
    
    // Check for numeric FOR syntax: FOR var = start TO end [STEP step]
    const auto numericFor = QRegularExpression(
        "^FOR\\s+(#?[A-Za-z0-9_][A-Za-z0-9_.]*)\\s*=\\s*(.+?)\\s+TO\\s+(.+?)(?:\\s+STEP\\s+(.+))?$",
        QRegularExpression::CaseInsensitiveOption).match(currentLine);
    if (numericFor.hasMatch())
    {
        QString counterVar = numericFor.captured(1);
        
        {
            // Remove # from variable name if present
            if (counterVar.startsWith("#"))
                counterVar = counterVar.mid(1);
            
            QString startStr = numericFor.captured(2);
            QString endStr = numericFor.captured(3);
            QString stepStr = numericFor.captured(4).isEmpty() ? QStringLiteral("1") : numericFor.captured(4);
            
            // Evaluate expressions
            float startValue = finiteNumber(calculateExpressions(startStr), "FOR start");
            float endValue = finiteNumber(calculateExpressions(endStr), "FOR limit");
            float stepValue = finiteNumber(calculateExpressions(stepStr), "FOR step");
            
            // Validate step value
            if (stepValue == 0 || !std::isfinite(startValue) || !std::isfinite(endValue) || !std::isfinite(stepValue))
            {
                throw GScriptEvaluationError("FOR requires finite bounds and a non-zero finite step.");
            }
            
            // Find ENDFOR line
            int endForLine = findEndForLine(gcodeOrder);
            if (endForLine == -1)
            {
                // ENDFOR not found - skip this FOR
                gcodeOrder++;
                return false;
            }
            
            // Create numeric FOR loop state
            ForLoopState newLoop(NUMERIC_FOR, counterVar, startValue, endValue, stepValue, gcodeOrder);
            newLoop.endForLine = endForLine;
            newLoop.nestingOrder = ++nextLoopNestingOrder;
            newLoop.ifDepth = ifBlockStack.size();
            newLoop.switchDepth = switchCaseStack.size();
            forLoopStack.push(newLoop);
            
            // Check if loop should run at least once
            bool shouldRun = false;
            if (stepValue > 0)
            {
                shouldRun = (startValue <= endValue);
            }
            else
            {
                shouldRun = (startValue >= endValue);
            }
            
            if (shouldRun)
            {
                // Set initial counter value and start first iteration
                saveVariable(counterVar, QString::number(startValue));

                gcodeOrder++;
                return false;
            }
            else
            {
                // Skip loop - go to ENDFOR
                forLoopStack.pop();
                gcodeOrder = endForLine + 1;
                return false;
            }
        }
    }
    
    throw GScriptEvaluationError("Invalid FOR syntax.");
}

bool GcodeScript::handleENDFOR(QList<QString> valuePairs, int i)
{
    if (forLoopStack.isEmpty())
    {
        // ENDFOR without FOR - error, skip line
        gcodeOrder++;
        return false;
    }
    
    ForLoopState& currentLoop = forLoopStack.top();
    
    if (currentLoop.type == NUMERIC_FOR)
    {
        // Update counter for next iteration
        const float nextValue = currentLoop.currentValue + currentLoop.stepValue;
        if (!std::isfinite(nextValue) || nextValue == currentLoop.currentValue)
            throw GScriptEvaluationError("FOR counter cannot advance within its numeric range.");
        currentLoop.currentValue = nextValue;
        
        // Check if loop should continue with the updated counter
        bool continueLoop = false;
        if (currentLoop.stepValue > 0)
        {
            continueLoop = (currentLoop.currentValue <= currentLoop.endValue);
        }
        else
        {
            continueLoop = (currentLoop.currentValue >= currentLoop.endValue);
        }
        

        if (continueLoop)
        {
            // Continue loop - update counter variable and jump back to start
            saveVariable(currentLoop.counterVar, QString::number(currentLoop.currentValue));
            forLoopStack.top() = currentLoop; // Update the stack

            gcodeOrder = currentLoop.startLine + 1;
            return false;
        }
        else
        {
            // Loop finished - pop from stack and continue
            forLoopStack.pop();
            gcodeOrder++;
            return false;
        }
    }
    else if (currentLoop.type == FOREACH_FOR)
    {
        // Move to next item in list
        currentLoop.currentIndex++;
        
        // Check if there are more objects
        QString objectVar = currentLoop.listName + "." + QString::number(currentLoop.currentIndex) + ".X";
        QString objectExists = getValueAsString(objectVar);
        
        if (objectExists != objectVar && objectExists != "NULL" && !objectExists.isEmpty())
        {
            // Continue loop with next object
            forLoopStack.top() = currentLoop; // Update the stack
            return executeForLoopIteration();
        }
        else
        {
            // Loop finished - pop from stack and continue
            forLoopStack.pop();
            gcodeOrder++;
            return false;
        }
    }
    
    // Should never reach here
    gcodeOrder++;
    return false;
}

bool GcodeScript::executeForLoopIteration()
{
    if (forLoopStack.isEmpty())
        return false;
        
    ForLoopState& currentLoop = forLoopStack.top();
    
    if (currentLoop.type == FOREACH_FOR)
    {
        // Set loop variable to current object index
        saveVariable(currentLoop.counterVar, QString::number(currentLoop.currentIndex));
        
        // Set convenience variables for current object
        QString objectPrefix = currentLoop.listName + "." + QString::number(currentLoop.currentIndex);
        QString currentObjPrefix = currentLoop.counterVar + "_current";
        
        // Copy object properties to current object variables
        saveVariable(currentObjPrefix + "_X", getValueAsString(objectPrefix + ".X"));
        saveVariable(currentObjPrefix + "_Y", getValueAsString(objectPrefix + ".Y"));
        saveVariable(currentObjPrefix + "_Z", getValueAsString(objectPrefix + ".Z"));
        saveVariable(currentObjPrefix + "_W", getValueAsString(objectPrefix + ".W"));
        saveVariable(currentObjPrefix + "_L", getValueAsString(objectPrefix + ".L"));
        saveVariable(currentObjPrefix + "_A", getValueAsString(objectPrefix + ".A"));
        
        // Start executing loop body
        gcodeOrder = currentLoop.startLine + 1;
        return false;
    }
    
    return false;
}

int GcodeScript::findEndForLine(int startLine)
{
    int nestedLevel = 1;
    
    for (int i = startLine + 1; i < gcodeList.size(); i++)
    {
        QString line = gcodeList[i].trimmed();
        if (line.isEmpty() || line.startsWith(";"))
            continue;
            
        QStringList tokens = line.split(' ', Qt::SkipEmptyParts);
        if (tokens.isEmpty())
            continue;
            
        QString firstToken = tokens[0].toUpper();
        
        // Skip line numbers (N10, N20, etc.)
        if (firstToken.startsWith("N") && firstToken.length() > 1)
        {
            if (tokens.size() > 1)
            {
                firstToken = tokens[1].toUpper();
            }
            else
            {
                continue;
            }
        }
        
        if (firstToken == "FOR")
        {
            nestedLevel++;
        }
        else if (firstToken == "ENDFOR")
        {
            nestedLevel--;
            if (nestedLevel == 0)
            {
                return i;
            }
        }
    }
    
    return -1; // ENDFOR not found
}

void GcodeScript::skipToEndFor()
{
    int endForLine = findEndForLine(gcodeOrder);
    if (endForLine != -1)
    {
        gcodeOrder = endForLine;
    }
    else
    {
        gcodeOrder = gcodeList.size();
    }
}

bool GcodeScript::handleWHILE(QList<QString> valuePairs, int i)
{
    Q_UNUSED(valuePairs)
    Q_UNUSED(i)
    const QRegularExpressionMatch match = QRegularExpression(
        "^\\s*WHILE\\s+(.+)$", QRegularExpression::CaseInsensitiveOption).match(currentLine);
    if (!match.hasMatch()) {
        faultExecution("WHILE requires a condition.");
        return true;
    }

    const int endLine = findEndWhileLine(gcodeOrder);
    if (endLine < 0) {
        faultExecution("WHILE has no matching ENDWHILE.");
        return true;
    }

    const QString condition = match.captured(1).trimmed();
    const bool conditionResult = finiteNumber(calculateExpressions(condition), "WHILE condition") != 0.0;
    const bool sameLoop = !whileLoopStack.isEmpty() &&
                          whileLoopStack.top().startLine == gcodeOrder;
    if (!conditionResult) {
        if (sameLoop)
            whileLoopStack.pop();
        gcodeOrder = endLine + 1;
        return false;
    }

    if (!sameLoop) {
        WhileLoopState state(condition, gcodeOrder);
        state.endWhileLine = endLine;
        state.nestingOrder = ++nextLoopNestingOrder;
        state.ifDepth = ifBlockStack.size();
        state.switchDepth = switchCaseStack.size();
        whileLoopStack.push(state);
    } else {
        whileLoopStack.top().condition = condition;
        whileLoopStack.top().endWhileLine = endLine;
    }
    gcodeOrder++;
    return false;
}

bool GcodeScript::handleENDWHILE(QList<QString> valuePairs, int i)
{
    Q_UNUSED(valuePairs)
    Q_UNUSED(i)
    if (whileLoopStack.isEmpty()) {
        faultExecution("ENDWHILE has no active WHILE.");
        return true;
    }
    gcodeOrder = whileLoopStack.top().startLine;
    return false;
}

int GcodeScript::findEndWhileLine(int startLine) const
{
    int depth = 1;
    for (int lineIndex = startLine + 1; lineIndex < gcodeList.size(); ++lineIndex) {
        QString statement = gcodeList.at(lineIndex).trimmed();
        statement.remove(QRegularExpression("^N\\d+\\s+",
                                            QRegularExpression::CaseInsensitiveOption));
        const QString command = statement.section(QRegularExpression("\\s+"), 0, 0).toUpper();
        if (command == "WHILE")
            ++depth;
        else if (command == "ENDWHILE" && --depth == 0)
            return lineIndex;
    }
    return -1;
}

bool GcodeScript::handleBREAK()
{
    return handleLoopControl(false);
}

bool GcodeScript::handleCONTINUE()
{
    return handleLoopControl(true);
}

bool GcodeScript::handleLoopControl(bool isContinue)
{
    int forFloor = callStack.isEmpty() ? 0 : callStack.top().forDepth;
    int whileFloor = callStack.isEmpty() ? 0 : callStack.top().whileDepth;
    if (returnPointerOrder >= 0) {
        forFloor = qMax(forFloor, subprogramFrames[returnPointerOrder].forDepth);
        whileFloor = qMax(whileFloor, subprogramFrames[returnPointerOrder].whileDepth);
    }
    const bool hasFor = forLoopStack.size() > forFloor;
    const bool hasWhile = whileLoopStack.size() > whileFloor;
    if (!hasFor && !hasWhile) {
        faultExecution(QString("%1 requires a loop in the current function or subprogram invocation.")
                           .arg(isContinue ? "CONTINUE" : "BREAK"));
        return true;
    }
    const bool nearestWhile = hasWhile && (!hasFor ||
        whileLoopStack.top().nestingOrder > forLoopStack.top().nestingOrder);
    const int ifDepth = nearestWhile ? whileLoopStack.top().ifDepth : forLoopStack.top().ifDepth;
    const int switchDepth = nearestWhile ? whileLoopStack.top().switchDepth : forLoopStack.top().switchDepth;
    while (ifBlockStack.size() > ifDepth)
        ifBlockStack.pop();
    while (switchCaseStack.size() > switchDepth)
        switchCaseStack.pop();
    const int endLine = nearestWhile ? whileLoopStack.top().endWhileLine : forLoopStack.top().endForLine;
    if (!isContinue) {
        if (nearestWhile)
            whileLoopStack.pop();
        else
            forLoopStack.pop();
    }
    gcodeOrder = endLine + (isContinue ? 0 : 1);
    return false;
}

bool GcodeScript::handleSWITCH(QList<QString> valuePairs, int i)
{
    Q_UNUSED(valuePairs)
    Q_UNUSED(i)
    const QRegularExpressionMatch match = QRegularExpression(
        "^\\s*SWITCH\\s+(.+)$", QRegularExpression::CaseInsensitiveOption).match(currentLine);
    if (!match.hasMatch()) {
        faultExecution("SWITCH requires a value.");
        return true;
    }

    QString expression = match.captured(1).trimmed();
    QString switchValue;
    if (expression.size() >= 2 &&
        ((expression.startsWith('"') && expression.endsWith('"')) ||
         (expression.startsWith('\'') && expression.endsWith('\''))))
        switchValue = expression.mid(1, expression.size() - 2);
    else if (expression.startsWith('#'))
        switchValue = getValueAsString(expression);
    else
        switchValue = calculateExpressions(expression).trimmed();

    const int endLine = findEndSwitchLine(gcodeOrder);
    if (endLine < 0) {
        faultExecution("SWITCH has no matching ENDSWITCH.");
        return true;
    }

    bool matchedCase = false;
    const int branchLine = findMatchingSwitchBranch(gcodeOrder, switchValue, &matchedCase);
    if (branchLine < 0) {
        gcodeOrder = endLine + 1;
        return false;
    }

    SwitchCaseState state(QString(), switchValue, gcodeOrder);
    state.endSwitchLine = endLine;
    state.caseMatched = true;
    state.defaultFound = !matchedCase;
    switchCaseStack.push(state);
    gcodeOrder = branchLine + 1;
    return false;
}

bool GcodeScript::handleCASE(QList<QString> valuePairs, int i)
{
    Q_UNUSED(valuePairs)
    Q_UNUSED(i)
    if (switchCaseStack.isEmpty()) {
        faultExecution("CASE can only be used inside SWITCH.");
        return true;
    }
    const int endLine = switchCaseStack.top().endSwitchLine;
    switchCaseStack.pop();
    gcodeOrder = endLine + 1;
    return false;
}

bool GcodeScript::handleDEFAULT()
{
    if (switchCaseStack.isEmpty()) {
        faultExecution("DEFAULT can only be used inside SWITCH.");
        return true;
    }
    const int endLine = switchCaseStack.top().endSwitchLine;
    switchCaseStack.pop();
    gcodeOrder = endLine + 1;
    return false;
}

bool GcodeScript::handleENDSWITCH()
{
    if (!switchCaseStack.isEmpty())
        switchCaseStack.pop();
    gcodeOrder++;
    return false;
}

int GcodeScript::findEndSwitchLine(int startLine) const
{
    int depth = 1;
    for (int lineIndex = startLine + 1; lineIndex < gcodeList.size(); ++lineIndex) {
        QString statement = gcodeList.at(lineIndex).trimmed();
        statement.remove(QRegularExpression("^N\\d+\\s+",
                                            QRegularExpression::CaseInsensitiveOption));
        const QString command = statement.section(QRegularExpression("\\s+"), 0, 0).toUpper();
        if (command == "SWITCH")
            ++depth;
        else if (command == "ENDSWITCH" && --depth == 0)
            return lineIndex;
    }
    return -1;
}

int GcodeScript::findMatchingSwitchBranch(int startLine, const QString& switchValue,
                                          bool* matchedCase)
{
    int depth = 1;
    int defaultLine = -1;
    for (int lineIndex = startLine + 1; lineIndex < gcodeList.size(); ++lineIndex) {
        QString statement = gcodeList.at(lineIndex).trimmed();
        statement.remove(QRegularExpression("^N\\d+\\s+",
                                            QRegularExpression::CaseInsensitiveOption));
        const QString command = statement.section(QRegularExpression("\\s+"), 0, 0).toUpper();
        if (command == "SWITCH") {
            ++depth;
            continue;
        }
        if (command == "ENDSWITCH") {
            if (--depth == 0)
                break;
            continue;
        }
        if (depth != 1)
            continue;
        if (command == "DEFAULT") {
            defaultLine = lineIndex;
            continue;
        }
        if (command != "CASE")
            continue;

        QString caseExpression = statement.mid(statement.indexOf(QRegularExpression("\\s+"))).trimmed();
        if (caseExpression.endsWith(':'))
            caseExpression.chop(1);
        QString caseValue;
        if (caseExpression.size() >= 2 &&
            ((caseExpression.startsWith('"') && caseExpression.endsWith('"')) ||
             (caseExpression.startsWith('\'') && caseExpression.endsWith('\''))))
            caseValue = caseExpression.mid(1, caseExpression.size() - 2);
        else if (caseExpression.startsWith('#'))
            caseValue = getValueAsString(caseExpression);
        else
            caseValue = calculateExpressions(caseExpression).trimmed();

        bool leftOk = false;
        bool rightOk = false;
        const double leftNumber = switchValue.toDouble(&leftOk);
        const double rightNumber = caseValue.toDouble(&rightOk);
        const bool equal = leftOk && rightOk
            ? qFuzzyCompare(1.0 + leftNumber, 1.0 + rightNumber)
            : switchValue == caseValue;
        if (equal) {
            if (matchedCase)
                *matchedCase = true;
            return lineIndex;
        }
    }
    if (matchedCase)
        *matchedCase = false;
    return defaultLine;
}

// ============== FUNCTION HANDLING METHODS ==============

bool GcodeScript::handleFUNCTION(QList<QString> valuePairs, int i)
{
    if (valuePairs.size() <= i + 1)
        return false;
    
    QString functionToken = valuePairs[i + 1];
    QString functionName = functionToken;
    QStringList parameters;
    
    // Parse parameters from function name if contains parentheses
    if (functionToken.contains('('))
    {
        int openParen = functionToken.indexOf('(');
        int closeParen = functionToken.lastIndexOf(')');
        
        // Always trim name before '('
        if (openParen != -1)
        {
            functionName = functionName.left(openParen);
        }

        if (openParen != -1 && closeParen != -1 && closeParen > openParen)
        {
            QString paramStr = functionToken.mid(openParen + 1, closeParen - openParen - 1);
            
            // Parse parameters
            if (!paramStr.trimmed().isEmpty())
            {
                const QStringList paramTokens = splitArgsRespectingParens(paramStr);
                for (QString param : paramTokens)
                {
                    param = param.trimmed();
                    // Remove # from parameter name if present
                    if (param.startsWith("#"))
                        param = param.mid(1);
                    parameters.append(param);
                }
            }
        }
    }
    else if (currentLine.contains('('))
    {
        // Parameters in same line: FUNCTION functionName (param1, param2)
        int openParen = currentLine.indexOf('(');
        int closeParen = currentLine.lastIndexOf(')');
        
        if (openParen != -1 && closeParen != -1 && closeParen > openParen)
        {
            QString paramStr = currentLine.mid(openParen + 1, closeParen - openParen - 1);
            
            if (!paramStr.trimmed().isEmpty())
            {
                const QStringList paramTokens = splitArgsRespectingParens(paramStr);
                for (QString param : paramTokens)
                {
                    param = param.trimmed();
                    if (param.startsWith("#"))
                        param = param.mid(1);
                    parameters.append(param);
                }
            }
        }
    }
    
    if (functionName.startsWith("#"))
        functionName = functionName.mid(1);
    functionName = functionName.toUpper();
    
    // Store function definition
    SimpleFunctionDef newFunction(functionName, parameters, gcodeOrder);
    functionDefinitions[functionName] = newFunction;
    
    // Skip to ENDFUNCTION
    for (int order = gcodeOrder + 1; order < gcodeList.size(); order++)
    {
        QString line = gcodeList[order];
        if (GScriptSyntax::command(GScriptSyntax::stripComment(line)) == "ENDFUNCTION")
        {
            gcodeOrder = order + 1;
            return false;
        }
    }
    
    return false;
}

bool GcodeScript::handleENDFUNCTION(QList<QString> valuePairs, int i)
{
    // If currently inside a function call (via callFunction), return to caller
    if (!functionReturnStack.isEmpty())
    {
        if (!callStack.isEmpty() && returnPointerOrder + 1 != callStack.top().subprogramDepth) {
            faultExecution("ENDFUNCTION cannot return across a subprogram call boundary.");
            return true;
        }
        int ret = functionReturnStack.pop();
        unwindFunctionFrame();
        gcodeOrder = ret + 1;
        return false;
    }

    // Otherwise, we are skipping a function definition in main flow
    gcodeOrder++;
    return false;
}

bool GcodeScript::handleRETURN(QList<QString> valuePairs, int i)
{
    QString returnTarget;
    QVariant returnValue;
    bool hasReturnValue = false;

    // Handle return value if provided
    if (valuePairs.size() > (i + 1))
    {
        const QRegularExpressionMatch returnMatch = QRegularExpression(
            "\\bRETURN\\b", QRegularExpression::CaseInsensitiveOption).match(currentLine);
        QString returnExpr = currentLine.mid(returnMatch.capturedEnd()).trimmed();
        if (!returnExpr.isEmpty())
        {
            returnValue = calculateExpressions(returnExpr);
            hasReturnValue = true;
            if (!callStack.isEmpty())
                returnTarget = callStack.top().retTarget;
        }
    }
    
    // Return to caller
    if (!functionReturnStack.isEmpty())
    {
        if (!callStack.isEmpty() && returnPointerOrder + 1 != callStack.top().subprogramDepth) {
            faultExecution("RETURN cannot return across a subprogram call boundary.");
            return true;
        }
        int ret = functionReturnStack.pop();
        unwindFunctionFrame();
        if (hasReturnValue && !returnTarget.isEmpty())
            saveVariable(returnTarget, returnValue);
        gcodeOrder = ret + 1;
    }
    else
    {
        gcodeOrder++;
    }
    return false;
}

bool GcodeScript::handleLOCAL(QList<QString> valuePairs, int i)
{
    Q_UNUSED(valuePairs)
    Q_UNUSED(i)
    if (callStack.isEmpty()) {
        faultExecution("LOCAL can only be used inside a FUNCTION.");
        return true;
    }

    const QRegularExpression keyword("\\bLOCAL\\b",
                                     QRegularExpression::CaseInsensitiveOption);
    const QRegularExpressionMatch keywordMatch = keyword.match(currentLine);
    QString declaration = currentLine.mid(keywordMatch.capturedEnd()).trimmed();
    const int equals = declaration.indexOf('=');
    const QString name = cleanedVarName(equals >= 0
                                            ? declaration.left(equals)
                                            : declaration);
    if (name.isEmpty() || name.contains('.')) {
        faultExecution("LOCAL requires a simple variable name.");
        return true;
    }

    QVariant value = 0.0;
    if (equals >= 0) {
        const QString expression = declaration.mid(equals + 1).trimmed();
        if (expression.size() >= 2 &&
            ((expression.startsWith('"') && expression.endsWith('"')) ||
             (expression.startsWith('\'') && expression.endsWith('\'')))) {
            value = expression.mid(1, expression.size() - 2);
        } else if (expression.startsWith('#') &&
                   !expression.contains(QRegularExpression("[+\\-*/%^<>=]"))) {
            value = getValueAsQVariant(expression);
        } else {
            value = calculateExpressions(expression);
        }
    }

    callStack.top().locals.insert(name, value);
    emit CatchVariable2(name, value);
    gcodeOrder++;
    return false;
}

bool GcodeScript::callFunction(QString functionName, QStringList arguments)
{
    return callFunction(functionName, arguments, QString());
}

bool GcodeScript::callFunction(QString functionName, QStringList arguments, const QString& retTarget)
{
    // Normalize name for consistent lookup
    // Final normalization for function name
    if (functionName.startsWith("#"))
        functionName = functionName.mid(1);
    // Ensure no trailing parentheses remain due to odd spacing
    {
        int parIdx = functionName.indexOf('(');
        if (parIdx != -1)
            functionName = functionName.left(parIdx);
    }
    functionName = functionName.toUpper();

    // Check if function exists
    if (!functionDefinitions.contains(functionName))
    {
        faultExecution(QString("Undefined function: %1.").arg(functionName));
        return false;
    }
    
    SimpleFunctionDef& funcDef = functionDefinitions[functionName];
    
    // Create call frame and bind parameters
    CallFrame frame;
    frame.retTarget = retTarget;
    frame.functionName = functionName;
    frame.callLine = gcodeOrder + 1;
    frame.subprogramDepth = returnPointerOrder + 1;
    frame.ifDepth = ifBlockStack.size();
    frame.forDepth = forLoopStack.size();
    frame.whileDepth = whileLoopStack.size();
    frame.switchDepth = switchCaseStack.size();
    if (arguments.size() != funcDef.parameters.size()) {
        faultExecution(QString("Function %1 expects %2 argument(s), received %3.")
                           .arg(functionName)
                           .arg(funcDef.parameters.size())
                           .arg(arguments.size()));
        return false;
    }
    const int bindCount = qMin(funcDef.parameters.size(), arguments.size());
    for (int i = 0; i < bindCount; ++i) {
        const QString paramName = funcDef.parameters[i];
        const QString argValue = calculateExpressions(arguments[i]);
        frame.locals[paramName] = argValue;
    }
    callStack.push(frame);
    
    // Save return address and jump to function
    functionReturnStack.push(gcodeOrder);
    
    // Jump to function definition (skip FUNCTION line)
    gcodeOrder = funcDef.startLine + 1;
    
    return false;
}

void GcodeScript::unwindFunctionFrame()
{
    if (callStack.isEmpty())
        return;
    const CallFrame frame = callStack.pop();
    while (ifBlockStack.size() > frame.ifDepth)
        ifBlockStack.pop();
    while (forLoopStack.size() > frame.forDepth)
        forLoopStack.pop();
    while (whileLoopStack.size() > frame.whileDepth)
        whileLoopStack.pop();
    while (switchCaseStack.size() > frame.switchDepth)
        switchCaseStack.pop();
}

bool GcodeScript::isFunctionCall(QString line)
{
    // Check if line contains a function call
    QStringList tokens = line.split(' ', Qt::SkipEmptyParts);
    
    if (tokens.isEmpty())
        return false;
    
    QString firstToken = tokens[0].toUpper();
    
    // Skip line numbers
    if (firstToken.startsWith("N") && firstToken.length() > 1)
    {
        if (tokens.size() > 1)
            firstToken = tokens[1].toUpper();
        else
            return false;
    }
    
    // Extract function name from token (remove parameters if present)
    QString functionName = firstToken;
    if (functionName.contains('('))
    {
        functionName = functionName.left(functionName.indexOf('('));
    }
    // Strip optional leading '#'
    if (functionName.startsWith('#')) functionName = functionName.mid(1);
    functionName = functionName.toUpper();
    
    // Check if it's a function call
    return functionDefinitions.contains(functionName);
}

QString GcodeScript::parseFunctionCall(QString line, QStringList& arguments)
{
    // Parse function call and extract function name and arguments
    arguments.clear();

    QStringList tokens = line.split(' ', Qt::SkipEmptyParts);
    if (tokens.isEmpty())
        return "";

    QString rawToken = tokens[0];
    QString upperToken = tokens[0].toUpper();

    // Skip line numbers
    if (upperToken.startsWith("N") && upperToken.length() > 1)
    {
        if (tokens.size() > 1) {
            rawToken = tokens[1];
            upperToken = tokens[1].toUpper();
        } else {
            return "";
        }
    }

    // Case: functionName(args) is in the first token
    if (upperToken.contains('('))
    {
        int openParen = rawToken.indexOf('(');
        int closeParen = rawToken.lastIndexOf(')');
        if (openParen != -1 && closeParen != -1 && closeParen > openParen)
        {
            QString paramStr = rawToken.mid(openParen + 1, closeParen - openParen - 1);
            QString funcName = upperToken.left(openParen);
            if (!paramStr.trimmed().isEmpty())
            {
                arguments = splitArgsRespectingParens(paramStr);
                for (QString& arg : arguments) { arg = arg.trimmed(); }
            }
            // Strip leading '#'
            if (funcName.startsWith('#')) funcName = funcName.mid(1);
            return funcName.toUpper();
        }
    }
    else if (line.contains('(') && line.contains(')'))
    {
        // Parameters in same line: functionName (arg1, arg2, ...)
        int openParen = line.indexOf('(');
        int closeParen = line.lastIndexOf(')');
        if (openParen < closeParen)
        {
            QString paramStr = line.mid(openParen + 1, closeParen - openParen - 1);
            if (!paramStr.trimmed().isEmpty())
            {
                arguments = splitArgsRespectingParens(paramStr);
                for (QString& arg : arguments) { arg = arg.trimmed(); }
            }
            // Determine function name from left side, skipping optional line number
            QString leftPart = line.left(openParen).trimmed();
            QStringList leftTokens = leftPart.split(' ', Qt::SkipEmptyParts);
            QString funcNameUpper;
            if (!leftTokens.isEmpty()) {
                QString lastTok = leftTokens.last();
                if (lastTok.length() > 1 && lastTok.at(0).toUpper() == 'N') {
                    funcNameUpper = (leftTokens.size() > 1) ? leftTokens[leftTokens.size()-2].toUpper() : lastTok.toUpper();
                } else {
                    funcNameUpper = lastTok.toUpper();
                }
            } else {
                funcNameUpper = leftPart.toUpper();
            }
            // Strip leading '#'
            if (funcNameUpper.startsWith('#')) funcNameUpper = funcNameUpper.mid(1);
            return funcNameUpper;
        }
    }

    // Not a function call
    return "";
}

// Missing function implementations

// ======== OBJECT MANAGEMENT FUNCTIONS IMPLEMENTATION ========

float GcodeScript::setObjectPickedByIndex(QString resultListName, int resultIndex)
{
    if (resultListName.isEmpty() || resultIndex < 0) {
        return 0.0f;
    }
    
    // Validate result list
    QVariant countVar = getValueAsQVariant(resultListName + ".Count");
    int count = countVar.toInt();
    if (resultIndex >= count) {
        return 0.0f;
    }
    
    // Get UID from result list (GetObjectsInArea result)
    QString uidVarName = resultListName + "." + QString::number(resultIndex) + ".UID";
    QVariant uidVar = getValueAsQVariant(uidVarName);
    int uid = uidVar.toInt();
    
    if (uid <= 0) {
        return 0.0f; // Invalid UID
    }
    
    // Send UID-based command for accurate tracking
    QString cmd = QString("SetObjectPickedByUID=Objects,%1").arg(uid);
    emit ChangeExternalVariable(cmd);
    
    return 1.0f; // Success
}

float GcodeScript::getObjectIndex(QString listName, int uid)
{
    if (listName.isEmpty() || uid < 0) {
        return -1.0f; // Invalid parameters
    }
    
    QVariant countVar = getValueAsQVariant(listName + ".Count");
    int count = countVar.toInt();
    
    for (int i = 0; i < count; i++) {
        QString uidVarName = listName + "." + QString::number(i) + ".UID";
        QVariant objUidVar = getValueAsQVariant(uidVarName);
        
        if (objUidVar.toInt() == uid) {
            return static_cast<float>(i); // Return index
        }
    }
    
    return -1.0f; // Object not found
}
