#pragma once

#include <iostream>
#include <stdexcept>
#include <source_location>

namespace LSystemInterpreter {

class Exception : public std::runtime_error {
public:
    Exception(const std::string& arg, const std::source_location& location = std::source_location::current());
    ~Exception() noexcept;

    [[nodiscard]] const char* what() const noexcept override;

private:
    std::string m_message;
    std::source_location m_location;

};

}
