#ifndef ROBOT_H
#define ROBOT_H

#include <QString>

class Robot
{
public:
    Robot();

    QString Name;
    int ID;
    float X_Location;
    float Y_Location;
    float Z_Location;

    float X;
    float Y;
    float Z;
    float W;
    float U;
    float V;

    float Velocity;
    float Acceleration;
    float Jerk;
    float Begin_Velocity;
    float End_Velocity;
};

#endif // ROBOT_H
