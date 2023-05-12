#pragma once

#include <chrono>
#include <cstdint>

class Timer {
private:
    std::chrono::time_point<std::chrono::steady_clock> m_start;
    std::chrono::time_point<std::chrono::steady_clock> m_end;

public:
    Timer();
    ~Timer();

    Timer& operator=(const Timer&) = delete;
};
