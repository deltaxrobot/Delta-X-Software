#include "MovementTimeCalculator.h"

#include <algorithm>
#include <cmath>
#include <cstdint>

#include <QtCore/QtGlobal>

namespace Delta { namespace Motion {
namespace {

template <typename T>
inline T clampValue(T value, T minValue, T maxValue)
{
    if (value < minValue) {
        return minValue;
    }
    if (value > maxValue) {
        return maxValue;
    }
    return value;
}

inline double clamp01(double value)
{
    return clampValue(value, 0.0, 1.0);
}

double smoothStep(double x, SmoothStepOrder order)
{
    const double clamped = clamp01(x);
    switch (order) {
    case SmoothStepOrder::Linear:
        return clamped;
    case SmoothStepOrder::Quintic: {
        const double x2 = clamped * clamped;
        const double x3 = x2 * clamped;
        return x3 * (10.0 + clamped * (6.0 * clamped - 15.0));
    }
    case SmoothStepOrder::Septic: {
        const double x2 = clamped * clamped;
        const double x4 = x2 * x2;
        return x4 * (35.0 + clamped * (clamped * (70.0 - 20.0 * clamped) - 84.0));
    }
    case SmoothStepOrder::Nonic: {
        const double x2 = clamped * clamped;
        const double x4 = x2 * x2;
        const double x5 = x4 * clamped;
        return x5 * (126.0 + clamped * (clamped * (540.0 + clamped * (70.0 * clamped - 315.0)) - 420.0));
    }
    case SmoothStepOrder::Cubic:
    default: {
        const double x2 = clamped * clamped;
        return x2 * (3.0 - 2.0 * clamped);
    }
    }
}

double clampPositive(double value, double fallback)
{
    return value > 0.0 ? value : fallback;
}

} // namespace

double calculateMovementTime(const MovementRequest &request,
                             const MovementConstraints &constraints)
{
    Q_UNUSED(request.endVelocity);

    if (request.distance <= 0.0) {
        return 0.0;
    }

    const double maxVelocityLimit = clampPositive(constraints.maxVelocity, kDefaultMaxVelocity);
    double velocity = clampValue(request.commandedVelocity, 0.0, maxVelocityLimit);
    if (velocity <= 0.0) {
        return 0.0;
    }

    const double interruptCycleMin = clampPositive(constraints.interruptCycleMin, kDefaultInterruptCycleMin);
    const double microsecondsPerSecond = clampPositive(constraints.microsecondsPerSecond, kMicrosecondsPerSecond);
    const double timeToNumInterrupt = microsecondsPerSecond / interruptCycleMin;

    const double maxAccelerationLimit = clampPositive(constraints.maxAcceleration, kDefaultMaxAcceleration);
    double acceleration = clampValue(request.acceleration, 0.0, maxAccelerationLimit);
    if (acceleration < 1e-6) {
        acceleration = 1e-6;
    }

    double beginEndVelocity = request.startVelocity;
    if (beginEndVelocity < 0.0) {
        beginEndVelocity = 0.0;
    }
    if (beginEndVelocity > velocity) {
        beginEndVelocity = velocity;
    }
    if (beginEndVelocity < 1e-6) {
        beginEndVelocity = 1e-6;
    }

    double beginEndIntCycle = velocity * interruptCycleMin / beginEndVelocity;
    if (beginEndIntCycle < interruptCycleMin) {
        beginEndIntCycle = interruptCycleMin;
    }

    double timeUsForChangeVelocity = 0.0;
    double fIncrease = 0.0;
    if (beginEndIntCycle > interruptCycleMin && velocity > beginEndVelocity) {
        timeUsForChangeVelocity = (velocity - beginEndVelocity) / acceleration * microsecondsPerSecond;
        if (timeUsForChangeVelocity < 0.0) {
            timeUsForChangeVelocity = 0.0;
        }
        fIncrease = beginEndIntCycle - interruptCycleMin;
    }

    const double timeMove = request.distance / velocity;
    std::int64_t totalInterrupts = static_cast<std::int64_t>(std::llround(timeMove * timeToNumInterrupt));
    if (totalInterrupts <= 0) {
        totalInterrupts = 1;
    }

    const std::int64_t accelUntil = totalInterrupts / 2;

    double currentCycle = beginEndIntCycle;
    double timeCounter = 0.0;
    double totalTimeUs = 0.0;
    std::int64_t interruptCounterWhenAccel = 0;

    for (std::int64_t totalCounter = 1; totalCounter <= totalInterrupts; ++totalCounter) {
        const double elapsed = currentCycle;
        totalTimeUs += elapsed;

        if (timeUsForChangeVelocity > 0.0 && fIncrease > 0.0) {
            if (totalCounter <= accelUntil && currentCycle > interruptCycleMin) {
                timeCounter += elapsed;
                if (timeCounter > timeUsForChangeVelocity) {
                    timeCounter = timeUsForChangeVelocity;
                }
                const double ratio = clamp01(timeUsForChangeVelocity > 0.0
                                                  ? timeCounter / timeUsForChangeVelocity
                                                  : 0.0);
                currentCycle = beginEndIntCycle - smoothStep(ratio, request.smoothStepOrder) * fIncrease;
                if (currentCycle < interruptCycleMin) {
                    currentCycle = interruptCycleMin;
                }
                interruptCounterWhenAccel = totalCounter;
            } else if (interruptCounterWhenAccel > 0 &&
                       totalCounter >= (totalInterrupts - interruptCounterWhenAccel - 2) &&
                       currentCycle < beginEndIntCycle) {
                timeCounter -= elapsed;
                if (timeCounter < 0.0) {
                    timeCounter = 0.0;
                }
                const double ratio = clamp01(timeUsForChangeVelocity > 0.0
                                                  ? timeCounter / timeUsForChangeVelocity
                                                  : 0.0);
                currentCycle = beginEndIntCycle - smoothStep(ratio, request.smoothStepOrder) * fIncrease;
                if (currentCycle > beginEndIntCycle) {
                    currentCycle = beginEndIntCycle;
                }
            }
        }
    }

    return totalTimeUs / microsecondsPerSecond;
}

} // namespace Motion
} // namespace Delta
