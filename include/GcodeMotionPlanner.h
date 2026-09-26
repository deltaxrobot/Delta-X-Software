#pragma once
#include <QString>
#include <QVector>
#include <QVector3D>

namespace GcodeMotion {
struct Limits {
    int speed = 100;
    int acceleration = 1500;
    int jerk = 15000;
    double segmentLength = 2.0;
    double minimumLength = 0.201;
    double junctionDeviation = 0.05;
    double queuedSeconds = 0.25;
};
struct State {
    QVector3D position;
    QVector3D direction;
    int speed = 0;
};
struct Segment {
    QVector3D start, end;
    int feed = 0, acceleration = 0, jerk = 0, entry = 0, exit = 0;
    double seconds = 0;
    QString gcode() const;
    State endState() const;
};
// Units: mm, seconds. E is exit speed, never extrusion. No device I/O here.
double transitionTime(double from, double to, const Limits& limits);
double transitionDistance(double from, double to, const Limits& limits);
double duration(double distance, int entry, int exit, const Limits& limits);
QVector<Segment> plan(const State& start, const QVector<QVector3D>& path,
                      const Limits& limits, QString* error = nullptr);
// Live cursor following: bounded prediction and time-based, speed-adaptive chunks.
// The terminal stop remains in the uncommitted plan, not at every input sample.
QVector<Segment> follow(const State& start, QVector3D target, QVector3D velocity,
                       double queuedSeconds, const Limits& limits, QString* error = nullptr);
Segment brake(const State& start, const Limits& limits);
}
