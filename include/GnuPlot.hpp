#pragma once

#define GNU_PLOT_H_
#ifdef GNU_PLOT_H_

#include <fstream>
#include <string>
#include <vector>

class GnuPlot {
public:
    inline GnuPlot(bool persist = true) {
        pipe = popen(persist ? "gnuplot -persist" : "gnuplot", "w");
    }

    inline virtual ~GnuPlot() {
        if (pipe)
            pclose(pipe);
    }

    void SendCommand(const std::string& cmd);
    virtual void Execute();
    void PrintBuffer();

protected:
    GnuPlot(const GnuPlot&) = delete;
    void operator=(const GnuPlot&) = delete;

    FILE* pipe;
    std::vector<std::string> buffer;

};

#endif
