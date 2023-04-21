#pragma once

#define GNU_PLOT_H_
#ifdef GNU_PLOT_H_

#include <fstream>
#include <string>
#include <vector>

class GnuPlot {
public:
    inline GnuPlot(bool persist = true) {
        m_pipe = popen(persist ? "gnuplot -persist" : "gnuplot", "w");
    }

    inline virtual ~GnuPlot() {
        if (m_pipe)
            pclose(m_pipe);
    }

    void SendCommand(const std::string& cmd);
    virtual void Execute();
    void PrintBuffer();

protected:
    GnuPlot(const GnuPlot&) = delete;
    void operator=(const GnuPlot&) = delete;

    FILE* m_pipe;
    std::vector<std::string> m_buffer;

};

#endif
