#include "system/TimeSystem.hpp"

#include <DTEngine/Window.hpp>

#include "GLFW/glfw3.h"

#include <cmath>

using namespace DTEngine;

// To prevent the accumulation of work, let the simulation run slow
constexpr int MAX_CATCHUP_STEPS = 5;

TimeSystem::~TimeSystem()
{
    //
}

TimeSystem::TimeSystem() :
    lastTime(0.0),
    deltaTime(0.0)
{
    //
}

bool TimeSystem::Init()
{
    if (Window::GetInstance() == nullptr) return false;
    return true;
}

float TimeSystem::GetDeltaTime() const
{
    return (float)deltaTime;
}

void TimeSystem::SetFixedTimeStep(double value)
{
    fixedTimeStep = value;
}

double TimeSystem::GetFixedTimeStep() const
{
    return fixedTimeStep;
}

void TimeSystem::UpdateTimeVariables()
{
    double newTime = glfwGetTime();

    // Avoids the first deltaTime being negative
    if (lastTime == 0.0) {
        lastTime = newTime;
        return;
    }

    deltaTime = newTime - lastTime;
    lastTime = newTime;
}

int TimeSystem::ConsumeFixedSteps()
{
    fixedAccumulator += deltaTime;

    int steps = static_cast<int>(fixedAccumulator / fixedTimeStep);

    if (steps > MAX_CATCHUP_STEPS) {
        // Clamping the step count alone is not enough, the debt would 
        // just carry into the next frame and spiral anyway
        fixedAccumulator = std::fmod(fixedAccumulator, fixedTimeStep);
        steps = MAX_CATCHUP_STEPS;
    }
    else {
        fixedAccumulator -= steps * fixedTimeStep;
    }

    return steps;
}

float TimeSystem::GetInterpolationAlpha() const
{
    return (float)(fixedAccumulator / fixedTimeStep);
}