#ifndef PARAMETER
#define PARAMETER

#include <QObject>

struct RobotPara
{
    float X = 0;
    float Y = 0;
    float Z = -200;
    float W = 0;
    float U = 0;
    float V = 0;
    float F = 200;
    float A = 1200;
    float S = 50;
    float E = 50;
    float J = 300000;

    float XHome = 0;
    float YHome = 0;
    float ZHome = -200;
    float WHome = 0;
    float UHome = 0;
    float VHome = 0;
    float Step = 10;

    void Set(QString key, float value)
    {
        if (key == "X")
        {
            X = value;
        }
        if (key == "Y")
        {
            Y = value;
        }
        if (key == "Z")
        {
            Z = value;
        }
        if (key == "W")
        {
            W = value;
        }
        if (key == "U")
        {
            U = value;
        }
        if (key == "V")
        {
            V = value;
        }
        if (key == "F")
        {
            F = value;
        }
        if (key == "A")
        {
            A = value;
        }
        if (key == "S")
        {
            S = value;
        }
        if (key == "E")
        {
            E = value;
        }
        if (key == "J")
        {
            J = value;
        }
    }

    float Get(QString key)
    {
        if (key == "X")
        {
            return X;
        }
        if (key == "Y")
        {
            return Y;
        }
        if (key == "Z")
        {
            return Z;
        }
        if (key == "W")
        {
            return W;
        }
        if (key == "U")
        {
            return U;
        }
        if (key == "V")
        {
            return V;
        }
        if (key == "F")
        {
            return F;
        }
        if (key == "A")
        {
            return A;
        }
        if (key == "S")
        {
            return S;
        }
        if (key == "E")
        {
            return E;
        }
        if (key == "J")
        {
            return J;
        }

        return 0;
    }

};

Q_DECLARE_METATYPE(RobotPara)

#endif
