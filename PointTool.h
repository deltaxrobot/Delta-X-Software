#ifndef POINTTOOL_H
#define POINTTOOL_H

#include <QTransform>
#include <QPointF>
#include <QMatrix4x4>
#include <cmath>
#include <QPolygonF>
#include <QMatrix>
#include <opencv2/opencv.hpp>
#include <qmath.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class PointTool : public QObject
{
    Q_OBJECT
public:
    static QTransform calculateTransform(const QPointF &P1, const QPointF &P2, const QPointF &P1_prime, const QPointF &P2_prime);
    static QMatrix calculateTransform2(const QPointF &P1, const QPointF &P2, const QPointF &P1_prime, const QPointF &P2_prime);
    static cv::Mat calculateMatrix(const QPolygonF &sourcePolygon, const QPolygonF &destPolygon);
    static  cv::Mat performAffineTransformation(const QPolygonF &sourcePolygon, const QPolygonF &destPolygon);
    static QPointF GetCenterOfPolygon(const QPolygonF &polygon);
};

#endif // POINTTOOL_H
