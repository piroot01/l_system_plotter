#pragma once

#include <cstdint>
#define LINE_PLOT_H_
#ifdef LINE_PLOT_H_

#include <string>

#include "GnuPlot.hpp"

struct Point {
    double x, y;

};

struct Line {
    Line(const Point& start, const Point& end, double width = 1, std::string color = "black");

    Point start, end;
    double width;
    std::string color;

};

class LinePlot : public GnuPlot {
public:
    LinePlot();
    virtual ~LinePlot();

    void SetPlotRange(const double xrange, const double yrange);
    void SetOutputName(const std::string& outName);

    void PlotLine(const Line& line);

    void Execute() override;

private:
    const std::string outputName = "out";
    const double xrange = 10;
    const double yrange = 10;

};

#endif
