#ifndef ROBOT_H
#define ROBOT_H

#include <QObject>
#include "device/device.h"
#include <string>
#include <math.h>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <ScurveInterpolator.h>
#include <QtMath>
#include <QVector3D>
#include <VariableManager.h>
#include <QVector3D>

class Robot : public Device
{
    Q_OBJECT
public:
    Robot(QString COM = "auto", int baudrate = 115200, bool is_open = true, QObject *parent = nullptr);
    ~Robot();

    QString SetInput(int pin);
    void SetOutput(int pin, bool state);
    void MovePoint(QVector3D point);
    void SetRobotModel(QString robot);
    void ProcessNextMove();

    float X,Y,Z,W,U,V,F,S,E,A,J;

signals:
    void Log(QString device, QString msg, int direction);

public slots:
    QString SendGcode(QString gcode = "G28", bool is_wait = false, int time_out = 10000);
    void ProcessResponse(QString id, QString response = "");
    void Sleep(int time_ms, bool sync);
    void GoHome();
    void Move(float x, float y, float z, float w, float u, float v, float f, float a, float s, float e, float j, bool sync, float time_offset);
    void MoveStep(QString direction, float step);
    QString GetInfo();

private:
    QVector3D StepVector;
    QString done_msg;
    QString last_gcode;
    QString now_gcode;
    QString path_type;
    float path_vel;
    float path_angle;
    QVector3D sync_vector;
    Scurve_Interpolator scurve_tool;

    float home_X, home_Y, home_Z, home_W, home_U, home_V;
    float old_X, old_Y, old_Z;
    QTimer* timer;
    bool isSyncDelay = false;

    QString robotModel = "Delta X 2";

    void saveParaVar();
    bool getPara(QString gcode);
    void calMoveTime();
    bool checkSetSyncPathCmd(QString cmd);
    bool checkJoggingCmd(QString cmd);
    QString syncGcode(QString cmd);
    double calculateMovingTime(double distance);
    QVector3D calculateSyncPosition(QVector3D robotPos, QVector3D objectPos, QVector3D beltVelocity, double tolerance = 1e-3);

};


#endif // ROBOT_H
