#include <fstream>
#include <string>
#include <iostream>

#include "GnuPlot.hpp"

void GnuPlot::SendCommand(const std::string& cmd) {
    if (!m_pipe)
        return;

    m_buffer.push_back(cmd);
}

void GnuPlot::PrintBuffer() {
    for (const auto& cmd : m_buffer)
        std::cout << cmd << '\n';
}

void GnuPlot::Execute() {
    if (!m_pipe)
        return;

    for (const auto& cmd : m_buffer)
        fputs((cmd + '\n').c_str(), m_pipe);
}
