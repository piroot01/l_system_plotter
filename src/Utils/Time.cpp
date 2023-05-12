#include <string>
#include <iomanip>

#include "Utils/Time.hpp"

void CurrentTime::SetFormat(const std::string& format) {
    m_timeFormat = format;
}

std::string CurrentTime::GetCurrentTime() const {
    auto currTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto tm = *std::localtime(&currTime);
    std::stringstream timeStream;
    timeStream << std::put_time(&tm, m_timeFormat.c_str());
    return timeStream.str();
}
