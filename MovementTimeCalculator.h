#pragma once

#include <QtCore/QObject>
#include <QtGlobal>

namespace Delta { namespace Motion {

constexpr double kDefaultInterruptCycleMin = 150.0;    // microseconds
constexpr double kMicrosecondsPerSecond = 1'000'000.0;
constexpr double kDefaultTimeToNumInterrupt = kMicrosecondsPerSecond / kDefaultInterruptCycleMin;
constexpr double kDefaultMaxVelocity = 900.0;          // mm/s
constexpr double kDefaultMaxAcceleration = 30000.0;    // mm/s^2

Q_NAMESPACE

enum class SmoothStepOrder : quint8 {
    Linear = 0,   // matches SmoothStep(x) = x
    Cubic = 1,    // SmoothStep(x) = x^2 * (3 - 2x)
    Quintic = 2,
    Septic = 3,
    Nonic = 4
};

Q_ENUM_NS(SmoothStepOrder)

struct MovementConstraints {
    double maxVelocity = kDefaultMaxVelocity;
    double maxAcceleration = kDefaultMaxAcceleration;
    double interruptCycleMin = kDefaultInterruptCycleMin;
    double microsecondsPerSecond = kMicrosecondsPerSecond;
};

struct MovementRequest {
    double startVelocity = 0.0;
    double commandedVelocity = 0.0;
    double endVelocity = 0.0;
    double acceleration = 0.0;
    double distance = 0.0;
    SmoothStepOrder smoothStepOrder = SmoothStepOrder::Cubic;
};

double calculateMovementTime(const MovementRequest &request,
                             const MovementConstraints &constraints = MovementConstraints());

} // namespace Motion
} // namespace Delta
