#include <string>

#include "GnuPlot.hpp"
#include "LinePlot.hpp"

Point Point::operator+(const Point& point) {
    Point p;
    p.x = this->x + point.x;
    p.y = this->y + point.y;
    return p;
}

Point& Point::operator+=(const Point& point) {
    this->x += point.x;
    this->y += point.y;
    return *this;
}

Line::Line(const Point& start, const Point& end, double width, std::string color)
    : start(start), end(end), width(width), color(color) {}

LinePlot::LinePlot(void) : GnuPlot(true) {
    SendCommand("set terminal pdfcairo font 'Times, 12' size 20cm, 20cm");
    SendCommand("unset xlabel");
    SendCommand("unset ylabel");
    SendCommand("unset xtics");
    SendCommand("unset ytics");
    SendCommand("unset key");

    SetOutputName(this->m_outputName);
    SetPlotRange(this->m_xrange, this->m_yrange);
}

void LinePlot::SetPlotRange(const double xrange, const double yrange) {
    SendCommand("set xrange [-20:" + std::to_string(xrange) + "]");
    SendCommand("set yrange [-20:" + std::to_string(yrange) + "]");
}

void LinePlot::SetOutputName(const std::string& outName) {
    SendCommand("set output '" + outName + ".pdf'");
}

LinePlot::~LinePlot(void) {}

void LinePlot::Execute(void) {
    SendCommand("plot NaN");
    GnuPlot::Execute();
}

void LinePlot::PlotLine(const Line& line) {
    SendCommand("set arrow from " +
        std::to_string(line.start.x) + ',' + std::to_string(line.start.y) +
        " to " +
        std::to_string(line.end.x) + ',' + std::to_string(line.end.y) +
        " nohead lc '" + line.color + "' lw '" + std::to_string(line.width));
}
