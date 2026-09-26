#include "DrawingProgram.h"
#include <QStringList>
#include <algorithm>
#include <cmath>

namespace DrawingProgram {
namespace {
bool fail(QString* error, const QString& text) { if (error) *error = text; return false; }
QString number(double value) { return QString::number(std::abs(value) < 0.0005 ? 0 : value, 'f', 3); }
bool finite(const QVector3D& p) { return std::isfinite(p.x()) && std::isfinite(p.y()) && std::isfinite(p.z()); }
}
bool validatePaths(const Paths& paths, QString* error)
{
    if (paths.isEmpty()) return fail(error, "There are no drawing paths.");
    qint64 count = 0;
    for (const auto& path : paths) {
        if (path.isEmpty()) return fail(error, "A drawing path is empty.");
        count += path.size();
        if (count > MaxPoints) return fail(error, "Too many points. Increase spacing or simplify the image.");
        for (const auto& p : path)
            if (!std::isfinite(p.x()) || !std::isfinite(p.y()) || std::abs(p.x()) > 100000 || std::abs(p.y()) > 100000)
                return fail(error, "Drawing coordinates must be finite and within +/-100000 mm.");
    }
    return true;
}
bool rasterPaths(const QImage& source, double width, double height, double spacing,
                 bool dots, Paths* paths, QString* error)
{
    if (!paths || source.isNull()) return fail(error, "Load an image first.");
    if (!std::isfinite(width) || !std::isfinite(height) || !std::isfinite(spacing) ||
        width <= 0 || height <= 0 || spacing <= 0)
        return fail(error, "Width, height and spacing must be positive finite numbers.");
    const double columns = std::ceil(width / spacing), rows = std::ceil(height / spacing);
    if (columns * rows > MaxPoints / 2 || columns > 10000 || rows > 10000)
        return fail(error, "The raster is too dense. Increase spacing or reduce its dimensions.");
    const int w = std::max(1, int(columns)), h = std::max(1, int(rows));
    const QImage image = source.scaled(w, h, Qt::IgnoreAspectRatio, Qt::FastTransformation);
    Paths converted;
    const double dx = width / w, dy = height / h;
    for (int row = 0; row < h; ++row) {
        QVector<QPointF> stroke;
        for (int step = 0; step < w; ++step) {
            const int col = row % 2 ? w - 1 - step : step;
            const auto color = image.pixelColor(col, row);
            const bool ink = color.alpha() >= 128 && qGray(color.rgb()) < 128;
            const double y = height / 2 - (row + 0.5) * dy;
            if (ink && dots) converted.append(QVector<QPointF>{QPointF(-width / 2 + (col + 0.5) * dx, y)});
            else if (ink) {
                const double x0 = -width / 2 + (col + (row % 2 ? 1 : 0)) * dx;
                const double x1 = -width / 2 + (col + (row % 2 ? 0 : 1)) * dx;
                if (stroke.isEmpty()) stroke.append(QPointF(x0, y));
                if (stroke.size() == 1) stroke.append(QPointF(x1, y));
                else stroke.last() = QPointF(x1, y);
            } else if (!stroke.isEmpty()) { converted.append(stroke); stroke.clear(); }
        }
        if (!stroke.isEmpty()) converted.append(stroke);
    }
    if (!validatePaths(converted, error)) return false;
    *paths = converted;
    return true;
}
bool generate(const Paths& paths, const Settings& s, QString* output, QString* error)
{
    if (!output || !validatePaths(paths, error)) return false;
    if (!finite(s.a) || !finite(s.b) || !finite(s.c)) return fail(error, "Plane coordinates must be finite.");
    const QVector3D u = s.b - s.a, v = s.c - s.a;
    const QVector3D n = QVector3D::crossProduct(u, v);
    if (u.length() < 0.001 || v.length() < 0.001 ||
        n.length() < 1e-5 * double(u.length()) * v.length() ||
        std::abs(n.z()) < 1e-4 * n.length())
        return fail(error, "Teach three distinct, non-collinear points on a non-vertical drawing plane.");
    if (!std::isfinite(s.travelZ) || !std::isfinite(s.travelSpeed) || s.travelSpeed <= 0 ||
        !std::isfinite(s.drawingSpeed) || s.drawingSpeed <= 0 ||
        !std::isfinite(s.acceleration) || s.acceleration <= 0)
        return fail(error, "Travel Z must be finite; both speeds and acceleration must be positive.");
    auto zAt = [&](const QPointF& p) {
        return s.a.z() - (double(n.x()) * (p.x() - s.a.x()) + double(n.y()) * (p.y() - s.a.y())) / n.z();
    };
    for (const auto& path : paths) for (const auto& p : path) {
        const double z = zAt(p);
        if (!std::isfinite(z) || std::abs(z) > 100000 || s.travelZ < z + 0.5)
            return fail(error, "Travel Z must be at least 0.5 mm above the entire drawing plane along the paths.");
    }
    QStringList lines{"; Delta X Drawing - millimetres, absolute robot XY, +Y up",
                      "; Home robot and verify tool, plane and workspace limits before running.", "G90"};
    if (s.laser) lines << "; Laser tool must already be configured (M03 S0..255)." << "M03 S0";
    lines << "M204 A" + number(s.acceleration);
    for (const auto& path : paths) {
        lines << "G01 F" + number(s.travelSpeed) << "G01 Z" + number(s.travelZ);
        lines << "G01 X" + number(path.first().x()) + " Y" + number(path.first().y());
        lines << "G01 F" + number(s.drawingSpeed);
        for (int i = 0; i < path.size(); ++i) {
            const auto& p = path[i];
            lines << "G01 X" + number(p.x()) + " Y" + number(p.y()) + " Z" + number(zAt(p));
            if (i == 0 && s.laser) lines << "M03 S255";
        }
        if (s.laser) lines << "M03 S0";
        lines << "G01 F" + number(s.travelSpeed) << "G01 Z" + number(s.travelZ);
    }
    lines << "; End drawing";
    *output = lines.join('\n') + '\n';
    return true;
}
}
