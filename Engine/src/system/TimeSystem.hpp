#ifndef DTENGINE_TIMESYSTEM_H
#define DTENGINE_TIMESYSTEM_H

#include "system/InternalSystem.hpp"

namespace DTEngine
{

class TimeSystem : public InternalSystem
{
friend class SystemRegistry;

public:
    ~TimeSystem();
    TimeSystem();

public:
    float GetDeltaTime() const;

    void SetFixedTimeStep(double value);
    double GetFixedTimeStep() const;

    void UpdateTimeVariables();

    // Advances the accumulator by deltaTime and returns how many fixed steps are
    // owed this frame, already consumed. Clamped against the spiral of death
    int ConsumeFixedSteps();

    // [0-1], where the render frame sits between the last two physics states.
    // Works properly only after ConsumeFixedSteps() has run for this frame
    float GetInterpolationAlpha() const;

protected:
    bool Init() override;

private:
    double lastTime;
    double deltaTime;

    double fixedTimeStep = 1.0 / 50.0;

    // Unsimulated time carried between frames
    double fixedAccumulator = 0.0;

};

}

#endif