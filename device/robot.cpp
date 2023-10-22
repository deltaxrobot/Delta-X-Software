#include "robot.h"

Robot::Robot(QString COM, int baudrate, bool is_open, QObject *parent) : Device(COM, baudrate, "IsDelta", "YesDelta", is_open, parent)
{
    qDebug() << "Robot init";
    connect(this, SIGNAL(receivedMsg(QString, QString)), this, SLOT(ProcessResponse(QString, QString)));
    this->scurve_tool = Scurve_Interpolator();

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
    O = 0;

    done_msg = "Ok";

    path_type = "line";
    path_vel = 100;
    path_angle = 0;
    path_rad_angle = 0;

    jsonObject["device"] = "robot";

    GetInfo();
}

Robot::~Robot()
{

}

QString Robot::SendGcode(QString gcode, bool is_wait, int time_out)
{
    if (checkSetSyncPathCmd(gcode))
    {
        emit receivedMsg(idName, "Ok");
        return "";
    }

    gcode = syncGcode(gcode);

    WriteData(gcode);

//    if (gcode.indexOf("G04") < 0)
//        qDebug() << gcode;
    last_gcode = now_gcode;
    now_gcode = gcode;
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
        qDebug() << response;
        serialPort->blockSignals(false);
        return response;
    }
    else
    {

    }

    return "";
}

void Robot::ProcessResponse(QString id, QString response) {

    if (now_gcode.count("G28") > 0 || now_gcode.count("M85"))
    {
        SendGcode("Position");
    }

    qDebug() << response;

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
        if (para[0] == 'Y')
            Y = value;
        if (para[0] == 'Z')
            Z = value;
        if (para[0] == 'W')
            W = value;
        if (para[0] == 'U')
            U = value;
        if (para[0] == 'V')
            V = value;
        if (para[0] == 'F')
        {
            if (isSyncDelay == false)
                F = value;
            else
                isSyncDelay = true;
        }
        if (para[0] == 'A')
            A = value;
        if (para[0] == 'S')
            S = value;
        if (para[0] == 'E')
            E = value;
        if (para[0] == 'S')
            S = value;
        if (para[0] == 'E')
            E = value;
        if (para[0] == 'J')
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
    float speed = 0;
    float angle = 0;
    if (list[1] != "") {
        speed = list[1].toFloat();
        angle = list[2].toFloat();
    }

    // Extract the values of X, Y, and Z from the command string, if present
    if (list[4] != "")
    {
        float x = list[4].toFloat();
        float y = list[5].toFloat();
        float z = list[6].toFloat();
        QVector3D velocity(x, y, z);
        speed = velocity.length();
        angle = qRadiansToDegrees(qAtan2(velocity.y(), velocity.x()));
    }

    SetSyncPath("line", speed, angle);

    // Print the results
    qDebug() << "Speed: " << speed << ", Angle: " << angle << " degrees.";
    return true;
}

QString Robot::syncGcode(QString cmd)
{
    QString result = cmd;
    QStringList params = cmd.split(' ');

    old_X = X;
    old_Y = Y;
    old_Z = Z;

    // Check if the command contains "SYNC"
    if (cmd.contains("SYNC"))
    {
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
            float new_x, new_y;
            std::pair<double, double> new_point = scurve_tool.find_sync_point(old_X, old_Y, old_Z, X, Y, Z, path_vel, path_angle, O);
            new_x = round(float(new_point.first) * 100) / 100;
            new_y = round(float(new_point.second) * 100) / 100;

            return QString("G01 X%1 Y%2 Z%3 W%4 F%5 A%6 S%7 E%8 J%9").arg(new_x).arg(new_y).arg(Z).arg(W).arg(F).arg(A).arg(S).arg(E).arg(J);
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

                distance = path_vel * (float(time_ms) / 1000);
                new_x = X + distance * cos(path_rad_angle);
                new_y = Y + distance * sin(path_rad_angle);

                isSyncDelay = true;

                return QString("G01 X%1 Y%2 F%3").arg(new_x).arg(new_y).arg(abs(path_vel));
            }
        }
    }
    return cmd;
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
    VariableManager::instance().addVar(QString("%1.O").arg(idName), O);
    VariableManager::instance().addVar(QString("%1.HOME_X").arg(idName), home_X);
    VariableManager::instance().addVar(QString("%1.HOME_Y").arg(idName), home_Y);
    VariableManager::instance().addVar(QString("%1.HOME_Z").arg(idName), home_Z);
    VariableManager::instance().addVar(QString("%1.HOME_W").arg(idName), home_W);
    VariableManager::instance().addVar(QString("%1.HOME_U").arg(idName), home_U);
    VariableManager::instance().addVar(QString("%1.HOME_V").arg(idName), home_V);
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
        float distance;
        float new_x, new_y;
        float old_F;

        distance = path_vel * (float(time_ms) / 1000);
        new_x = X + distance * cos(path_rad_angle);
        new_y = Y + distance * sin(path_rad_angle);
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
        gcode += " S" + QString::number(E);
    }
    if (E != NULL)
    {
        E = E;
        scurve_tool.setVelEnd(E);
        gcode += " E" + QString::number(S);
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

void Robot::SetSyncPath(QString path = "line", float con_vel = 100, float con_angle = 0)
{
    path_type = path;
    path_vel = con_vel;
    path_angle = con_angle;
    path_rad_angle = qDegreesToRadians(con_angle);
}
