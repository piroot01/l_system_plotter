#include <stdexcept>
#include <string>

#include "LSystemInterpreter/Exception.hpp"

namespace LSystemInterpreter {

Exception::Exception(const std::string& arg, const std::source_location& location)
    : std::runtime_error(arg), m_location(location) {
    m_message = "\33[1m" + std::string(location.file_name()) + ":" + std::to_string(location.line()) + ": \33[31merror:\33[0m " + arg;
}

Exception::~Exception() noexcept = default;

[[nodiscard]] const char* Exception::what() const noexcept {
    return m_message.c_str();
}

} // namespace LSystemInterpreter

