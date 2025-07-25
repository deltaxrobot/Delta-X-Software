#include "robot.h"

Robot::Robot(QString COM, int baudrate, bool is_open, QObject *parent) : Device(COM, baudrate, "IsDelta", "YesDelta", is_open, parent)
{
//    qDebug() << "Robot init";
    connect(this, SIGNAL(receivedMsg(QString, QString)), this, SLOT(ProcessResponse(QString, QString)));
    this->scurve_tool = Scurve_Interpolator();

    StepVector = QVector3D(0, 0, 0);

    X = 0;
    Y = 0;
    Z = 0;
    W = 0;
    U = 0;
    V = 0;
    F = 500;
    A = 8000;
    S = 30;
    E = 40;
    J = 255000;

    done_msg = "Ok";

    path_type = "line";
    path_vel = 100;

    jsonObject["device"] = "robot";

    GetInfo();
}

Robot::~Robot()
{

}

QString Robot::SendGcode(QString gcode, bool is_wait, int time_out)
{
    if (checkJoggingCmd(gcode))
    {
        IsGcodeDone = true;
        emit receivedMsg(idName, "Ok");
        return "";
    }

    if (checkSetSyncPathCmd(gcode))
    {
        IsGcodeDone = true;
        emit receivedMsg(idName, "Ok");
        return "";
    }

    gcode = syncGcode(gcode);

    WriteData(gcode);
    emit Log(idName, gcode, 1);

    last_gcode = now_gcode;
    now_gcode = gcode;

    jsonObject["gcode"] = now_gcode;

    bool isMovingGcode = this->getPara(gcode);

    GetInfo();

    if (is_wait)
    {
        serialPort->blockSignals(true);
        if (isMovingGcode)
        {
            this->calMoveTime();
            time_out = this->scurve_tool.t_target * 1000 + 1000;
        }

        QString response = this->GetResponse(time_out);
//        qDebug() << response;
        serialPort->blockSignals(false);
        return response;
    }
    else
    {

    }

    return "";
}

void Robot::ProcessResponse(QString id, QString response) {

    jsonObject["response"] = response;
//    emit Log(idName, response, 0);

    ProcessNextMove();

    if (now_gcode.count("G28") > 0 || now_gcode.count("M85"))
    {
        SendGcode("Position");
        return;
    }

//    qDebug() << response;

    if (now_gcode.count("Position") > 0) {
        if (response.count(",") > 1) {
            QStringList paras = response.split(",");
            if (last_gcode.count("G28") > 0)
            {
                for (int i = 0; i < paras.size(); i++)
                {
                    if (i == 0) {
                        X = home_X = paras[i].toFloat();
                    }
                    if (i == 1) {
                        Y = home_Y = paras[i].toFloat();
                    }
                    if (i == 2) {
                        Z = home_Z = paras[i].toFloat();
                    }
                    if (i == 3) {
                        W = home_W = paras[i].toFloat();
                    }
                    if (i == 4) {
                        U = home_U = paras[i].toFloat();
                    }
                    if (i == 5) {
                        V = home_V = paras[i].toFloat();
                    }
                }

                VariableManager::instance().addVar(QString("%1.HOME_X").arg(idName), home_X);
                VariableManager::instance().addVar(QString("%1.HOME_Y").arg(idName), home_Y);
                VariableManager::instance().addVar(QString("%1.HOME_Z").arg(idName), home_Z);
                VariableManager::instance().addVar(QString("%1.HOME_W").arg(idName), home_W);
                VariableManager::instance().addVar(QString("%1.HOME_U").arg(idName), home_U);
                VariableManager::instance().addVar(QString("%1.HOME_V").arg(idName), home_V);
            }

            else
            {
                for (int i = 0; i < paras.size(); i++)
                {
                    if (i == 0) {
                        X = paras[i].toFloat();
                    }
                    if (i == 1) {
                        Y = paras[i].toFloat();
                    }
                    if (i == 2) {
                        Z = paras[i].toFloat();
                    }
                    if (i == 3) {
                        W = paras[i].toFloat();
                    }
                    if (i == 4) {
                        U = paras[i].toFloat();
                    }
                    if (i == 5) {
                        V = paras[i].toFloat();
                    }
                }
            }

            saveParaVar();

            GetInfo();
        }
    }
}

bool Robot::getPara(QString gcode)
{
    QStringList paras = gcode.split(" ");

    if (paras[0].indexOf("G01") < 0 && paras[0].indexOf("G1") < 0 && paras[0].indexOf("M203") < 0 && paras[0].indexOf("M204") < 0 && paras[0].indexOf("M205") < 0)
        return false;

    old_X = X;
    old_Y = Y;
    old_Z = Z;

    for (int i = 0; i < paras.size(); ++i)
    {
        QString para = paras.at(i);
        float value = para.mid(1).toFloat();
        VariableManager::instance().Prefix = ProjectName;

        if (para[0] == 'X')
            X = value;
        else if (para[0] == 'Y')
            Y = value;
        else if (para[0] == 'Z')
            Z = value;
        else if (para[0] == 'W')
            W = value;
        else if (para[0] == 'U')
            U = value;
        else if (para[0] == 'V')
            V = value;
        else if (para[0] == 'F')
        {
//            if (isSyncDelay == false)
            F = value;
        }
        else if (para[0] == 'A')
            A = value;
        else if (para[0] == 'S')
            S = value;
        else if (para[0] == 'E')
            E = value;
        else if (para[0] == 'J')
            J = value;
    }

    saveParaVar();

    scurve_tool.setMaxAcc(A);
    scurve_tool.setMaxVel(F);
    scurve_tool.setMaxJerk(J);
    scurve_tool.setVelStart(S);
    scurve_tool.setVelEnd(E);

    return true;
}

void Robot::calMoveTime()
{
    float xy = sqrt(pow(this->X - this->old_X, 2) + pow(this->Y - this->old_Y, 2));
    float xyz = sqrt(pow(xy, 2) + pow(this->Z - this->old_Z, 2));
    this->scurve_tool.p_target = xyz;
    this->scurve_tool.start();
}

bool Robot::checkSetSyncPathCmd(QString cmd)
{
    // SYNC (1, 2, 1.5)
    // SYNC (X, Y, Z)

    QRegExp rx("\\s*SYNC\\s*\\(([-]?\\d+\\.?\\d*),?\\s*([-]?\\d+\\.?\\d*)\\)|\\s*SYNC\\s*\\(([-]?\\d+\\.?\\d*),?\\s*([-]?\\d+\\.?\\d*),?\\s*([-]?\\d+\\.?\\d*)\\)");

    if (!rx.exactMatch(cmd))
    {
        return false;
    }

    QStringList list = rx.capturedTexts();
    if (list[1] != "") {
        path_vel = list[1].toFloat();
        path_angle = list[2].toFloat();

        path_angle = qDegreesToRadians(path_angle);

        // Tính toán tọa độ X và Y
        double x = path_vel * qCos(path_angle);
        double y = path_vel * qSin(path_angle);

        sync_vector = QVector3D(x, y, 0);
    }

    // Extract the values of X, Y, and Z from the command string, if present
    if (list[4] != "")
    {
        float x = list[3].toFloat();
        float y = list[4].toFloat();
        float z = list[5].toFloat();
        sync_vector = QVector3D(x, y, z);
        path_vel = sync_vector.length();
        path_angle = qAcos(x / path_vel);
    }

    // Print the results
//    qDebug() << "Speed: " << path_vel << ", Angle: " << qRadiansToDegrees(path_angle) << " degrees.";
    return true;
}

QString Robot::syncGcode(QString cmd)
{
    if (!cmd.contains("SYNC"))
        return cmd;

    QString result = cmd;
    QStringList params = cmd.split(' ');

    old_X = X;
    old_Y = Y;
    old_Z = Z;

    if (cmd.contains("G01"))
    {
        // Extract the values of X, Y, Z, W, U, V, F, A, and J from the command string
        for (int i = 1; i < params.size(); i++)
        {
            QString param = params[i];
            if (param.startsWith("X"))
            {
                X = param.mid(1).toFloat();
            } else if (param.startsWith("Y"))
            {
                Y = param.mid(1).toFloat();
            } else if (param.startsWith("Z"))
            {
                Z = param.mid(1).toFloat();
            } else if (param.startsWith("W"))
            {
                W = param.mid(1).toFloat();
            } else if (param.startsWith("U"))
            {
                U = param.mid(1).toFloat();
            } else if (param.startsWith("V"))
            {
                V = param.mid(1).toFloat();
            } else if (param.startsWith("F"))
            {
                F = param.mid(1).toFloat();
            } else if (param.startsWith("A"))
            {
                A = param.mid(1).toFloat();
            } else if (param.startsWith("J"))
            {
                J = param.mid(1).toFloat();
            }
        }

        scurve_tool.setMaxVel(F);
        scurve_tool.setMaxAcc(A);
        scurve_tool.setVelStart(S);
        scurve_tool.setVelEnd(E);
        scurve_tool.setMaxJerk(J);

//        float new_x, new_y;
//        std::pair<double, double> new_point = scurve_tool.find_sync_point(old_X, old_Y, old_Z, X, Y, Z, path_vel, path_angle, O);
//        new_x = round(float(new_point.first) * 100) / 100;
//        new_y = round(float(new_point.second) * 100) / 100;

        QVector3D newPosition = calculateSyncPosition(QVector3D(old_X, old_Y, old_Z), QVector3D(X, Y, Z), sync_vector);

        if (robotModel == "Delta X S")
        {
            return QString("G01 X%1 Y%2 Z%3 W%4 F%5 A%6 S%7 E%8 J%9").arg(newPosition.x()).arg(newPosition.y()).arg(newPosition.z()).arg(W).arg(F).arg(A).arg(S).arg(E).arg(J);
        }
        else if (robotModel == "Delta X 2" || robotModel == "Delta X 1")
        {
            return QString("G01 X%1 Y%2 Z%3").arg(newPosition.x()).arg(newPosition.y()).arg(newPosition.z());
        }
    }
    else if (cmd.contains("G04"))
    {
        QRegExp rx("P(\\d+\\.?\\d*)");

        if (rx.indexIn(cmd) != -1)
        {
            QString match = rx.cap(1);
            float time_ms = match.toInt();

            float distance;
            float new_x, new_y;

            QVector3D moving = sync_vector * (float(time_ms) / 1000);
            new_x = X + moving.x();
            new_y = Y + moving.y();

//            isSyncDelay = true;

            return QString("G01 X%1 Y%2 F%3").arg(new_x).arg(new_y).arg(abs(path_vel));
        }
    }
    return cmd;
}

double Robot::calculateMovingTime(double distance)
{
    if (robotModel == "Delta X S" || robotModel == "Delta X 3")
    {
        scurve_tool.p_target = distance;
        scurve_tool.start();

        return scurve_tool.t_target;
    }
    else if (robotModel == "Delta X 2")
    {
        float t1, t2, t3, t_total;
        float v_max = F;
        float a_max = A;
        float s = distance;
        float v_start = S;
        float v_end = S;

        if (v_max > 900)
            v_max = 900;
        if (a_max > 3000)
            a_max = 3000;

        t1 = (v_max - v_start) / a_max;
        t3 = (v_max - v_end) / a_max;
        
        float s1, s3;
        s1 = s3 = v_start * t1 + 0.5 * a_max * t1 * t1;

        if (s > s1 + s3)
        {
            float s2 = s - s1 - s3;
            t2 = s2 / v_max;

            t_total = t1 + t2 + t3;
        }
        else
        {
            float vpeak_squared = a_max * s + (v_start*v_start + v_end*v_end) / 2.0;
            float new_v_max = sqrt(vpeak_squared);
            float t1 = (new_v_max - v_start) / a_max;

            t_total = t1 * 2;
        }

        return t_total;
    }
    else
    {
        float t1, t2, t3, t_total;
        float v_max = F;
        float a_max = A;
        float s = distance;

        t1 = (v_max) / a_max;
        t3 = (v_max) / a_max;

        float s1, s3;
        s1 = s3 = 0.5 * a_max * t1 * t1;

        if (s > s1 + s3)
        {
            float s2 = s - s1 - s3;
            t2 = s2 / v_max;

            t_total = t1 + t2 + t3;
        }
        else
        {
            float new_v_max = sqrt(a_max * s);
            float t1 = (new_v_max) / a_max;

            t_total = t1 * 2;
        }

        return t_total;
    }
    
}

QVector3D Robot::calculateSyncPosition(QVector3D robotPos, QVector3D objectPos, QVector3D beltVelocity, double tolerance) {
    double t, t_new, distance_initial, distance_new;
    QVector3D estimatedObjectPos;

    // Ước tính khoảng cách ban đầu và thời gian di chuyển
    distance_initial = (objectPos - robotPos).length();
    t = calculateMovingTime(distance_initial);

    do {
        // Cập nhật vị trí mới của vật
        estimatedObjectPos = objectPos + beltVelocity * t;

        // Tính khoảng cách mới
        distance_new = (estimatedObjectPos - robotPos).length();

        // Cập nhật lại ước tính thời gian
        t_new = calculateMovingTime(distance_new);

        // Kiểm tra điều kiện dừng
        if (std::abs(t_new - t) < tolerance) {
            break;
        }

        t = t_new;

    } while (true);

    return estimatedObjectPos;
}

QString Robot::GetInfo()
{
    jsonObject["id"] = ID();
    jsonObject["id_name"] = idName;
    jsonObject["home_x"] = home_X;
    jsonObject["home_y"] = home_Y;
    jsonObject["home_z"] = home_Z;
    jsonObject["home_w"] = home_W;
    jsonObject["home_u"] = home_U;
    jsonObject["home_v"] = home_V;

    jsonObject["x"] = X;
    jsonObject["y"] = Y;
    jsonObject["z"] = Z;
    jsonObject["w"] = W;
    jsonObject["u"] = U;
    jsonObject["v"] = V;

    jsonObject["F"] = F;
    jsonObject["A"] = A;
    jsonObject["S"] = S;
    jsonObject["E"] = E;
    jsonObject["J"] = J;

    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    QString jsonString = jsonDocument.toJson(QJsonDocument::Indented);

    emit infoReady(jsonString);

    return jsonString;
}

void Robot::saveParaVar()
{
    VariableManager::instance().Prefix = ProjectName;
    VariableManager::instance().addVar(QString("%1.X").arg(idName), X);
    VariableManager::instance().addVar(QString("%1.Y").arg(idName), Y);
    VariableManager::instance().addVar(QString("%1.Z").arg(idName), Z);
    VariableManager::instance().addVar(QString("%1.W").arg(idName), W);
    VariableManager::instance().addVar(QString("%1.U").arg(idName), U);
    VariableManager::instance().addVar(QString("%1.V").arg(idName), V);
    VariableManager::instance().addVar(QString("%1.F").arg(idName), F);
    VariableManager::instance().addVar(QString("%1.A").arg(idName), A);
    VariableManager::instance().addVar(QString("%1.J").arg(idName), J);
    VariableManager::instance().addVar(QString("%1.OLD_X").arg(idName), old_X);
    VariableManager::instance().addVar(QString("%1.OLD_Y").arg(idName), old_Y);
    VariableManager::instance().addVar(QString("%1.OLD_Z").arg(idName), old_Z);

}

QString Robot::SetInput(int pin)
{
    QString gcode = QString("M07 I%1").arg(pin);
    QString state = SendGcode(gcode);
    QStringList paras = state.split(" ");
    for (QString para : paras)
    {
        if (para[0] == 'V') {
            return para.mid(1);
        }
    }

    return "";
}

void Robot::SetOutput(int pin, bool state)
{
    QString gcode;
    if (state != 0) {
        gcode = QString("M03 S%1").arg(pin);
    } else {
        gcode = QString("M05 S%1").arg(pin);
    }
    SendGcode(gcode);
}

void Robot::GoHome()
{
    SendGcode("G28");
    SendGcode("Position");
}

void Robot::Sleep(int time_ms=1000, bool sync=false)
{
    if (sync == false)
    {
        SendGcode(QString("G04 P%1").arg(time_ms));
    }
    else
    {
        float new_x, new_y;
        float old_F;

        QVector3D moving = sync_vector * (float(time_ms) / 1000);
        new_x = X + moving.x();
        new_y = Y + moving.y();
        old_F = F;
        Move(round(float(new_x)), round(float(new_y)), NULL, NULL, NULL, NULL, F, NULL, NULL, NULL, NULL, false, 0);
        F = old_F;
        scurve_tool.setMaxVel(F);
    }
}

void Robot::Move(float x = 0, float y = 0, float z = 0, float w = 0, float u = 0, float v = 0, float f = 0, float a = 0, float s = 0, float e = 0, float j = 0, bool sync = false, float time_offset = 0)
{
    QString gcode = "G01";
    old_X = X;
    old_Y = Y;
    old_Z = Z;

    if (x != NULL)
    {
        X = x;
        gcode += " X" + QString::number(X);
    }
    if (y != NULL)
    {
        Y = y;
        gcode += " Y" + QString::number(Y);
    }
    if (z != NULL)
    {
        Z = z;
        gcode += " Z" + QString::number(Z);
    }
    if (w != NULL)
    {
        W = w;
        gcode += " W" + QString::number(W);
    }
    if (u != NULL)
    {
        U = u;
        gcode += " U" + QString::number(U);
    }
    if (v != NULL)
    {
        V = v;
        gcode += " V" + QString::number(V);
    }
    if (f != NULL)
    {
        F = f;
        scurve_tool.setMaxVel(F);
        gcode += " F" + QString::number(F);
    }
    if (a != NULL)
    {
        A = a;
        scurve_tool.setMaxAcc(A);
        gcode += " A" + QString::number(A);
    }
    if (s != NULL)
    {
        S = s;
        scurve_tool.setVelStart(S);
        gcode += " S" + QString::number(S);
    }
    if (E != NULL)
    {
        E = E;
        scurve_tool.setVelEnd(E);
        gcode += " E" + QString::number(E);
    }
    if (J != NULL)
    {
        J = J;
        scurve_tool.setMaxJerk(J);
        gcode += " J" + QString::number(J);
    }

    if (!sync)
    {
        SendGcode(gcode);
    }
    else
    {
        float new_x, new_y;
        std::pair<double, double> new_point = scurve_tool.find_sync_point(old_X, old_Y, old_Z, X, Y, Z, path_vel, path_angle, time_offset);
        new_x = round(float(new_point.first) * 100) / 100;
        new_y = round(float(new_point.second) * 100) / 100;

        SendGcode(QString("G01 X%1 Y%2 Z%3 W%4 F%5 A%6 S%7 E%8 J%9").arg(new_x).arg(new_y).arg(Z).arg(W).arg(F).arg(A).arg(S).arg(E).arg(J));
    }
}

void Robot::MoveStep(QString direction, float step) {
    direction = direction.toLower();
    if (direction == "left") {
        QString pos = "X" + QString::number(X - step);
        SendGcode("G01 " + pos);
    }
    else if (direction == "right") {
        QString pos = "X" + QString::number(X + step);
        SendGcode("G01 " + pos);
    }
    else if (direction == "forward") {
        QString pos = "Y" + QString::number(Y + step);
        SendGcode("G01 " + pos);
    }
    else if (direction == "backward") {
        QString pos = "Y" + QString::number(Y - step);
        SendGcode("G01 " + pos);
    }
    else if (direction == "up") {
        QString pos = "Z" + QString::number(Z + step);
        SendGcode("G01 " + pos);
    }
    else if (direction == "down") {
        QString pos = "Z" + QString::number(Z - step);
        SendGcode("G01 " + pos);
    }
}

void Robot::MovePoint(QVector3D point)
{
    Move(point.x(), point.y(), point.z());
}

void Robot::SetRobotModel(QString robot)
{
    robotModel = robot;
}

bool Robot::checkJoggingCmd(QString cmd)
{
    QRegularExpression re("^\\s*jogging\\s*\\(\\s*([+-]?\\d+(?:\\.\\d+)?)\\s*,\\s*([+-]?\\d+(?:\\.\\d+)?)\\s*,\\s*([+-]?\\d+(?:\\.\\d+)?)\\s*\\)\\s*$");

    QRegularExpressionMatch match = re.match(cmd);
    if (!match.hasMatch()) {
        // Không đúng format
        return false;
    }

    // Nếu match, chuyển sang số thực
    float x = match.captured(1).toDouble();
    float y = match.captured(2).toDouble();
    float z = match.captured(3).toDouble();

    StepVector.setX(x);
    StepVector.setY(y);
    StepVector.setZ(z);

    return true;
}



void Robot::ProcessNextMove()
{
    if (IsGcodeDone == false || StepVector == QVector3D(0,0,0))
        return;

    QVector3D desPoint = StepVector + QVector3D(X, Y, Z);
    MovePoint(desPoint);
}

