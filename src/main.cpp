#include <iostream>
#include <memory>
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
    lSys.SetNumberOfIterations(5);
    lSys.Iterate();

    LSystemPlot lSysPlot(90, 0.5, 19);

    lSysPlot.LoadModel(lSys.Get());

    auto lW = std::make_shared<LineWidth>();
    lW->SetLineGradient(2);
    lW->SetDeform(LineWidth::Deform::Constant);

    lSysPlot.LoadLineModifier(lW);
    lSysPlot.SetPosition(0, -20);
    lSysPlot.SetLineWidth(2);

    lSysPlot.Plot();

    return 0;
}
