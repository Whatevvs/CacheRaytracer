#include "Timer.h"

// Returns time since initalization of clock
float Timer::TimeSinceStart()
{
    std::atomic_thread_fence(std::memory_order_relaxed);
    std::chrono::duration<float> timeDifference = Clock::now() - m_startTime;
    std::atomic_thread_fence(std::memory_order_relaxed);

    return timeDifference.count();
}

// Returns time between current and last call to TimeSinceLast
float Timer::TimeSinceLast()
{
    float totalTime = TimeSinceStart();
    float timeDifference = totalTime - m_lastTime;
    m_lastTime = totalTime;

    return timeDifference;
}

float Timer::PeekTimeSinceLast()
{
    return TimeSinceStart() - m_lastTime;
}
