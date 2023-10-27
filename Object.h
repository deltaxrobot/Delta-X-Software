#ifndef OBJECT
#define OBJECT

#include <QObject>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "UnityTool.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QLineEdit>

struct MappingFloat
{
    float Real;
    float Image;
};

struct MappingRange
{
    MappingFloat Min;
    MappingFloat Max;
};

class Object
{
public:
    Object(cv::RotatedRect rotateRec)
    {
        X.Image = rotateRec.center.x;
        Y.Image = rotateRec.center.y;

        if (rotateRec.size.height < rotateRec.size.width)
        {
            Width.Image = rotateRec.size.height;
            Length.Image = rotateRec.size.width;
            Angle.Image = rotateRec.angle;
        }
        else
        {
            Width.Image = rotateRec.size.width;
            Length.Image = rotateRec.size.height;
            Angle.Image = rotateRec.angle + 90;
        }

        ToPoints();
    }

    Object()
    {
        X.Real = 100;
        Y.Real = 100;
        Width.Real = 50;
        Length.Real = 100;
        Height.Real = 10;
        Angle.Real = 0;

        ToPoints();
    }

    void CopyFrom(Object obj)
    {
        X = obj.X;
        Y = obj.Y;
        Height = obj.Height;
        Width = obj.Width;
        Length = obj.Length;
        Angle = obj.Angle;

        RangeWidth = obj.RangeWidth;
        RangeHeight = obj.RangeHeight;
        RangeLength = obj.RangeLength;
    }

    void Move(QPointF offset)
    {
        X.Real += offset.x();
        Y.Real += offset.y();
    }

    void Map(Object &object, QMatrix matrix)
    {
        QPointF PPoint(object.X.Image, 0 - object.Y.Image);
        QPointF RPoint = matrix.map(PPoint);
        QLineF rHeight = matrix.map(QLineF(QPointF(0, 0), QPointF(0, object.Height.Image)));
        QLineF rWidth = matrix.map(QLineF(QPointF(0, 0), QPointF(0, object.Width.Image)));
        QLineF rLength = matrix.map(QLineF(QPointF(0, 0), QPointF(0, object.Length.Image)));
        QLineF pAngle = QLineF(QPointF(0, 0), QPointF(0, 100));
        pAngle.setAngle(object.Angle.Image);
        QLineF rAngle = matrix.map(pAngle);

        object.X.Real = RPoint.x();
        object.Y.Real = RPoint.y();
        object.Height.Real = rHeight.length();
        object.Width.Real = rWidth.length();
        object.Length.Real = rLength.length();
        object.Angle.Real = rAngle.angle();
    }

    void Map(QMatrix matrix)
    {
        QPointF PPoint(X.Image, 0 - Y.Image);
        QPointF RPoint = matrix.map(PPoint);
        QLineF rHeight = matrix.map(QLineF(QPointF(0, 0), QPointF(0, Height.Image)));
        QLineF rWidth = matrix.map(QLineF(QPointF(0, 0), QPointF(0, Width.Image)));
        QLineF rLength = matrix.map(QLineF(QPointF(0, 0), QPointF(0, Length.Image)));
        QLineF pAngle = QLineF(QPointF(0, 0), QPointF(0, 100));
        pAngle.setAngle(Angle.Image);
        QLineF rAngle = matrix.map(pAngle);

        X.Real = RPoint.x();
        Y.Real = RPoint.y();
        Height.Real = rHeight.length();
        Width.Real = rWidth.length();
        Length.Real = rLength.length();
        Angle.Real = rAngle.angle();


    }

    bool IsSame(Object object, float error)
    {
        if (abs(X.Real - object.X.Real) > Length.Real * error)
            return false;

        if (abs(Y.Real - object.Y.Real) > Length.Real * error)
            return false;

        if (abs(Length.Real - object.Length.Real) > Length.Real * error)
            return false;

        if (abs(Width.Real - object.Width.Real) > Width.Real * error)
            return false;

        return true;
    }

    bool IsSameType(Object obj)
    {
        if (obj.Length.Image >= RangeLength.Min.Image && obj.Length.Image <= RangeLength.Max.Image)
        {
            if (obj.Width.Image >= RangeWidth.Min.Image && obj.Width.Image <= RangeWidth.Max.Image)
            {
                return true;
            }
        }

        return false;
    }

    cv::Point2f* ToPoints()
    {
        RotateRec.center.x = X.Image;
        RotateRec.center.y = Y.Image;
        RotateRec.size.height = Width.Image;
        RotateRec.size.width = Length.Image;
        RotateRec.angle = Angle.Image;

        RotateRec.points(points);

        for (int i = 0; i < 4; i++)
        {
            if (points[i].x < 0)
            {
                points[i].x = 0;
            }
            if (points[i].y < 0)
            {
                points[i].y = 0;
            }
        }

        return points;
    }

    QPolygonF ToPolygon()
    {
        ToPoints();

        QPolygonF poly;

        for(int i = 0; i < 4; i++)
        {
            poly.append(QPointF(points[i].x, points[i].y));
        }

        return poly;
    }

    MappingFloat X;
    MappingFloat Y;
    MappingFloat Height;
    MappingFloat Width;
    MappingFloat Length;
    MappingFloat Angle;
    QString Type = "Type 1";

    MappingRange RangeHeight;
    MappingRange RangeWidth;
    MappingRange RangeLength;

    QPointF Offset;

    cv::RotatedRect RotateRec;

private:

    cv::Point2f points[4];
};

#endif
