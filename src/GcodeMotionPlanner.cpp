#include "GcodeMotionPlanner.h"
#include <algorithm>
#include <cmath>
#include <limits>

namespace GcodeMotion {
namespace {
QVector3D rounded(QVector3D p)
{
    for (int i = 0; i < 3; ++i) p[i] = std::round(p[i] * 1000.0) / 1000.0;
    return p;
}
bool validPoint(const QVector3D& p)
{
    for (int i = 0; i < 3; ++i)
        if (!std::isfinite(p[i]) || std::abs(p[i]) > 100000) return false;
    return true;
}
bool validLimits(const Limits& l)
{
    return l.speed >= 3 && l.speed <= 20000 && l.acceleration > 0 && l.acceleration <= 50000 &&
        l.jerk > 0 && l.jerk <= 10000000 && std::isfinite(l.minimumLength) &&
        l.minimumLength >= 0.201 && std::isfinite(l.segmentLength) &&
        l.segmentLength >= 2 * l.minimumLength && std::isfinite(l.junctionDeviation) &&
        l.junctionDeviation >= 0 && std::isfinite(l.queuedSeconds) && l.queuedSeconds > 0;
}
int reachable(int from, double distance, const Limits& l)
{
    int lo = from, hi = l.speed - 2;
    while (lo < hi) {
        const int mid = (lo + hi + 1) / 2;
        if (transitionDistance(from, mid, l) <= distance) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}
int junction(const QVector3D& a, const QVector3D& b, const Limits& l)
{
    const double dot = qBound(-1.0, double(QVector3D::dotProduct(a, b)), 1.0);
    if (dot > 0.999999) return l.speed - 2;
    if (dot <= 0) return 0; // Preserve sharp corners/reversals by stopping.
    const double c = std::sqrt((1 + dot) / 2);
    const double radius = l.junctionDeviation * c / (1 - c);
    // Scalar S-curve limits alone do not constrain changes of direction.
    const double speed = std::min(std::sqrt(l.acceleration * radius),
                                  std::cbrt(l.jerk * radius * radius));
    return int(std::min(double(l.speed - 2), std::floor(speed)));
}
Segment segment(QVector3D a, QVector3D b, int entry, int exit, const Limits& l)
{
    return {a, b, l.speed, l.acceleration, l.jerk, entry, exit,
            duration(double((b - a).length()), entry, exit, l)};
}
}

double transitionTime(double from, double to, const Limits& l)
{
    const double dv = std::abs(to - from);
    const double a = l.acceleration, j = l.jerk;
    return dv <= a * a / j ? 2 * std::sqrt(dv / j) : dv / a + a / j;
}
double transitionDistance(double from, double to, const Limits& l)
{
    return (from + to) * 0.5 * transitionTime(from, to, l);
}
double duration(double distance, int entry, int exit, const Limits& l)
{
    double low = std::max(entry, exit), high = l.speed;
    auto rampDistance = [&](double peak) {
        return transitionDistance(entry, peak, l) + transitionDistance(peak, exit, l);
    };
    if (rampDistance(low) > distance + 0.0001) return std::numeric_limits<double>::infinity();
    for (int i = 0; i < 40; ++i) {
        const double mid = (low + high) / 2;
        if (rampDistance(mid) <= distance) low = mid;
        else high = mid;
    }
    return transitionTime(entry, low, l) + transitionTime(low, exit, l) +
        std::max(0.0, distance - rampDistance(low)) / low;
}
QString Segment::gcode() const
{
    return QStringLiteral("G01 X%1 Y%2 Z%3 F%4 A%5 J%6 S%7 E%8")
        .arg(end.x(), 0, 'f', 3).arg(end.y(), 0, 'f', 3).arg(end.z(), 0, 'f', 3)
        .arg(feed).arg(acceleration).arg(jerk).arg(entry).arg(exit);
}
State Segment::endState() const { return {end, (end - start).normalized(), exit}; }

QVector<Segment> plan(const State& start, const QVector<QVector3D>& path,
                      const Limits& l, QString* error)
{
    if (error) error->clear();
    auto fail = [&](const char* message) -> QVector<Segment> {
        if (error) *error = QString::fromLatin1(message);
        return {};
    };
    if (!validLimits(l) || !validPoint(start.position) || start.speed < 0 || start.speed > l.speed - 2 ||
        (start.speed && (!validPoint(start.direction) || start.direction.length() < 0.9f)))
        return fail("Invalid motion limits or initial state.");
    if (path.size() > 4096) return fail("Motion look-ahead exceeds 4096 points.");
    QVector<QVector3D> points{rounded(start.position)};
    // Remove only exactly collinear forward vertices; retain the supplied path.
    for (const auto& p : path) {
        if (!validPoint(p)) return fail("Motion coordinates are not finite or are out of range.");
        const auto next = rounded(p);
        if (next == points.last()) continue;
        while (points.size() >= 2) {
            const auto a = points.last() - points[points.size() - 2], b = next - points.last();
            if (QVector3D::dotProduct(a, b) <= 0) break;
            const auto line = next - points[points.size() - 2];
            const float t = QVector3D::dotProduct(a, line) / line.lengthSquared();
            if ((a - line * t).length() > 0.0005f) break;
            points.removeLast();
        }
        points.append(next);
    }
    QVector<QVector3D> nodes{points.first()};
    for (int i = 1; i < points.size(); ++i) {
        const auto delta = points[i] - points[i - 1];
        const double length = delta.length();
        if (length < l.minimumLength) return fail("Path detail is below the firmware minimum move length.");
        const int count = int(std::ceil(length / l.segmentLength));
        if (nodes.size() + count > 4096) return fail("Motion look-ahead exceeds 4096 segments.");
        for (int n = 1; n <= count; ++n) nodes.append(rounded(points[i - 1] + delta * (float(n) / count)));
    }
    const int count = nodes.size() - 1;
    if (!count) return {};
    QVector<double> distances(count);
    QVector<QVector3D> directions(count);
    QVector<int> speeds(count + 1, 0);
    for (int i = 0; i < count; ++i) {
        const auto delta = nodes[i + 1] - nodes[i];
        distances[i] = delta.length();
        if (distances[i] < 0.2) return fail("Rounded segment is below the firmware minimum move length.");
        directions[i] = delta.normalized();
        if (i) speeds[i] = junction(directions[i - 1], directions[i], l);
    }
    if (start.speed && junction(start.direction.normalized(), directions.first(), l) < start.speed)
        return fail("Committed speed requires braking before changing direction.");
    speeds[0] = start.speed;
    for (int i = count - 1; i >= 0; --i) {
        const int maximum = reachable(speeds[i + 1], distances[i], l);
        if (!i && speeds[0] > maximum) return fail("Committed speed requires more braking distance.");
        speeds[i] = std::min(speeds[i], maximum);
    }
    for (int i = 0; i < count; ++i)
        speeds[i + 1] = std::min(speeds[i + 1], reachable(speeds[i], distances[i], l));
    QVector<Segment> result;
    for (int i = 0; i < count; ++i) {
        const auto move = segment(nodes[i], nodes[i + 1], speeds[i], speeds[i + 1], l);
        if (!std::isfinite(move.seconds) || move.gcode().size() > 79)
            return fail("Motion profile cannot be represented by the controller protocol.");
        result.append(move);
    }
    return result;
}

QVector<Segment> follow(const State& start, QVector3D target, QVector3D velocity,
                       double queuedSeconds, const Limits& limits, QString* error)
{
    if (error) error->clear();
    if (!validLimits(limits) || !validPoint(start.position) || start.speed < 0 || start.speed > 20000 ||
        (start.speed && (!validPoint(start.direction) || start.direction.length() < 0.9f)) || !validPoint(target) ||
        !validPoint(velocity) || !std::isfinite(queuedSeconds) || queuedSeconds < 0) {
        if (error) *error = QStringLiteral("Invalid live target or timing.");
        return {};
    }
    const float inputSpeed = qMin(float(limits.speed), velocity.length());
    const auto offset = target - start.position;
    // Prediction is intent, not measured position. Bound both time and distance;
    // a stale tracker supplies zero velocity and the exact target is restored.
    const double leadSeconds = qMin(0.08, queuedSeconds + 0.06);
    const auto prediction = inputSpeed >= 10
        ? velocity.normalized() * float(qMin(3.0, inputSpeed * leadSeconds)) : QVector3D{};
    if (!validPoint(target + prediction)) {
        if (error) *error = QStringLiteral("Predicted target is out of range.");
        return {};
    }
    const auto delta = target + prediction - start.position;
    if (delta.length() < limits.minimumLength)
        return start.speed ? QVector<Segment>{brake(start, limits)} : QVector<Segment>{};

    Limits live = limits;
    const int servoFeed = int(std::ceil(inputSpeed + offset.length() / 0.12));
    live.speed = qMin(limits.speed, qMax(qMax(3, start.speed + 2), servoFeed));
    // Let an acceleration ramp span several millimetres instead of restarting
    // zero acceleration at every fixed 2 mm boundary. Cruise chunks aim for 60 ms.
    live.segmentLength = qMin(limits.segmentLength,
                             qMax(2 * limits.minimumLength, live.speed * 0.06));
    if (inputSpeed > 1)
        live.segmentLength = qMin(live.segmentLength, qMax(2 * limits.minimumLength, delta.length() * 0.5));
    const auto destination = start.position + delta.normalized() * qMin(20.0f, delta.length());
    auto result = plan(start, {destination}, live, error);
    if (start.speed && result.isEmpty()) {
        // Splitting a feasible final ramp can make it infeasible because each
        // sub-ramp must end at zero acceleration. Keep this last deceleration
        // intact rather than braking just short and losing a sub-minimum residue.
        const auto end = rounded(destination);
        const auto displacement = end - rounded(start.position);
        const double stoppingDistance = transitionDistance(start.speed, 0, live);
        if (live.speed >= start.speed + 2 && displacement.length() <= stoppingDistance + 2 * limits.minimumLength &&
            junction(start.direction.normalized(), displacement.normalized(), live) >= start.speed) {
            const auto finalRamp = segment(rounded(start.position), end, start.speed, 0, live);
            if (std::isfinite(finalRamp.seconds)) {
                if (error) error->clear();
                return {finalRamp};
            }
        }
        if (error) error->clear();
        return {brake(start, limits)};
    }
    return result;
}

Segment brake(const State& start, const Limits& limits)
{
    Limits l = limits;
    l.speed = std::max(3, start.speed + 2);
    const double distance = std::max(l.minimumLength, transitionDistance(start.speed, 0, l) + 0.002);
    return segment(start.position, rounded(start.position + start.direction.normalized() * float(distance)),
                   start.speed, 0, l);
}
}
