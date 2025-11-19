/*
* GScript - new script language for robot automation
*/

#include "GcodeScript.h"
#include "CloudPointMapper.h"
#include "VariableManager.h"
#include "SoftwareManager.h"
#include <QStandardPaths>
#include <QDir>
#include <QDateTime>
#include <QDebug>
#include <QTimer>
#include <QMetaObject>
#include <QRegularExpression>
#include <QPointF>

// Initialize static regex patterns for better performance
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
static constexpr QRegularExpression::PatternOptions kRegexOptimizeOption = QRegularExpression::PatternOptions();
#else
static constexpr QRegularExpression::PatternOptions kRegexOptimizeOption = QRegularExpression::OptimizeOnFirstUsageOption;
#endif

const QRegularExpression GcodeScript::m98Regex("M98\\s+([A-Za-z][A-Za-z0-9]*)(?:\\((.*)\\))?", kRegexOptimizeOption);
const QRegularExpression GcodeScript::objectInAreaRegex("\\(([^)]+)\\)", kRegexOptimizeOption);

// Initialize cloud point mapper member variables
GcodeScript::GcodeScript(QObject* parent)
    : QObject(parent)
    , m_zPlaneFilterHandler(nullptr)
    , m_cloudPointMapper(nullptr)
    , m_cloudPointMapperInitialized(false)
    , returnPointerOrder(-1)
    , IsConveyorSync(false)
{
    // Initialize array
    for (int i = 0; i < 20; i++) {
        returnSubProPointer[i] = -1;
    }
    
    // Initialize cloud point mapper
    initializeCloudPointMapper();
}

GcodeScript::~GcodeScript()
{
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
    gcodeScript = gcode;
}

QString GcodeScript::GetGcodeScript()
{
    return gcodeScript;
}

void GcodeScript::SetProgramPath(QString path)
{
    programPath = path;
    QFileInfo fileInfo(programPath);
    programName = fileInfo.fileName();
}

QString GcodeScript::GetProgramPath()
{
    return programPath;
}

QString GcodeScript::GetProgramName()
{
    return programName;
}

bool GcodeScript::IsRunning()
{
    return isRunning;
}

void GcodeScript::setZPlaneFilterHandler(QObject* handler)
{
    m_zPlaneFilterHandler = handler;
}

void GcodeScript::ExecuteGcode(QString gcodes, int startMode)
{
    isRunning = true;
    SoftwareManager::GetInstance()->RunningScriptThreadNumber++;

    QList<QString> tempGcodeList = gcodes.split('\n');

    gcodeList.clear();
    lineNumberCacheValid = false;  // Invalidate cache when gcodeList changes
    
    // Clear IF block stack when starting new script
    ifBlockStack.clear();
    
    // Clear FOR loop stack when starting new script
    forLoopStack.clear();
    
    // Clear function and label definitions and call stacks when starting new script
    functionDefinitions.clear();
    labelDefinitions.clear();
    callStack.clear();
    functionReturnStack.clear();

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
        this->response = response;
        saveVariable("Response", response);
        TransmitNextGcode();
    }
}

void GcodeScript::SendMsgToDevice(QString deviceId, QString msg)
{
    transmitDeviceId = deviceId;
    transmitMsg = msg;
    emit SendGcodeToDevice(deviceId, msg);
}

void GcodeScript::TransmitNextGcode()
{
    if (gcodeOrder >= gcodeList.size())
    {
        Stop();

        return;
    }

    while (true)
    {
        currentLine = gcodeList.at(gcodeOrder);
        bool isGcode = true;

        if (currentLine == "")
        {
            isGcode = false;
            gcodeOrder += 1;
        }
        else
        {
            QStringList tokens = currentLine.split(' ');
            if (!tokens.isEmpty()) {
                QString firstPair = tokens.at(0);

                if (!firstPair.isEmpty() && firstPair.at(0) == 'N')
            {
                QString line = currentLine;
                currentLine = line.replace(firstPair + " ", "");
                }
            }

            isGcode = findExeGcodeAndTransmit();
        }

        if (gcodeOrder >= gcodeList.size())
        {
            Stop();

            break;
        }

        if (isGcode == true)
        {
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
    isRunning = false;
    SoftwareManager::GetInstance()->RunningScriptThreadNumber--;
    emit Finished();

    gcodeList.clear();
    gcodeOrder = 0;
    
    // Clear IF block stack on stop
    ifBlockStack.clear();
    
    // Clear FOR loop stack on stop
    forLoopStack.clear();
    
    // Clear function and label definitions and call stacks on stop
    functionDefinitions.clear();
    labelDefinitions.clear();
    callStack.clear();
    functionReturnStack.clear();
}

void GcodeScript::ReceivedGcode(QString gcode)
{
    ExecuteGcode(gcode, BEGIN);
}

void GcodeScript::prepareCurrentLine()
{
    // Revert to original simple processing to fix script not running
    currentLine = currentLine.replace("  ", " ");
    currentLine = currentLine.replace("\t", "");
    
    // Add spaces around operators for proper parsing
    normalizeOperators();
    
    currentLine = formatSpaces(currentLine);
}

bool GcodeScript::shouldSkipLine()
{
    if (currentLine.isEmpty() || currentLine.at(0) == ';') {
        gcodeOrder++;
        return true;
    }
    if(currentLine.contains(";")) {
        currentLine = currentLine.split(";").at(0);
    }
    return false;
}

void GcodeScript::collapseGcodeLine()
{
    int openBracIndex = currentLine.indexOf('[');

    while (openBracIndex != -1) {
        int closeBracIndex = findClosingBracket(openBracIndex);
        QString expressInBracket = currentLine.mid(openBracIndex, closeBracIndex - openBracIndex + 1);
        
        // Normalize operators in the expression before calculating
        QString normalizedExpression = expressInBracket;
        normalizeExpressionOperators(normalizedExpression);
        
        QString resultInBracket = calculateExpressions(normalizedExpression);

        currentLine.replace(expressInBracket, resultInBracket);
        openBracIndex = currentLine.indexOf('[');
    }
}

int GcodeScript::findClosingBracket(int openIndex)
{
    int subBracNum = 1;
    for (int i = openIndex + 1; i < currentLine.length(); i++) {
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
    QString cleanValue = value.replace(" ", "");  // Táº¡o báº£n sao Ä‘á»ƒ xá»­ lÃ½
    QStringList values = cleanValue.split(',');

    // Xá»­ lÃ½ trÆ°á»ng há»£p khÃ´ng cÃ³ dáº¥u pháº©y (hÃ m 1 tham sá»‘ hoáº·c khÃ´ng tham sá»‘)
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

    // Set object picked: #setObjectPicked(index) hoặc #setObjectPicked(listName, index)
    if (functionName.toLower() == "setobjectpicked")
    {
        if (values.size() == 1) {
            // #setObjectPicked(#PickableObjects.[#i]) - sử dụng resultListName từ context
            // Tạm thời dùng "PickableObjects" làm default, có thể cần customize
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
        mapper->exportToVariableManager("CloudMapping");
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
    statsText += QString("Points: %1, ").arg(stats.totalPoints);
    statsText += QString("Avg Error: %1mm, ").arg(stats.averageError, 0, 'f', 2);
    statsText += QString("Max Error: %1mm, ").arg(stats.maxError, 0, 'f', 2);
    statsText += QString("Coverage: %1%, ").arg(stats.coverage, 0, 'f', 1);
    statsText += QString("Valid: %1").arg(stats.isValid ? "Yes" : "No");
    
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
        mapper->exportToVariableManager("CloudMapping");
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
        mapper->exportToVariableManager("CloudMapping");
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
    
    bool success = mapper->exportToVariableManager(variableName);
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
    
    bool success = mapper->importFromVariableManager(variableName);
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
        mapper->exportToVariableManager("CloudMapping");
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
        mapper->exportToVariableManager("CloudMapping");
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
    QString prefix = gcode.mid(0, gcode.indexOf(" "));
    if (conveyorGcodes.indexOf(prefix) > -1)
        return true;
    return false;
}

bool GcodeScript::isSlidingGcode(QString gcode)
{
    QString conveyorGcodes = "M320 M321 M322 M323";
    QString prefix = gcode.mid(0, gcode.indexOf(" "));
    if (conveyorGcodes.indexOf(prefix) > -1)
        return true;
    return false;
}

bool GcodeScript::isEncoderGcode(QString gcode)
{
    QString encoderGcodes = "M316 M317 M318 M319";
    QString prefix = gcode.mid(0, gcode.indexOf(" "));
    if (encoderGcodes.indexOf(prefix) > -1)
        return true;
    return false;
}

bool GcodeScript::isMovingGcode(QString gcode)
{
    QString movingGcodes = "G01 G00 G1 G0 G02 G03";
    QString prefix = gcode.mid(0, gcode.indexOf(" "));
    if (movingGcodes.indexOf(prefix) > -1)
        return true;
    return false;
}

bool GcodeScript::findExeGcodeAndTransmit()
{
    currentGcodeEditorCursor = gcodeOrder;

    if (elapsedTimer.restart() > 50 && gcodeList.count() > 1)
        emit Moved(currentGcodeEditorCursor);

    prepareCurrentLine();
    
    if (shouldSkipLine()) return false;
    collapseGcodeLine();

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

    for (int i = 0; i < valuePairsSize; i++)
    {
        // Skip empty tokens (already handled by Qt::SkipEmptyParts above)
        const QString& currentToken = valuePairs[i];  // Use reference to avoid copy

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
                                    // Chuyá»ƒn Ä‘á»•i QPointF thÃ nh cv::Point2f
                                    cv::Point2f cvInputPoint(point.x(), point.y());

                                    // Táº¡o má»™t máº£ng cÃ¡c Ä‘iá»ƒm Ä‘áº§u vÃ o
                                    std::vector<cv::Point2f> inputPoints;
                                    inputPoints.push_back(cvInputPoint);

                                    // Máº£ng Ä‘á»ƒ lÆ°u trá»¯ cÃ¡c Ä‘iá»ƒm Ä‘áº§u ra
                                    std::vector<cv::Point2f> outputPoints;

                                    // Ãp dá»¥ng phÃ©p biáº¿n Ä‘á»•i perspective cho cÃ¡c Ä‘iá»ƒm Ä‘áº§u vÃ o
                                    cv::perspectiveTransform(inputPoints, outputPoints, transformMatrix);

                                    // Láº¥y Ä‘iá»ƒm Ä‘áº§u ra Ä‘Ã£ Ä‘Æ°á»£c biáº¿n Ä‘á»•i
                                    cv::Point2f cvOutputPoint = outputPoints[0];

                                    // Chuyá»ƒn Ä‘á»•i cv::Point2f thÃ nh QPointF
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
                if (rightExpression.contains("#GetObjectInArea"))
                {
                    QRegularExpressionMatch match = objectInAreaRegex.match(rightExpression);

                    if (match.hasMatch()) {
                        QString ref = match.captured(1);
                        QStringList paras = ref.split(',');
                        QString trackingID = paras.at(0).trimmed();
                        QStringList pair1 = paras.at(1).trimmed().split('=');
                        QStringList pair2 = paras.at(2).trimmed().split('=');

                        QString avaible_list = valuePairs[0];

                        float min = pair1.at(1).toFloat();
                        float max = pair2.at(1).toFloat();

                        int index = 0;

                        bool isXdirection = false;

                        if (ref.contains("X_MIN") && ref.contains("X_MAX"))
                        {
                            isXdirection = true;
                        }

                        transmitDeviceId = QString("tracking") + trackingID;
                        emit GetObjectsRequest(trackingID.toInt(), avaible_list, min, max, isXdirection);

                        gcodeOrder++;
                        return true;
                    }
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

        if (currentToken == "GOTO" && valuePairsSize > (i + 1))
        {
            return handleGOTO(valuePairs, i);
        }

        // --------------- JUMP (named label) ---------------------
        if (currentToken == "JUMP" && valuePairsSize > (i + 1))
        {
            return handleJUMP(valuePairs, i);
        }

        // --------------- LABEL (no-op at runtime) ---------------------
        if (currentToken == "LABEL")
        {
            gcodeOrder++;
            return false;
        }

        // --------------- IF-ELIF-ELSE-ENDIF ---------------------
        if (currentToken == "IF")
        {
            return handleIF(valuePairs, i);
        }
        
        // --------------- ELIF ---------------------
        if (currentToken == "ELIF")
        {
            return handleELIF(valuePairs, i);
        }
        
        // --------------- ELSE ---------------------
        if (currentToken == "ELSE")
        {
            return handleELSE(valuePairs, i);
        }
        
        // --------------- ENDIF ---------------------
        if (currentToken == "ENDIF")
        {
            return handleENDIF(valuePairs, i);
        }
        
        // --------------- FOR LOOPS ---------------------
        if (currentToken == "FOR" && valuePairsSize > (i + 1))
        {
            return handleFOR(valuePairs, i);
        }
        
        // --------------- ENDFOR ---------------------
        if (currentToken == "ENDFOR")
        {
            return handleENDFOR(valuePairs, i);
        }
        
        // --------------- FUNCTION DECLARATION ---------------------
        if (currentToken == "FUNCTION" && valuePairsSize > (i + 1))
        {
            return handleFUNCTION(valuePairs, i);
        }
        
        // --------------- ENDFUNCTION ---------------------
        if (currentToken == "ENDFUNCTION")
        {
            return handleENDFUNCTION(valuePairs, i);
        }
        
        // --------------- RETURN ---------------------
        if (currentToken == "RETURN")
        {
            return handleRETURN(valuePairs, i);
        }        

        // --------------- DEFINE SUBPROGRAM ------

        // N15 O2000
        // ....
        // N45 M99

        if (!currentToken.isEmpty() && currentToken[0] == 'O')
        {
            return handleDEFINE_SUBPROGRAM(valuePairs, i);
        }

        // --------------- CALL SUBPROGRAM --------

        // N50 M98 P2000



        if (currentToken == "M98" && valuePairsSize > (i + 1))
        {
            QRegularExpressionMatch match = m98Regex.match(currentLine.replace('_', ""));

            if (match.hasMatch()) {
                QString functionName = match.captured(1);
                QString params = match.captured(2);

                if (!functionName.isEmpty() && functionName.at(0) == 'P')
                    functionName.remove(0, 1);

                functionName = functionName.toLower();

                QStringList paramList;

                if (!params.isEmpty()) {
                    paramList = params.split(',', Qt::SkipEmptyParts);
                    for (QString &param : paramList) {
                        param = param.trimmed();
                    }
                }

                // Unified handling: M98 PupdateTracking / PupdateTracking(0)
                if (functionName.startsWith("updatetracking"))
                {
                    int trackingId = 0;
                    if (!paramList.isEmpty()) {
                        bool ok=false; int v=paramList.first().toInt(&ok); if (ok) trackingId = v;
                    } else {
                        // Support numeric suffix: PupdateTracking0
                        QRegularExpression rx("^updatetracking(\\d+)$");
                        QRegularExpressionMatch mm = rx.match(functionName);
                        if (mm.hasMatch()) trackingId = mm.captured(1).toInt();
                    }

                    transmitDeviceId = QString("tracking") + QString::number(trackingId);
                    emit UpdateTrackingRequest(trackingId);

                    // Fail-safe timeout to avoid hanging if no response
                    const QString expected = transmitDeviceId;
                    QTimer::singleShot(1500, this, [this, expected]() {
                        if (!isRunning) return;
                        if (this->transmitDeviceId == expected) {
                            this->response = "Timeout";
                            saveVariable("Response", this->response);
                            TransmitNextGcode();
                        }
                    });

                    gcodeOrder++;
                    return true;
                }

                // Unified handling: M98 PcaptureAndDetect / PcaptureAndDetect(0)
                if (functionName.startsWith("captureanddetect"))
                {
                    int trackingId = 0;
                    if (!paramList.isEmpty()) {
                        bool ok=false; int v=paramList.first().toInt(&ok); if (ok) trackingId = v;
                    }

                    // Persist default camera tracking ID for Camera to pick up
                    saveVariable("Camera.TrackingID", QString::number(trackingId));

                    transmitDeviceId = QString("tracking") + QString::number(trackingId);
                    emit CaptureAndDetectRequest();

                    // Fail-safe timeout to avoid hanging if no response
                    const QString expected = transmitDeviceId;
                    QTimer::singleShot(1500, this, [this, expected]() {
                        if (!isRunning) return;
                        if (this->transmitDeviceId == expected) {
                            this->response = "Timeout";
                            saveVariable("Response", this->response);
                            TransmitNextGcode();
                        }
                    });

                    gcodeOrder++;
                    return true;
                }

                if (functionName == "addobject")
                {                    
                    QString listName = paramList.at(0);
                    QStringList objectInfo;
                    // ThÃªm táº¥t cáº£ pháº§n tá»­ tá»« paramList vÃ o paras trá»« pháº§n tá»­ Ä‘áº§u tiÃªn
                    objectInfo.append(paramList.mid(1));
                    QList<QStringList> objects;
                    objects.append(objectInfo);

                    emit AddObject(listName, objects);
                    gcodeOrder++;
                    return false;
                }
            }

            if (!valuePairs[i + 1].isEmpty() && valuePairs[i + 1].at(0) == 'P')
            {
                QString subProName = valuePairs[i + 1].mid(1);
                subProName = subProName.remove("_").toLower();

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
                
                if (subProName.startsWith("logmessage"))
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

                if (subProName.contains("delay") == true)
                {
                    int pos1 = subProName.indexOf("(") + 1;
                    int pos2 = subProName.lastIndexOf(")");
                    QString valueS = subProName.mid(pos1, pos2 - pos1);

                    QThread::msleep(valueS.toULong());

                    gcodeOrder++;
                    return false;
                }

                // P_update_tracking = Pupdatetracking = PupdateTracking = P_updateTracking(0)
                if (subProName.contains("updatetracking") == true)
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
                    emit UpdateTrackingRequest(valueS.toInt());
                    // Fail-safe timeout to avoid hanging if no response
                    const QString expected = transmitDeviceId;
                    QTimer::singleShot(1500, this, [this, expected]() {
                        if (!isRunning) return;
                        if (this->transmitDeviceId == expected) {
                            this->response = "Timeout";
                            saveVariable("Response", this->response);
                            TransmitNextGcode();
                        }
                    });

                    gcodeOrder++;
                    return true;
                }

                // P_capture_and_detect = Pcaptureanddetect = PcaptureAndDetect
                if (subProName.contains("captureanddetect") == true)
                {
                    // Optional parameter: captureanddetect(n)
                    int trackingId = 0;
                    if (subProName.contains("("))
                    {
                        int pos1 = subProName.indexOf("(") + 1;
                        int pos2 = subProName.lastIndexOf(")");
                        trackingId = subProName.mid(pos1, pos2 - pos1).toInt();
                    }

                    // Persist default camera tracking ID for Camera to pick up
                    saveVariable("Camera.TrackingID", QString::number(trackingId));

                    transmitDeviceId = QString("tracking") + QString::number(trackingId);
                    emit CaptureAndDetectRequest();

                    // Fail-safe timeout to avoid hanging if no response
                    const QString expected = transmitDeviceId;
                    QTimer::singleShot(1500, this, [this, expected]() {
                        if (!isRunning) return;
                        if (this->transmitDeviceId == expected) {
                            this->response = "Timeout";
                            saveVariable("Response", this->response);
                            TransmitNextGcode();
                        }
                    });

                    gcodeOrder++;
                    return true;
                }

                //QString funcName = "sendExternalMCU";

                if (subProName.contains("send") == true)
                {
                    int pos1 = subProName.indexOf("\"") + 1;
                    int pos2 = subProName.lastIndexOf("\"");
                    QString msg = subProName.mid(pos1, pos2 - pos1);

                    pos1 = subProName.indexOf("send") + 4;
                    pos2 = subProName.indexOf("\(");
                    QString deviceName = subProName.mid(pos1, pos2 - pos1);

                    SendMsgToDevice(deviceName, msg);

                    gcodeOrder++;
                    return false;
                }


                if (subProName.contains("sendGcode") == true)
                {
                    int pos1 = subProName.indexOf("\"") + 1;
                    int pos2 = subProName.lastIndexOf("\"");
                    QString msg = subProName.mid(pos1, pos2 - pos1);

                    pos1 = subProName.indexOf("sendGcode") + 4;
                    pos2 = subProName.indexOf("\(");
                    QString deviceName = subProName.mid(pos1, pos2 - pos1);

                    SendMsgToDevice(deviceName, msg);

                    gcodeOrder++;
                    return true;
                }

                for (int order = 0; order < gcodeList.size(); order++)
                {
                    if (gcodeList[order].contains(QString("O") + subProName))
                    {
                        returnPointerOrder++;
                        returnSubProPointer[returnPointerOrder] = gcodeOrder;

                        gcodeOrder = order + 1;

                        //TransmitNextGcode();

                        return false;
                    }
                }
            }

            if (!valuePairs[i + 1].isEmpty() && valuePairs[i + 1].at(0) == 'F')
            {
                QString subProName = valuePairs[i + 1].mid(1);
            }
        }

        if (currentToken == "M99")
        {
            gcodeOrder = returnSubProPointer[returnPointerOrder] + 1;
            returnPointerOrder--;
            return false;
        }

        if (currentToken == "SYNC")
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

        if (currentToken == "SELECT")
        {
            const QString& selectedDevice = valuePairs[i + 1];
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
            // Function call failed, skip line
            gcodeOrder++;
            return false;
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
    QString upperLine = currentLine.toUpper();
    int ifPos = upperLine.indexOf("IF");
    int thenPos = upperLine.indexOf("THEN", ifPos + 2);
    QString conditionStr;
    if (ifPos != -1 && thenPos != -1)
        conditionStr = currentLine.mid(ifPos + 2, thenPos - (ifPos + 2)).trimmed();
    else if (ifPos != -1)
        conditionStr = currentLine.mid(ifPos + 2).trimmed();
    else
        conditionStr = valuePairs.size() > i + 1 ? valuePairs[i + 1] : "";

    bool conditionResult = (calculateExpressions(conditionStr).toFloat() != 0);
    
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
            gcodeOrder++; // Move to next line after executing
            ifBlockStack.pop(); // Remove the IF block as it's completed
            return findExeGcodeAndTransmit();
        }
        else
        {
            // Look for ELIF, ELSE, or just skip to next line
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

    trimmedStr = trimmedStr.replace(" ", "");
    QRegularExpression rx("\\((-?\\d+(?:\\.\\d+)?),(-?\\d+(?:\\.\\d+)?),?(-?\\d+(?:\\.\\d+)?)?\\)");
    QRegularExpressionMatch match = rx.match(trimmedStr);

    // TODO: chÆ°a gÃ¡n 2 point vá»›i nhau Ä‘Æ°á»£c
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
    for (int order = gcodeOrder + 1; order < gcodeList.size(); order++)
    {
        if (gcodeList[order].indexOf("M99") > -1)
        {
            gcodeOrder = order + 1;
            return false;
        }
    }
    return false;
}

bool GcodeScript::handleGCODE(QString transmitGcode)
{
    // Apply Z-plane filtering to resolved G-code
    if (m_zPlaneFilterHandler) {
        QString filteredGcode;
        bool invokeOk = QMetaObject::invokeMethod(
            m_zPlaneFilterHandler.data(),
            "filterSingleLineForZPlane",
            Qt::BlockingQueuedConnection,
            Q_RETURN_ARG(QString, filteredGcode),
            Q_ARG(QString, transmitGcode));
        if (invokeOk) {
            transmitGcode = filteredGcode;
        }
    }

    
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
        SendMsgToDevice(DefaultRobot, transmitGcode);
        gcodeOrder += 1;
        return true;
    }

    false;
}

void GcodeScript::handleSENT_TO_DEVICE(QList<QString> valuePairs, int i)
{
    QString msg = valuePairs[i + 1];

    QString deviceName = valuePairs.at(i);
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
    expression = expression.replace("  ", " ");

    int loopNumber = 100;

    while (loopNumber--)
    {
        int openIndex = expression.lastIndexOf('[');

        int multiplyIndex = expression.indexOf('*');
        int divideIndex = expression.indexOf('/');
        int moduloIndex = expression.indexOf('%');
        int plusIndex = expression.indexOf('+');
        int subIndex = expression.indexOf("- ");

        int andIndex = expression.indexOf("AND");
        int orIndex = expression.indexOf("OR");
        int xorIndex = expression.indexOf("XOR");

        int eqIndex = expression.indexOf("EQ");
        int neIndex = expression.indexOf("NE");
        int ltIndex = expression.indexOf("LT");
        int leIndex = expression.indexOf("LE");
        int gtIndex = expression.indexOf("GT");
        int geIndex = expression.indexOf("GE");

        if (eqIndex == -1)
        {
            eqIndex = expression.indexOf("==");
        }
        if (neIndex == -1)
        {
            neIndex = expression.indexOf("!=");
        }
        if (ltIndex == -1)
        {
            ltIndex = expression.indexOf("<");
        }
        if (leIndex == -1)
        {
            leIndex = expression.indexOf("<=");
        }
        if (gtIndex == -1)
        {
            gtIndex = expression.indexOf(">");
        }
        if (geIndex == -1)
        {
            geIndex = expression.indexOf(">=");
        }
        if (andIndex == -1)
        {
            andIndex = expression.indexOf("&&");
        }
        if (orIndex == -1)
        {
            orIndex = expression.indexOf("||");
        }
        if (xorIndex == -1)
        {
            xorIndex = expression.indexOf("^^");
        }

        if (openIndex > -1)
        {
            int closeIndex = expression.indexOf(']', openIndex);
            QString subExpression = expression.mid(openIndex + 1, closeIndex - openIndex -1);
            QString result = calculateExpressions(subExpression);

            subExpression = QString("[") + subExpression + "]";

            expression.replace(subExpression, result);

            continue;
        }
        else if ((multiplyIndex > -1 || divideIndex > -1 || moduloIndex > -1 || plusIndex > -1 || subIndex > -1 || andIndex > -1 || orIndex > -1 || xorIndex > -1) && isNotNegative(expression) && !expression.contains('('))
        {
            // 3 + 2 * 5 - 4 / 2

            int operaIndex = subIndex;

            operaIndex = (plusIndex > -1) ? plusIndex : operaIndex;
            operaIndex = (andIndex > -1) ? andIndex : operaIndex;
            operaIndex = (orIndex > -1) ? orIndex : operaIndex;
            operaIndex = (xorIndex > -1) ? xorIndex : operaIndex;
            operaIndex = (multiplyIndex > -1) ? multiplyIndex : operaIndex;
            operaIndex = (divideIndex > -1) ? divideIndex : operaIndex;
            operaIndex = (moduloIndex > -1) ? moduloIndex : operaIndex;

            QString value1S = getLeftWord(expression, operaIndex);
            QString value2S = getRightWord(expression, operaIndex);

            QString value1Val = getValueAsString(value1S);
            QString value2Val = getValueAsString(value2S);

            float value1 = value1Val.toFloat();
            float value2 = value2Val.toFloat();

            float result = value1 - value2;
            QString resultS = QString::number(result);

            QString operaExpression = value1S + " - " + value2S;

            if (multiplyIndex > -1)
            {
                result = value1 * value2;
                resultS = QString::number(result);

                operaExpression = value1S + " * " + value2S;
            }
            else if (divideIndex > -1)
            {
                if (value2 != 0)
                    result = value1 / value2;
                else
                    result = 0;
                resultS = QString::number(result);

                operaExpression = value1S + " / " + value2S;
            }
            else if (moduloIndex > -1)
            {
                if (value2 != 0)
                    result = (int)value1 % (int)value2;
                else
                    result = 0;
                resultS = QString::number(result);

                operaExpression = value1S + " % " + value2S;
            }
            else if (plusIndex > -1)
            {
                result = value1 + value2;
                resultS = QString::number(result);

                operaExpression = value1S + " + " + value2S;
            }
            else if (andIndex > -1)
            {
                result = value1 * value2;
                result = (result > 0) ? 1 : 0;
                resultS = QString::number(result);

                operaExpression = value1S + " AND " + value2S;
            }
            else if (orIndex > -1)
            {
                result = value1 + value2;
                result = (result > 0) ? 1 : 0;
                resultS = QString::number(result);

                operaExpression = value1S + " OR " + value2S;
            }

            if (xorIndex > -1)
            {
                value1 = (value1 > 0) ? 1 : 0;
                value2 = (value2 > 0) ? 1 : 0;
                result = (value1 != value2) ? 1 : 0;

                resultS = QString::number(result);

                operaExpression = value1S + " XOR " + value2S;
            }

            expression.replace(operaExpression, QString::number(result));

            continue;
        }

        else if ((eqIndex > -1 || ltIndex > -1 || gtIndex > -1 || neIndex > -1 || leIndex > -1 || geIndex > -1) && !expression.contains('('))
        {
            QString value1S;
            QString opeS;
            QString value2S;

            float value1;
            float value2;

            int operatorIndex = eqIndex;

            operatorIndex = (neIndex > -1) ? neIndex : operatorIndex;
            operatorIndex = (ltIndex > -1) ? ltIndex : operatorIndex;
            operatorIndex = (leIndex > -1) ? leIndex : operatorIndex;
            operatorIndex = (gtIndex > -1) ? gtIndex : operatorIndex;
            operatorIndex = (geIndex > -1) ? geIndex : operatorIndex;

            value1S = getLeftWord(expression, operatorIndex);
            value2S = getRightWord(expression, operatorIndex);


            value1 = getValueAsString(value1S).toFloat();

            value2 = getValueAsString(value2S).toFloat();


            int returnValue = -1;

            if (value1S.startsWith("\"") && value1S.endsWith("\""))
            {
                returnValue = (eqIndex > -1) ? ((value1S == value2S) ? 1 : 0 ) : returnValue;
            }
            else
            {
                returnValue = (eqIndex > -1) ? ((value1 == value2) ? 1 : 0 ) : returnValue;
            }

            returnValue = (neIndex > -1) ? ((value1 != value2) ? 1 : 0) : returnValue;
            returnValue = (ltIndex > -1) ? ((value1 < value2) ? 1 : 0) : returnValue;
            returnValue = (leIndex > -1) ? ((value1 <= value2) ? 1 : 0) : returnValue;
            returnValue = (gtIndex > -1) ? ((value1 > value2) ? 1 : 0) : returnValue;
            returnValue = (geIndex > -1) ? ((value1 >= value2) ? 1 : 0) : returnValue;

            if (returnValue != -1)
                return QString::number(returnValue);
        }

        else
        {
            // Kiá»ƒm tra xem cÃ³ pháº£i hÃ m toÃ¡n há»c khÃ´ng
            if (expression.contains('(') && expression.contains(')') && expression.startsWith('#'))
            {
                // Function calls will be handled at statement level, not in expression evaluation
                // Just treat unknown functions as variables for now
                
                // Náº¿u khÃ´ng pháº£i user-defined function, kiá»ƒm tra built-in math functions
                float result = EvaluateFunctionToFloat(expression);
                if (result != NULL_NUMBER)
                {
                    return QString::number(result);
                }
            }

            QString value = getValueAsString(deleteSpaces(expression));

            if (deleteSpaces(expression) == "NULL")
            {
                value = "NULL";
            }

            return value;
        }


        return expression;
    }

    return expression;
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
    QStringList out;
    QString curr;
    int depthParen = 0;
    int depthBracket = 0;
    bool inQuote = false;
    QChar quoteChar = '\0';

    for (int i = 0; i < s.size(); ++i) {
        const QChar ch = s.at(i);
        if (ch == '"' || ch == '\'') {
            if (!inQuote) { inQuote = true; quoteChar = ch; }
            else if (quoteChar == ch) { inQuote = false; quoteChar = '\0'; }
            curr.append(ch);
            continue;
        }
        if (!inQuote) {
            if (ch == '(') depthParen++;
            else if (ch == ')') depthParen = qMax(0, depthParen - 1);
            else if (ch == '[') depthBracket++;
            else if (ch == ']') depthBracket = qMax(0, depthBracket - 1);
            if (ch == ',' && depthParen == 0 && depthBracket == 0) {
                out.append(curr.trimmed());
                curr.clear();
                continue;
            }
        }
        curr.append(ch);
    }
    if (!curr.trimmed().isEmpty()) out.append(curr.trimmed());
    return out;
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
        QVariant value = VariableManager::instance().getVar(varName, QVariant());
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

        // Strip inline comment
        int semicolonIdx = line.indexOf(';');
        if (semicolonIdx != -1)
            line = line.left(semicolonIdx).trimmed();

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
                    if (l.contains("ENDFUNCTION")) { endLine = i; break; }
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
    QString functionName = expression.mid(nameStart, p1 - nameStart);
    QString argsStr = expression.mid(p1 + 1,  p2 - p1 - 1);

    QStringList values;
    if (!argsStr.trimmed().isEmpty())
        values = splitArgsRespectingParens(argsStr);
    for (int i = 0; i < values.size(); ++i) {
        values[i] = calculateExpressions(values.at(i).trimmed());
    }
    values.append("0");
    values.append("0");

    QString fname = functionName.toLower();
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
        return cloudPointAddCalibration(values[0].toFloat(), values[1].toFloat(), values[2].toFloat(), values[3].toFloat(), values[4].toFloat(), values[5].toFloat(), values.size()>6?values[6].toFloat():1.0f, values.size()>7?values[7]:"");
    if (fname == "cloudpointtransformx")
        return cloudPointTransformX(values[0].toFloat(), values[1].toFloat(), values[2].toFloat(), values.size()>3?values[3].toInt():1);
    if (fname == "cloudpointtransformy")
        return cloudPointTransformY(values[0].toFloat(), values[1].toFloat(), values[2].toFloat(), values.size()>3?values[3].toInt():1);
    if (fname == "cloudpointtransformz")
        return cloudPointTransformZ(values[0].toFloat(), values[1].toFloat(), values[2].toFloat(), values.size()>3?values[3].toInt():1);
    if (fname == "cloudpointgetconfidence")
        return cloudPointGetConfidence(values[0].toFloat(), values[1].toFloat(), values[2].toFloat(), values.size()>3?values[3].toInt():1);
    if (fname == "cloudpointgeterror")
        return cloudPointGetError(values[0].toFloat(), values[1].toFloat(), values[2].toFloat(), values.size()>3?values[3].toInt():1);
    if (fname == "cloudpointgetcount") return cloudPointGetCount();
    if (fname == "cloudpointisvalid") return cloudPointIsValid();
    if (fname == "cloudpointclear") return cloudPointClear();
    if (fname == "cloudpointbuildgrid") return cloudPointBuildGrid(values.size()>0?values[0].toFloat():10.0f);
    if (fname == "cloudpointvalidate") return cloudPointValidate(values.size()>0?values[0].toFloat():0.2f);
    if (fname == "cloudpointsave") return cloudPointSave(values.size()>0?values[0]:"");
    if (fname == "cloudpointload") return cloudPointLoad(values.size()>0?values[0]:"");
    if (fname == "cloudpointexport") return cloudPointExport(values.size()>0?values[0]:"CloudMapping");
    if (fname == "cloudpointimport") return cloudPointImport(values.size()>0?values[0]:"CloudMapping");
    if (fname == "cloudpointremove") return cloudPointRemove(values[0].toInt());
    if (fname == "cloudpointupdate") return cloudPointUpdate(values[0].toInt(), values[1].toFloat(), values[2].toFloat(), values[3].toFloat(), values[4].toFloat(), values[5].toFloat(), values[6].toFloat(), values.size()>7?values[7].toFloat():1.0f);
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
        if (result != NULL_NUMBER)
        {
            return QString::number(result);
        }
    }

    name = name.replace("#", "");

    QString fullName = name;

    QStringList paras = name.split('.');

    if (paras[0] != ProjectName)
    {
        VariableManager::instance().Prefix = ProjectName;
    }
    else
    {
        VariableManager::instance().Prefix = "";
    }

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

    if (VariableManager::instance().containsFullKey(fullName) == true)
    {
        QVariant var = VariableManager::instance().getVar(fullName);
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

    QStringList paras = key.split('.');

    if (paras[0] != ProjectName)
    {
        VariableManager::instance().Prefix = ProjectName;
    }
    else
    {
        VariableManager::instance().Prefix = "";
    }

    fullName = fullName.replace(" ", "");

    return VariableManager::instance().getVar(fullName);
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

    emit CatchVariable2(name, value);

    QStringList paras = name.split('.');

    if (paras[0] != ProjectName)
    {
        VariableManager::instance().Prefix = ProjectName;
    }
    else
    {
        VariableManager::instance().Prefix = "";
    }

    VariableManager::instance().addVar(name, value);
}

void GcodeScript::saveVariable(QString name, QVariant value)
{
    emit CatchVariable2(name, value);

    QStringList paras = name.split('.');

    if (paras[0] != ProjectName)
    {
        VariableManager::instance().Prefix = ProjectName;
    }
    else
    {
        VariableManager::instance().Prefix = "";
    }

    VariableManager::instance().addVar(name, value);
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
        saveVariable("LastError", r);
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
    QString upperLine = currentLine.toUpper();
    int elifPos = upperLine.indexOf("ELIF");
    int thenPos = upperLine.indexOf("THEN", elifPos + 4);
    QString conditionStr;
    if (elifPos != -1 && thenPos != -1)
        conditionStr = currentLine.mid(elifPos + 4, thenPos - (elifPos + 4)).trimmed();
    else if (elifPos != -1)
        conditionStr = currentLine.mid(elifPos + 4).trimmed();
    else
        conditionStr = valuePairs.size() > i + 1 ? valuePairs[i + 1] : "";
    bool conditionResult = (calculateExpressions(conditionStr).toFloat() != 0);
    
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
            gcodeOrder++;
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
    QString statement = currentLine.mid(currentLine.indexOf("ELSE") + 4).trimmed();
    
    if (!statement.isEmpty())
    {
        // Single-line ELSE statement
        if (!currentBlock.conditionMet)
        {
            currentBlock.conditionMet = true;
            currentBlock.insideBlock = true;
            currentLine = statement;
            gcodeOrder++;
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
            forLoopStack.push(newLoop);
            
            // Start first iteration
            return executeForLoopIteration();
        }
    }
    
    // Check for numeric FOR syntax: FOR var = start TO end [STEP step]
    if (valuePairs.size() >= (i + 5))
    {
        QString counterVar = valuePairs[i + 1];
        
        if (valuePairs[i + 2] == "=" && valuePairs[i + 4].toUpper() == "TO")
        {
            // Remove # from variable name if present
            if (counterVar.startsWith("#"))
                counterVar = counterVar.mid(1);
            
            QString startStr = valuePairs[i + 3];
            QString endStr = valuePairs[i + 5];
            QString stepStr = "1"; // Default step
            
            // Check for STEP clause
            if (valuePairs.size() >= (i + 8) && valuePairs[i + 6].toUpper() == "STEP")
            {
                stepStr = valuePairs[i + 7];
            }
            
            // Evaluate expressions
            float startValue = calculateExpressions(startStr).toFloat();
            float endValue = calculateExpressions(endStr).toFloat();
            float stepValue = calculateExpressions(stepStr).toFloat();
            
            // Validate step value
            if (stepValue == 0)
            {
                // Invalid step - skip this FOR
                gcodeOrder++;
                return false;
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
    
    // Invalid FOR syntax - skip line
    gcodeOrder++;
    return false;
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
        currentLoop.currentValue += currentLoop.stepValue;
        
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
        if (line.contains("ENDFUNCTION"))
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
        int ret = functionReturnStack.pop();
        if (!callStack.isEmpty()) callStack.pop();
        gcodeOrder = ret + 1;
        return false;
    }

    // Otherwise, we are skipping a function definition in main flow
    gcodeOrder++;
    return false;
}

bool GcodeScript::handleRETURN(QList<QString> valuePairs, int i)
{
    // Handle return value if provided
    if (valuePairs.size() > (i + 1))
    {
        QString returnExpr = currentLine.mid(currentLine.indexOf("RETURN") + 6).trimmed();
        if (!returnExpr.isEmpty())
        {
            QString returnValue = calculateExpressions(returnExpr);
            // Assign to caller's target variable if any
            if (!callStack.isEmpty()) {
                const QString retTarget = callStack.top().retTarget;
                if (!retTarget.isEmpty()) {
                    saveVariable(retTarget, returnValue);
                }
            }
        }
    }
    
    // Return to caller
    if (!functionReturnStack.isEmpty())
    {
        int ret = functionReturnStack.pop();
        if (!callStack.isEmpty()) callStack.pop();
        gcodeOrder = ret + 1;
    }
    else
    {
        gcodeOrder++;
    }
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
        qWarning() << "GScript: call to undefined function" << functionName;
        return false;
    }
    
    SimpleFunctionDef& funcDef = functionDefinitions[functionName];
    
    // Create call frame and bind parameters
    CallFrame frame;
    frame.retTarget = retTarget;
    if (arguments.size() != funcDef.parameters.size()) {
        qWarning() << "GScript: arity mismatch for" << functionName
                   << "expected" << funcDef.parameters.size() << "got" << arguments.size();
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

// ===============================================================
// Z-PLANE LIMITING IMPLEMENTATIONS
// ===============================================================

float GcodeScript::zPlaneCalculateZ(float x, float y)
{
    QString prefix = ProjectName + ".ZPlane.";
    
    // Check if Z-plane is enabled and valid
    bool isEnabled = VariableManager::instance().getVar(prefix + "IsEnabled", false).toBool();
    bool isValid = VariableManager::instance().getVar(prefix + "IsValid", false).toBool();
    
    if (!isEnabled || !isValid) {
        return 0.0f; // Return 0 if plane is not available
    }
    
    // Get plane equation coefficients: ax + by + cz + d = 0
    double a = VariableManager::instance().getVar(prefix + "A", 0.0).toDouble();
    double b = VariableManager::instance().getVar(prefix + "B", 0.0).toDouble();
    double c = VariableManager::instance().getVar(prefix + "C", 1.0).toDouble();
    double d = VariableManager::instance().getVar(prefix + "D", 0.0).toDouble();
    
    // Calculate Z: z = -(ax + by + d) / c
    if (std::abs(c) < 1e-10) {
        return 0.0f; // Avoid division by zero
    }
    
    float z = static_cast<float>(-(a * x + b * y + d) / c);
    return z;
}

bool GcodeScript::zPlaneIsEnabled()
{
    QString prefix = ProjectName + ".ZPlane.";
    bool isEnabled = VariableManager::instance().getVar(prefix + "IsEnabled", false).toBool();
    bool isValid = VariableManager::instance().getVar(prefix + "IsValid", false).toBool();
    
    return isEnabled && isValid;
}

bool GcodeScript::zPlaneIsPointBelow(float x, float y, float z)
{
    QString prefix = ProjectName + ".ZPlane.";
    
    // Check if Z-plane is enabled and valid
    bool isEnabled = VariableManager::instance().getVar(prefix + "IsEnabled", false).toBool();
    bool isValid = VariableManager::instance().getVar(prefix + "IsValid", false).toBool();
    
    if (!isEnabled || !isValid) {
        return false; // No limiting if plane is not available
    }
    
    // Get plane equation coefficients: ax + by + cz + d = 0
    double a = VariableManager::instance().getVar(prefix + "A", 0.0).toDouble();
    double b = VariableManager::instance().getVar(prefix + "B", 0.0).toDouble();
    double c = VariableManager::instance().getVar(prefix + "C", 1.0).toDouble();
    double d = VariableManager::instance().getVar(prefix + "D", 0.0).toDouble();
    
    // Calculate plane equation value: ax + by + cz + d
    double planeValue = a * x + b * y + c * z + d;
    
    // Point is below plane if the equation value is negative
    return planeValue < 0;
}

bool GcodeScript::zPlaneGetEquation(float& a, float& b, float& c, float& d)
{
    QString prefix = ProjectName + ".ZPlane.";
    
    // Check if Z-plane is valid
    bool isValid = VariableManager::instance().getVar(prefix + "IsValid", false).toBool();
    
    if (!isValid) {
        a = b = d = 0.0f;
        c = 1.0f;
        return false;
    }
    
    // Get plane equation coefficients
    a = static_cast<float>(VariableManager::instance().getVar(prefix + "A", 0.0).toDouble());
    b = static_cast<float>(VariableManager::instance().getVar(prefix + "B", 0.0).toDouble());
    c = static_cast<float>(VariableManager::instance().getVar(prefix + "C", 1.0).toDouble());
    d = static_cast<float>(VariableManager::instance().getVar(prefix + "D", 0.0).toDouble());
    
    return true;
}

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
