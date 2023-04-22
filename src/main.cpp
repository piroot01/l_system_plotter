#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>
#include <unordered_set>

#include "Colors.hpp"
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

    auto lW = std::make_shared<LineWidth>();
    lW->SetLineGradient(2);
    lW->SetDeform(LineWidth::Deform::Constant);

    auto lC = std::make_shared<LineColor>();
    lC->SetBaseColor(Colors::Brown);

    lSysPlot.LoadLineModifier(lW);
    lSysPlot.LoadLineModifier(lC);
    lSysPlot.SetPosition(0, -20);
    lSysPlot.SetLineWidth(1);

    lSysPlot.Plot();

    return 0;
}
