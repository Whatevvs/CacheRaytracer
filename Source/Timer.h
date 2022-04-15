#pragma once
#include <chrono>
#include <atomic>

// Adapted from Incomputable's reply
// https://codereview.stackexchange.com/questions/196245/extremely-simple-timer-class-in-c

class Timer
{
    typedef std::chrono::high_resolution_clock Clock;

    const Clock::time_point m_startTime;
    float m_lastTime { 0.0f };

public:
    Timer() : m_startTime(Clock::now()), m_lastTime(TimeSinceLast()) {}

    float TimeSinceStart();
    float TimeSinceLast();
};