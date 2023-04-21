#include <iostream>

#include "LinePlot.hpp"

int main() {
    LinePlot lp;

    lp.SetOutputName("test");
    lp.DummyPlot();
    lp.PrintBuffer();
    lp.Execute();

    return 0;
}
