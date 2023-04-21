#pragma once

#define LINE_PLOT_H_
#ifdef LINE_PLOT_H_

#include <string>

#include "GnuPlot.hpp"

class LinePlot : public GnuPlot {
public:
    LinePlot();
    virtual ~LinePlot();

    void SetOutputName(const std::string& outName);

    void DummyPlot();
private:
    const std::string outputName = "graph";

};

#endif
