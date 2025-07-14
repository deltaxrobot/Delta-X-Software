#include "GcodeScript.h"
#include <cstdlib>
#include <ctime>

// Initialize static regex patterns for better performance
const QRegularExpression GcodeScript::m98Regex("M98\\s+([A-Za-z]+)(?:\\((.*)\\))?", QRegularExpression::OptimizeOnFirstUsageOption);
const QRegularExpression GcodeScript::objectInAreaRegex("\\(([^)]+)\\)", QRegularExpression::OptimizeOnFirstUsageOption);

GcodeScript::GcodeScript()
{
    // Khởi tạo seed cho random number generator
    srand(static_cast<unsigned int>(time(nullptr)));
}

GcodeScript::~GcodeScript()
{

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
    
    // Clear function definitions when starting new script
    functionDefinitions.clear();
    returnFunctionOrder = -1;

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

    TransmitNextGcode();
}

void GcodeScript::GetResponse(QString deviceId, QString response)
{
    if (checkExclution(response))
        return;

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
    
    // Clear function definitions on stop
    functionDefinitions.clear();
    returnFunctionOrder = -1;
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
    QString cleanValue = value.replace(" ", "");  // Tạo bản sao để xử lý
    QStringList values = cleanValue.split(',');

    // Xử lý trường hợp không có dấu phẩy (hàm 1 tham số hoặc không tham số)
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

    if (functionName.toLower() == "asin")
    {
        return asin(values[0].toFloat()) * 180 / M_PI;
    }

    if (functionName.toLower() == "abs")
    {
        return abs(values[0].toFloat());
    }

    if (functionName.toLower() == "sqrt")
    {
        return sqrt(values[0].toFloat());
    }

    if (functionName.toLower() == "pow")
    {
        if (values.length() >= 2)
        {
            return pow(values[0].toFloat(), values.at(1).toFloat());
        }
        else
        {
            return NULL_NUMBER;
        }
    }

    if (functionName.toLower() == "round")
    {
        return round(values[0].toInt());
    }

    if (functionName.toLower() == "random")
    {
        // #random() - Trả về số ngẫu nhiên từ 0.0 đến 1.0
        return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    }

    if (functionName.toLower() == "randomrange")
    {
        // #randomRange(min, max) - Trả về số ngẫu nhiên trong khoảng [min, max]
        if (values.length() >= 2)
        {
            float min = values[0].toFloat();
            float max = values[1].toFloat();
            if (min > max) {
                // Hoán đổi nếu min > max
                float temp = min;
                min = max;
                max = temp;
            }
            return min + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (max - min);
        }
        else
        {
            return NULL_NUMBER;
        }
    }

    if (functionName.toLower() == "randomint")
    {
        // #randomInt(min, max) - Trả về số nguyên ngẫu nhiên trong khoảng [min, max]
        if (values.length() >= 2)
        {
            int min = values[0].toInt();
            int max = values[1].toInt();
            if (min > max) {
                // Hoán đổi nếu min > max
                int temp = min;
                min = max;
                max = temp;
            }
            return min + rand() % (max - min + 1);
        }
        else
        {
            return NULL_NUMBER;
        }
    }



    return NULL_NUMBER;
}

bool GcodeScript::isGlobalVariable(QString name)
{
    if (name == NULL)
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
    const QStringList valuePairs = currentLine.split(' ', Qt::SkipEmptyParts);
    const QString transmitGcode = currentLine;
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
                
                // Check if right side is a function call
                QStringList arguments;
                QString functionName = parseFunctionCall(rightExpression, arguments);
                
                if (!functionName.isEmpty() && functionDefinitions.contains(functionName))
                {
                    // Handle function call with return value assignment
                    QString varName = currentToken.mid(1); // Remove #
                    
                    // Store variable name for return value assignment
                    saveVariable(QString("__RETURN_VAR__"), varName);
                    
                    // Call function
                    callFunction(functionName, arguments);
                    return false;
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

                            if (!pointName.isEmpty() && pointName[0] == '#')
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
                                }
                                else
                                {
                                    point = getValueAsQVariant(pointName).value<QPointF>();
                                }
                            }
                            else if (paras.count() > 1)
                            {
                                point.setX(paras[0].toFloat());
                                point.setY(paras[1].toFloat());
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
                                    // Chuyển đổi QPointF thành cv::Point2f
                                    cv::Point2f cvInputPoint(point.x(), point.y());

                                    // Tạo một mảng các điểm đầu vào
                                    std::vector<cv::Point2f> inputPoints;
                                    inputPoints.push_back(cvInputPoint);

                                    // Mảng để lưu trữ các điểm đầu ra
                                    std::vector<cv::Point2f> outputPoints;

                                    // Áp dụng phép biến đổi perspective cho các điểm đầu vào
                                    cv::perspectiveTransform(inputPoints, outputPoints, transformMatrix);

                                    // Lấy điểm đầu ra đã được biến đổi
                                    cv::Point2f cvOutputPoint = outputPoints[0];

                                    // Chuyển đổi cv::Point2f thành QPointF
                                    QPointF outputPoint(cvOutputPoint.x, cvOutputPoint.y);

                                    QString varName = currentToken.mid(1);
                                    saveVariable(varName, outputPoint);

                                    gcodeOrder++;
                                    return false;
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

        // --------------- IF-ELIF-ELSE-ENDIF ---------------------
        if (currentToken == "IF" && valuePairsSize > (i + 2))
        {
            if (valuePairs[i + 2] == "THEN")
            {
                return handleIF(valuePairs, i);
            }
        }
        
        // --------------- ELIF ---------------------
        if (currentToken == "ELIF" && valuePairsSize > (i + 2))
        {
            if (valuePairs[i + 2] == "THEN")
            {
                return handleELIF(valuePairs, i);
            }
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

                functionName.toLower();

                QStringList paramList;

                if (!params.isEmpty()) {
                    paramList = params.split(',', QString::SkipEmptyParts);
                    for (QString &param : paramList) {
                        param = param.trimmed();
                    }
                }

                if (functionName == "addobject")
                {                    
                    QString listName = paramList.at(0);
                    QStringList objectInfo;
                    // Thêm tất cả phần tử từ paramList vào paras trừ phần tử đầu tiên
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

                    gcodeOrder++;
                    return true;
                }

                // P_capture_and_detect = Pcaptureanddetect = PcaptureAndDetect
                if (subProName.contains("captureanddetect") == true)
                {
                    transmitDeviceId = QString("tracking0");
                    emit CaptureAndDetectRequest();

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
            
            // Check if right part is a function call
            if (isFunctionCall(rightPart))
            {
                QStringList arguments;
                QString functionName = parseFunctionCall(rightPart, arguments);
                
                if (!functionName.isEmpty() && functionDefinitions.contains(functionName))
                {
                    // Store variable name for return value
                    if (leftPart.startsWith("#"))
                        leftPart = leftPart.mid(1);
                    saveVariable("__RETURN_VAR__", leftPart);
                    
                    // Call function
                    callFunction(functionName, arguments);
                    return false;
                }
            }
        }
    }
    
    // Check for simple function call
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
    // Evaluate condition
    QString conditionStr = valuePairs[i + 1];
    bool conditionResult = (calculateExpressions(conditionStr).toFloat() != 0);
    
    // Check if there's a single-line THEN statement
    QString statement = currentLine.mid(currentLine.indexOf("THEN") + 5).trimmed();
    
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
    QRegExp rx("\\((-?\\d+(?:\\.\\d+)?),(-?\\d+(?:\\.\\d+)?),?(-?\\d+(?:\\.\\d+)?)?\\)");

    // TODO: chưa gán 2 point với nhau được
    if (trimmedStr.startsWith("(") && rx.indexIn(trimmedStr) == 0)
    {
        QString x = rx.cap(1);
        QString y = rx.cap(2);
        QString z = rx.cap(3);

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
                int index = expression.indexOf(QRegExp("\\b" + op + "\\b"));
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
            // Kiểm tra xem có phải hàm toán học không
            if (expression.contains('(') && expression.contains(')') && expression.startsWith('#'))
            {
                // Function calls will be handled at statement level, not in expression evaluation
                // Just treat unknown functions as variables for now
                
                // Nếu không phải user-defined function, kiểm tra built-in math functions
                float result = GetResultOfMathFunction(expression);
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
    QRegExp opRegExp("(?<!\\S)(\\+|\\*|\\/|\\%|\\(|\\)|\\^)(?!\\S)");
    s.replace(opRegExp, " \\1 ");

    return s;
}

// Advanced whitespace normalization for better performance and cleaner parsing
QString GcodeScript::normalizeWhitespace(const QString& line)
{
    // Temporarily disabled - using simple processing instead
    return line;
}

// Preprocess entire gcode script for maximum optimization
void GcodeScript::preprocessGcodeScript()
{
    // Temporarily disabled to fix script execution issues
    return;
}

bool GcodeScript::isNotNegative(QString s)
{
    bool isNumeric = false;
    s.toDouble(&isNumeric);

    return !isNumeric;
}

QString GcodeScript::getValueAsString(QString name)
{
    // Kiểm tra xem có phải hàm toán học không (có dấu ngoặc đơn)
    if (name.contains('(') && name.contains(')'))
    {
        float result = GetResultOfMathFunction(name);
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

    if (fullName.endsWith(".X", Qt::CaseInsensitive) || fullName.endsWith(".Y", Qt::CaseInsensitive))
    {
        QString pointName = fullName.left(fullName.length() - 2);
        QVariant pointVar = getValueAsQVariant(pointName);
        if (pointVar.canConvert<QPointF>())
        {
            QPointF point = pointVar.value<QPointF>();
            emit CatchVariable2(pointName, pointVar);

            if (fullName.endsWith(".X", Qt::CaseInsensitive))
            {
                return QString::number(point.x());
            }
            else
            {
                return QString::number(point.y());
            }

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
    if (response.contains("Error:Angle"))
        return true;
//    else if (response.count(",") > 1)
//    {
//        if (!transmitMsg.contains("Position") && !transmitMsg.contains("G28"))
//            return true;
//    }
//    else if (transmitMsg.contains("G28") && response.contains("Ok"))
//    {
//        return true;
//    }

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
    
    // Evaluate ELIF condition
    QString conditionStr = valuePairs[i + 1];
    bool conditionResult = (calculateExpressions(conditionStr).toFloat() != 0);
    
    // Check if there's a single-line THEN statement
    QString statement = currentLine.mid(currentLine.indexOf("THEN") + 5).trimmed();
    
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
    
    QString functionName = valuePairs[i + 1];
    QStringList parameters;
    
    // Parse parameters from function name if contains parentheses
    if (functionName.contains('('))
    {
        int openParen = functionName.indexOf('(');
        int closeParen = functionName.lastIndexOf(')');
        
        if (openParen != -1 && closeParen != -1 && closeParen > openParen)
        {
            QString paramStr = functionName.mid(openParen + 1, closeParen - openParen - 1);
            functionName = functionName.left(openParen);
            
            // Parse parameters
            if (!paramStr.trimmed().isEmpty())
            {
                QStringList paramTokens = paramStr.split(',');
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
                QStringList paramTokens = paramStr.split(',');
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
    
    if (functionName.startsWith("#"))
        functionName = functionName.mid(1);
    
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
    // Simply skip ENDFUNCTION when encountered during function definition
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
            saveVariable("__RETURN_VALUE__", returnValue);
            
            // Check if there's a variable to assign return value to
            QString returnVar = getValueAsString("__RETURN_VAR__");
            if (returnVar != "__RETURN_VAR__" && !returnVar.isEmpty())
            {
                saveVariable(returnVar, returnValue);
                saveVariable(QString("__RETURN_VAR__"), QString("")); // Clear return var
            }
        }
    }
    
    // Similar to M99 - return to caller
    if (returnFunctionOrder >= 0)
    {
        gcodeOrder = returnFunctionPointer[returnFunctionOrder] + 1;
        returnFunctionOrder--;
    }
    else
    {
        gcodeOrder++;
    }
    return false;
}

bool GcodeScript::callFunction(QString functionName, QStringList arguments)
{
    // Check if function exists
    if (!functionDefinitions.contains(functionName))
    {
        return false;
    }
    
    SimpleFunctionDef& funcDef = functionDefinitions[functionName];
    
    // Bind parameters to variables (simple binding)
    for (int i = 0; i < funcDef.parameters.size() && i < arguments.size(); i++)
    {
        QString paramName = funcDef.parameters[i];
        QString argValue = calculateExpressions(arguments[i]);
        saveVariable(paramName, argValue);
    }
    
    // Similar to M98 - save return address and jump to function
    returnFunctionOrder++;
    returnFunctionPointer[returnFunctionOrder] = gcodeOrder;
    
    // Jump to function definition (skip FUNCTION line)
    gcodeOrder = funcDef.startLine + 1;
    
    return false;
}

bool GcodeScript::isFunctionCall(QString line)
{
    // Check if line contains a function call
    QStringList tokens = line.split(' ', QString::SkipEmptyParts);
    
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
    
    // Check if it's a function call
    return functionDefinitions.contains(functionName);
}

QString GcodeScript::parseFunctionCall(QString line, QStringList& arguments)
{
    // Parse function call and extract function name and arguments
    arguments.clear();
    
    QStringList tokens = line.split(' ', QString::SkipEmptyParts);
    
    if (tokens.isEmpty())
        return "";
    
    QString functionName = tokens[0].toUpper();
    
    // Skip line numbers
    if (functionName.startsWith("N") && functionName.length() > 1)
    {
        if (tokens.size() > 1)
            functionName = tokens[1].toUpper();
        else
            return "";
    }
    
    // Check if function name contains parameters
    if (functionName.contains('('))
    {
        int openParen = functionName.indexOf('(');
        int closeParen = functionName.lastIndexOf(')');
        
        if (openParen != -1 && closeParen != -1 && closeParen > openParen)
        {
            QString paramStr = functionName.mid(openParen + 1, closeParen - openParen - 1);
            functionName = functionName.left(openParen);
            
            if (!paramStr.trimmed().isEmpty())
            {
                arguments = paramStr.split(',', QString::SkipEmptyParts);
                for (QString& arg : arguments)
                {
                    arg = arg.trimmed();
                }
            }
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
                arguments = paramStr.split(',', QString::SkipEmptyParts);
                for (QString& arg : arguments)
                {
                    arg = arg.trimmed();
                }
            }
        }
    }
    
    return functionName;
}


