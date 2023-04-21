#include <iostream>
#include <unordered_map>
#include <vector>
#include <unordered_set>

#include "LinePlot.hpp"
#include "LSystem.hpp"
#include "LSystemPlot.hpp"

int main() {
    std::unordered_set<char> constants = {'+', '-', '[', ']'};
    std::string axiom = "X";
    std::unordered_map<char, std::string> rules = {
        {'X', "F-[[X]+X]+F[+FX]-X"},
        {'F', "FF"},
    };

    LSystem lSys(constants, axiom, rules);
    lSys.SetNumberOfIterations(6);
    lSys.Iterate();

    LSystemPlot lSysPlot(90, 0.2, 22.5);

    lSysPlot.LoadModel(lSys.Get());

    lSysPlot.SetPosition(0, -20);
    lSysPlot.UseGrad();
    lSysPlot.SetLineWidth(10);
    lSysPlot.SetLineGradient(300);

    lSysPlot.Plot();

    return 0;
}
