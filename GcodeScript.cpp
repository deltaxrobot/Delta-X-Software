#include "GcodeScript.h"


GcodeScript::GcodeScript()
{

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

    QList<QString> tempGcodeList = gcodes.split('\n');

    gcodeList.clear();

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

        line = DeleteExcessSpace(line);

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
            QString firstPair = currentLine.split(' ').at(0);

            if (firstPair.at(0) == 'N')
            {
                QString line = currentLine;
                currentLine = line.replace(firstPair + " ", "");
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

void GcodeScript::Stop()
{
    isRunning = false;
    emit Finished();

    gcodeList.clear();
    gcodeOrder = 0;
}

float GcodeScript::GetResultOfMathFunction(QString expression)
{
    if (expression == "")
        return NULL_NUMBER;

    if (expression.at(0) != '#')
        return NULL_NUMBER;

    int p1 = expression.indexOf('(');
    int p2 = expression.lastIndexOf(')');

    if (p1 == -1 && p2 == -1)
        return NULL_NUMBER;

    QString functionName = expression.mid(1, p1 - 1);
    QString value = expression.mid(p1 + 1,  p2 - p1 - 1);
    QStringList values = value.replace(" ", "").split(',');

    if (value.lastIndexOf(',') < value.lastIndexOf(')'))
    {
        values.clear();
        values.append(value);
    }

    values.append("0");
    values.append("0");

    for (int i = 0; i < values.size(); i++)
    {
        if (values.at(i) != "")
        {
            if (values.at(i).at(0) == '#')
            {
                QString val = getValueOfVariable(values.at(i));
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

    currentLine = currentLine.replace("  ", " ");
    currentLine = formatSpaces(currentLine);

    if (currentLine == "")
    {
        gcodeOrder += 1;
        return false;
    }

    if (currentLine.at(0) == ';')
    {
        gcodeOrder += 1;
        return false;
    }

    if(currentLine.contains(";"))
    {
        currentLine = currentLine.split(";").at(0);
    }

    //-----------------------------------
    int openBracIndex = currentLine.indexOf('[');
    QString expressInBracket = "";
    QString resultInBracket;
    int subBracNum = 0;

    // ------------- Conlapse Gcode Line by calculating all expression in [ ... ] ---------------

    while (openBracIndex > -1)
    {
        /*int thenIndex = currentLine.indexOf("THEN");

        if (thenIndex < -1)
            thenIndex = currentLine.length();*/

        for (int i = openBracIndex; i < currentLine.length(); i++)
        {
            expressInBracket += currentLine.at(i);

            if (currentLine.at(i) == '[')
            {
                subBracNum++;
            }

            if (currentLine.at(i) == ']')
            {
                subBracNum--;
            }

            if (subBracNum == 0)
                break;
        }

        resultInBracket = calculateExpressions(expressInBracket);

        currentLine.replace(expressInBracket, resultInBracket);

        expressInBracket = "";

        openBracIndex = currentLine.indexOf('[');
    }

    //-------------- Find programing statement ------------------------

    QList<QString> valuePairs = currentLine.split(' ');
    QString transmitGcode = currentLine;

    for (int i = 0; i < valuePairs.size(); i++)
    {
        if (valuePairs.at(i) == "")
            continue;
        //------------ GOTO -----------

        if (valuePairs.at(i) == "GOTO" && valuePairs.size() > (i + 1))
        {
            bool isNumber;
            int goID;

            goID = valuePairs[i + 1].toInt(&isNumber, 10);

            if (isNumber == true)
            {
                for (int order = 0; order < gcodeList.size(); order++)
                {
                    QList<QString> pairs = gcodeList[order].split(' ');
                    if (pairs.count() > 1)
                    {
                        if (pairs[0] != "")
                        {
                            if (pairs[0].at(0) == 'N')
                            {
                                int id = pairs[0].mid(1).toInt();

                                if (id == goID)
                                {
                                    gcodeOrder = order;
                                    //TransmitNextGcode();
                                    return false;
                                }
                            }
                        }
                    }
                }
            }
        }

        // --------------- IF ---------------------
        if (valuePairs.at(i) == "IF" && valuePairs.size() > (i + 3))
        {
            if (valuePairs[i + 2] == "THEN")
            {
                QString statement = currentLine.mid(currentLine.indexOf("THEN") + 5);

                bool result = false;

                if (valuePairs[i + 1] == "1")
                {
                    result = true;
                }

                if (result == true)
                {
                    transmitGcode = statement;
                    currentLine = transmitGcode;
                    return findExeGcodeAndTransmit();
                }
                else
                {
                    gcodeOrder++;
                    //TransmitNextGcode();
                    return false;
                }
            }
        }
        //0765414444

        //------------ VARIABLE ------------

        // #100 = 2
        // #100 = #100 + 2
        // #100 = #101 - #102

        if (valuePairs.at(i).at(0) == '#' && valuePairs.size() > (i + 2))
        {
            if (valuePairs[i + 1] == "=")
            {
                QString varName = valuePairs.at(i).mid(1);
                QString expression = currentLine.mid(currentLine.indexOf("=") + 2);
                QString trimmedStr = expression;

                trimmedStr = trimmedStr.replace(" ", "");  // Xóa khoảng trắng ở đầu và cuối chuỗi
//                QRegExp rx("\\((-?\\d+(?:\\.\\d+)?),(-?\\d+(?:\\.\\d+)?)\\)");
                QRegExp rx("\\((-?\\d+(?:\\.\\d+)?),(-?\\d+(?:\\.\\d+)?),?(-?\\d+(?:\\.\\d+)?)?\\)");

                if (rx.indexIn(trimmedStr) != -1)
                {
                    QString x = rx.cap(1);
                    QString y = rx.cap(2);
                    QString z = rx.cap(4);

                    saveVariable(varName + ".X", calculateExpressions(x));
                    saveVariable(varName + ".Y", calculateExpressions(y));

                    if (!z.isEmpty()) {
                        saveVariable(varName + ".Z", calculateExpressions(z));
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

        }

        // --------------- WHILE ------------------

        // --------------- DEFINE SUBPROGRAM ------

        // N15 O2000
        // ....
        // N45 M99

        if (valuePairs.at(i).at(0) == 'O')
        {
            /*QString subProName = valuePairs.at(i).mid(1);

            bool isNumber;
            int subProID;

            subProID = subProName.toInt(&isNumber, 10);

            if (isNumber == true)
            {*/
                for (int order = gcodeOrder + 1; order < gcodeList.size(); order++)
                {
                    if (gcodeList[order].indexOf("M99") > -1)
                    {
                        gcodeOrder = order + 1;
                        //TransmitNextGcode();
                        return false;
                    }
                }
            /*}*/
        }

        // --------------- CALL SUBPROGRAM --------

        // N50 M98 P2000

        if (valuePairs.at(i) == "M98" && valuePairs.size() > (i + 1))
        {
            if (valuePairs[i + 1].at(0) == 'P')
            {
                QString subProName = valuePairs[i + 1].mid(1);
                subProName = subProName.remove("_").toLower();

                // PclearObjects = P_clear_object = PClearObject = ...

                if (subProName == "clearobjects")
                {
                    emit DeleteAllObjects();
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
                    if (gcodeList[order].indexOf(QString("O") + subProName) > -1)
                    {
                        returnPointerOrder++;
                        returnSubProPointer[returnPointerOrder] = gcodeOrder;

                        gcodeOrder = order + 1;

                        //TransmitNextGcode();

                        return false;
                    }
                }
            }

            if (valuePairs[i + 1].at(0) == 'F')
            {
                QString subProName = valuePairs[i + 1].mid(1);
            }
        }

        if (valuePairs.at(i) == "M99")
        {
            gcodeOrder = returnSubProPointer[returnPointerOrder] + 1;
            returnPointerOrder--;
            //TransmitNextGcode();
            return false;
        }

        if (valuePairs.at(i) == "SYNC")
        {
            QString target = valuePairs.at(i + 1);
            if (target.contains("robot") && valuePairs.count() > i + 2)
            {
                QString vector = "";
                for (int j = i + 2; j < valuePairs.count(); j++)
                {
                    vector += valuePairs.at(j);
                }

                SendMsgToDevice(target, QString("SYNC ") + vector);

                gcodeOrder++;

                return true;
            }
        }

        if (valuePairs.at(i) == "SELECT")
        {
            QString selectedDevice = valuePairs.at(i + 1);
            if (selectedDevice.contains("robot"))
                DefaultRobot = valuePairs.at(i + 1);
            else if (selectedDevice.contains("conveyor"))
                DefaultConveyor = valuePairs.at(i + 1);
            else if (selectedDevice.contains("encoder"))
                DefaultEncoder = valuePairs.at(i + 1);
            else if (selectedDevice.contains("slider"))
                DefaultSlider = valuePairs.at(i + 1);
            else if (selectedDevice.contains("device"))
                DefaultDevice = valuePairs.at(i + 1);

            gcodeOrder++;

            return false;
        }


        //device0 msg;

        QStringList deviceNames = {"robot", "device", "conveyor", "slider", "encoder"};
        bool isSendDevice = false;
        for (int j = 0; j < deviceNames.count(); j++)
        {
            if (valuePairs.at(i).contains(deviceNames[j]))
            {
                isSendDevice = true;
                break;
            }
        }

        if (isSendDevice == true)
        {
            QString msg = valuePairs[i + 1];;

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
            return true;
        }
    }

    if (isConveyorGcode(transmitGcode))
    {
        gcodeOrder++;
        SendMsgToDevice(DefaultConveyor, transmitGcode);
        return true;
    }

    if (isSlidingGcode(transmitGcode))
    {
        gcodeOrder++;
        SendMsgToDevice(DefaultSlider, transmitGcode);
        return true;
    }

    if (isEncoderGcode(transmitGcode))
    {
        gcodeOrder++;
        SendMsgToDevice(DefaultEncoder, transmitGcode);
        return true;
    }

    transmitGcode = convertGcodeToSyncConveyor(transmitGcode);

//    updatePositionIntoSystemVariable(transmitGcode);

    SendMsgToDevice(DefaultRobot, transmitGcode);
    gcodeOrder += 1;
    return true;
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

        value1S = getValueOfVariable(value1S);
        value2S = getValueOfVariable(value2S);

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
//    QMutexLocker ml(&mMutex);

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
        else if ((multiplyIndex > -1 || divideIndex > -1 || moduloIndex > -1 || plusIndex > -1 || subIndex > -1 || andIndex > -1 || orIndex > -1 || xorIndex > -1) && isNotNegative(expression))
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

            QString value1Val = getValueOfVariable(value1S);
            QString value2Val = getValueOfVariable(value2S);

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

        else if (eqIndex > -1 || ltIndex > -1 || gtIndex > -1 || neIndex > -1 || leIndex > -1 || geIndex > -1)
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


            value1 = getValueOfVariable(value1S).toFloat();

            value2 = getValueOfVariable(value2S).toFloat();


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

            float value = getValueOfVariable(deleteSpaces(expression)).toFloat();


            if (deleteSpaces(expression) == "NULL")
            {
                value = NULL_NUMBER;
            }


            return QString::number(value);
        }


        return expression;
    }

    return expression;
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

bool GcodeScript::isNotNegative(QString s)
{
    bool isNumeric = false;
    s.toDouble(&isNumeric);

    return !isNumeric;
}

QString GcodeScript::getValueOfVariable(QString name)
{
    name = name.replace("#", "");
//    name = name.replace("_", ".");

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

//    qDebug() << "Full name: " + fullName;

    if (VariableManager::instance().contains(fullName) == true)
    {
        QVariant var = VariableManager::instance().getVar(fullName);
        emit CatchVariable(name, var.toString());
        return var.toString();
    }
    else
    {
        return name;
    }
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

    emit CatchVariable(name, value);

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

QString GcodeScript::convertGcodeToSyncConveyor(QString gcode)
{
//    QMutexLocker ml(&mMutex);

    if (IsConveyorSync == false)
        return gcode;

    if (!(gcode.indexOf("G01 ") > -1 || gcode.indexOf("G1 ") > -1 || gcode.indexOf("G0 ") > -1 || gcode.indexOf("G00 ") > -1 || gcode.indexOf("G04 ") > -1 || gcode.indexOf("G4 ") > -1))
        return gcode;

    float velocity = getValueOfVariable("F").toFloat();
    float accel = getValueOfVariable("A").toFloat();
    float startSpeed = getValueOfVariable("S").toFloat();
    float endSpeed = getValueOfVariable("E").toFloat();
    float conveyorSpeed = getValueOfVariable("ConveyorSpeed").toFloat();

    if (conveyorSpeed == 0)
        return gcode;

    QString conveyorDirection = (getValueOfVariable("ConveyorDirection").toFloat() == 0) ? "X":"Y";

    float currentX = getValueOfVariable("X").toFloat();
    //qDebug() << "current X: " << currentX;
    float currentY = getValueOfVariable("Y").toFloat();
    float currentZ = getValueOfVariable("Z").toFloat();

    float time = 1;

    float desireX = currentX;
    float desireY = currentY;
    float desireZ = currentZ;

    float xy = 0;
    float xyz = 0;

    QString newGcode = "";

    if (gcode.indexOf("G01 ") > -1 || gcode.indexOf("G1 ") > -1 || gcode.indexOf("G0 ") > -1 || gcode.indexOf("G00 ") > -1)
    {
        QStringList paras = gcode.split(' ');

        for(int i = 0; i < paras.size(); i++)
        {
            if (paras.at(i).at(0) == 'X')
            {
                desireX = paras.at(i).mid(1).toFloat();
                //qDebug() << "desire X: " << desireX;
            }
            if (paras.at(i).at(0) == 'Y')
            {
                desireY = paras.at(i).mid(1).toFloat();
            }
            if (paras.at(i).at(0) == 'Z')
            {
                desireZ = paras.at(i).mid(1).toFloat();
            }
            if (paras.at(i).at(0) == 'F')
            {
                velocity = paras.at(i).mid(1).toFloat();
            }
            if (paras.at(i).at(0) == 'A')
            {
                accel = paras.at(i).mid(1).toFloat();
            }
            if (paras.at(i).at(0) == 'S')
            {
                startSpeed = paras.at(i).mid(1).toFloat();
            }
            if (paras.at(i).at(0) == 'E')
            {
                endSpeed = paras.at(i).mid(1).toFloat();
            }
        }

        DeltaXSMoving.setMaxAcc(accel);
        DeltaXSMoving.setVelEnd(endSpeed);
        DeltaXSMoving.setVelStart(startSpeed);
        DeltaXSMoving.setMaxVel(velocity);

        float distanceConveyor = 0;
        float distanceRobot = 0;
        float increaseValue = conveyorSpeed / abs(conveyorSpeed);



        while (abs(distanceConveyor) < 2000)
        {
            xy = qSqrt(qPow(desireX - currentX, 2) + qPow(desireY - currentY, 2));
            xyz = qSqrt(qPow(xy, 2) + qPow(desireZ - currentZ, 2));

            distanceConveyor += increaseValue;

            //qDebug() << "distance+: " << distanceConveyor;

            // S2 = S1^2 - 2.S.S1.cos(alpha) + S^2
            float alpha = atan(abs(desireY - currentY) / abs(desireX - currentX));
            distanceRobot = sqrt(pow(distanceConveyor, 2) - 2 * xyz * distanceConveyor * cos(alpha) + pow(xyz, 2));

            time = abs(distanceConveyor) / abs(conveyorSpeed);
            //qDebug() << "time: " << time;

            DeltaXSMoving.setTarget(distanceRobot);

            DeltaXSMoving.start();

            //qDebug() << "target: " << DeltaXSMoving.t_target + 0.005;

            if ((time) > (DeltaXSMoving.t_target + 0.005))
            {
                break;
            }
        }

        //qDebug() << "distance: " << distanceConveyor;

        if (conveyorDirection == "X")
        {
            desireX += distanceConveyor;
            //qDebug() << "desire X + distance: " << desireX;
        }
        if (conveyorDirection == "Y")
        {
            desireY += distanceConveyor;
        }

        for(int i = 0; i < paras.size(); i++)
        {
            if (paras.at(i).at(0) == 'X')
            {
                paras.replace(i, QString("X%1").arg(desireX));
            }
            if (paras.at(i).at(0) == 'Y')
            {
                paras.replace(i, QString("Y%1").arg(desireY));
            }
            if (paras.at(i).at(0) == 'Z')
            {
                paras.replace(i, QString("Z%1").arg(desireZ));
            }

            newGcode += paras.at(i) + " ";
        }

        if (newGcode.indexOf('X') == -1)
        {
            newGcode += QString(" X%1").arg(desireX);;
        }

        if (newGcode.indexOf('Y') == -1)
        {
            newGcode += QString(" Y%1").arg(desireY);;
        }

        //newGcode = QString("G01 X%1 Y%2 Z%3 F%4 A%5 S%6 E%7").arg(desireX).arg(desireY).arg(desireZ).arg(velocity).arg(accel).arg(startSpeed).arg(endSpeed);
    }

    if (gcode.indexOf("G04 ") > -1 || gcode.indexOf("G4 ") > -1)
    {
        QStringList paras = gcode.split(' ');

        for(int i = 0; i < paras.size(); i++)
        {
            if (paras.at(i).at(0) == 'P')
            {
                time = paras.at(i).mid(1).toFloat() / 1000;
            }
        }

        float distanceConveyor = time * conveyorSpeed;

        //qDebug() << "distance: " << distanceConveyor;

        if (conveyorDirection == "X")
        {
            desireX += distanceConveyor;
            //qDebug() << "desire X G04: " << desireX;
            newGcode = QString("G01 X%1 F%2").arg(desireX).arg(abs(conveyorSpeed));
        }
        if (conveyorDirection == "Y")
        {
            desireY += distanceConveyor;
            newGcode = QString("G01 Y%1 F%2").arg(desireY).arg(abs(conveyorSpeed));;
        }
    }

    return newGcode;
}
