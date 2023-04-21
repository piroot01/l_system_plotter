#include <iostream>

#include "LinePlot.hpp"

int main() {
    LinePlot lp;

    lp.SetOutputName("test");

    Line l1({0, 0}, {1, 0});
    Line l2({1, 0}, {1, 1});

    lp.PlotLine(l1);
    lp.PlotLine(l2);
    lp.PrintBuffer();
    lp.Execute();

    return 0;
}
