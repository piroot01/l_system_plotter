#include "GnuPlot.hpp"
#include "LinePlot.hpp"

LinePlot::LinePlot() : GnuPlot(true) {
    SendCommand("set terminal pdfcairo font 'Times, 12' size 20cm, 20cm");
    SendCommand("unset xlabel");
    SendCommand("unset ylabel");
    SendCommand("unset xtics");
    SendCommand("unset ytics");
    SendCommand("unset key");

    SetOutputName(outputName);
}

void LinePlot::SetOutputName(const std::string& outName) {
    SendCommand("set output '" + outName + ".pdf'");
}

LinePlot::~LinePlot() {}

void LinePlot::DummyPlot() {
    SendCommand("plot '-' with lines lc rgb 'black'");
    SendCommand("0 0");
    SendCommand("1 1");
    SendCommand("e");
}
