#include <chrono>
#include <iostream>

#include "Timer.hpp"

Timer::Timer() {
    m_start = std::chrono::steady_clock::now();
}

Timer::~Timer() {
    m_end = std::chrono::steady_clock::now();
    std::cout << "Timer: " << std::chrono::duration_cast<std::chrono::microseconds>(m_end - m_start) << "\n";
}
