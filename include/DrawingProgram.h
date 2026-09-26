#pragma once
#include <QImage>
#include <QPointF>
#include <QString>
#include <QVector>
#include <QVector3D>

// Robot XY millimetres: origin at canvas centre, +Y up.
namespace DrawingProgram {
using Paths = QVector<QVector<QPointF>>;
constexpr int MaxPoints = 200000;
struct Settings {
    QVector3D a, b, c;
    double travelZ = 0; // Absolute Z; must clear every path vertex.
    double travelSpeed = 100, drawingSpeed = 20, acceleration = 500;
    bool laser = false;
};
bool validatePaths(const Paths& paths, QString* error);
bool rasterPaths(const QImage& image, double width, double height, double spacing,
                 bool dots, Paths* paths, QString* error);
bool generate(const Paths& paths, const Settings& settings, QString* output, QString* error);
}
