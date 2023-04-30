#pragma once

#define TIME_H_
#ifdef TIME_H_

#include <chrono>
#include <string>

class CurrentTime {
private:
    std::string m_timeFormat;

public:
    CurrentTime(const std::string& format = "%d-%m-%Y %H:%M:%S") : m_timeFormat(format) {}

    void SetFormat(const std::string& format);
    std::string GetCurrentTime() const;

    CurrentTime& operator=(const CurrentTime&) = delete;
};

#endif
