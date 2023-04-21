#include <iostream>
#include <unordered_map>
#include <vector>
#include <unordered_set>

#include "LinePlot.hpp"
#include "LSystem.hpp"
#include "LSystemPlot.hpp"

int main() {
    std::vector<char> alphabet = {'M', 'S', '+', '-', '[', ']'};
    std::unordered_set<char> constants = {'+', '-', '[', ']'};
    std::string axiom = "M";
    std::unordered_map<char, std::string> rules = {
        {'M', "S[+M][-M]SM"},
        {'S', "SS"},
    };

    LSystem lSys(alphabet, constants, axiom, rules);

    lSys.SetNumberOfIterations(7);
    lSys.Iterate();

    lSys.Print();
    LSystemPlot lSysPlot(0, 0.15, 45);

    lSysPlot.LoadModel(lSys.Get());

    lSysPlot.Plot();

    return 0;
}
