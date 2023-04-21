#include <fstream>
#include <string>
#include <iostream>

#include "GnuPlot.hpp"

void GnuPlot::SendCommand(const std::string& cmd) {
    if (!pipe)
        return;

    buffer.push_back(cmd);
}

void GnuPlot::PrintBuffer() {
    for (const auto& cmd : buffer)
        std::cout << cmd << '\n';
}

void GnuPlot::Execute() {
    if (!pipe)
        return;

    for (const auto& cmd : buffer)
        fputs((cmd + '\n').c_str(), pipe);
}
