#pragma once

#include <cstdint>
#define LINE_PLOT_H_
#ifdef LINE_PLOT_H_

#include <string>

#include "GnuPlot.hpp"
#include "Colors.hpp"

struct Point {
    double x, y;
    Point operator+(const Point& point);
    Point& operator+=(const Point& point);
};

struct Line {
    Line(const Point& start, const Point& end, const double width = 1, const std::string& color = Colors::Black);

    Point start, end;
    double width;
    std::string color;

};

class LinePlot : public GnuPlot {
public:
    LinePlot(void);
    virtual ~LinePlot(void);

    void SetPlotRange(const double xrange, const double yrange);
    void SetOutputName(const std::string& outName);

    void PlotLine(const Line& line);

    void Execute(void) override;

protected:
    const std::string m_outputName = "out";
    const double m_xrange = 20;
    const double m_yrange = 20;

};

#endif
