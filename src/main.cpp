#include <string>
#include <vector>
#include <iostream>

#include "Colors.hpp"
#include "Timer.hpp"
#include "HpdfApi.hpp"
#include "Time.hpp"
#include "LSystem.hpp"
#include "ConfigReader.hpp"
#include "LSystemInterpreter.hpp"

int main(int argv, char* argc[]) {
    Timer t;
    
    ConfigReader config("l_system_interpreter.json");
    config.ReadConfig();

    std::unordered_set<char> constants = {'+', '-', '[', ']'};
    std::string axiom = "X";
    std::unordered_map<char, std::string> rules = {
        {'X', "F-[[X]+X]+F[+FX]-X"},
        {'F', "FF"},
    };

    Grammar g(constants, axiom, rules);
    LSystem l(g);

    LSystemInterpreter interpreter(l.Iterate(3), config);
    interpreter.PrintConfig();

/*
    CurrentTime cr;
    cr.SetFormat("%H:%M:%S");
    Hpdf test("test.pdf");
    test.AddPage();

    Painter p(test.GetPage(0));
    p.Line({10, 10}, {245, 245}, 2, Colors::Blue, HPDF_ROUND_END);
    p.PageLabel(std::string(argc[0]) + " - " + cr.GetCurrentTime(), test.GetFont("Courier"), 5, Colors::Red);
*/
}
