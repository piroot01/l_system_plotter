#include <iostream>
#include <unordered_map>
#include <vector>
#include <unordered_set>

#include "LinePlot.hpp"
#include "LSystem.hpp"

int main() {
/*
    LinePlot lp;

    lp.SetOutputName("test");

    Line l1({0, 0}, {1, 0});
    Line l2({1, 0}, {1, 1});

    lp.PlotLine(l1);
    lp.PlotLine(l2);
    lp.PrintBuffer();
    lp.Execute();
*/
    std::vector<char> alphabet = {'F', 'G', '+', '-'};
    std::unordered_set<char> constants = {'+', '-'};
    std::string axiom = "F";
    std::unordered_map<char, std::string> rules = {
        {'F', "F+G"},
        {'G', "F-G"},
    };

    LSystem lSys(alphabet, constants, axiom, rules);

    lSys.SetNumberOfIterations(5);
    lSys.Iterate();

    std::cout << *lSys.Get() << '\n';

    //lSys.Print();


    return 0;
}
