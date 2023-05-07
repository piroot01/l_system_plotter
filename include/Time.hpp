#pragma once

#include <chrono>
#include <string>

class CurrentTime {
private:
    std::string m_timeFormat;

public:
    CurrentTime(const std::string& format = "%d-%m-%Y %H:%M:%S") : m_timeFormat(format) {}
    ~CurrentTime() = default;

    void SetFormat(const std::string& format);
    std::string GetCurrentTime() const;

    CurrentTime(const CurrentTime&) = delete;
    CurrentTime(CurrentTime&&) = delete;
    CurrentTime& operator=(const CurrentTime&) = delete;
    CurrentTime& operator=(CurrentTime&&) = delete;
};
