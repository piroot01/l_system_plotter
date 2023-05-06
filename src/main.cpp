#include <string>
#include <vector>
#include <iostream>

#include "Colors.hpp"
#include "Timer.hpp"
#include "HpdfApi.hpp"
#include "Time.hpp"
#include "LSystem.hpp"
#include "ConfigReader.hpp"

int main(int argv, char* argc[]) {
    Timer t;
    ConfigReader::Instance().SetConfigFilename("config");
    ConfigReader::Instance().ReadConfig();

    std::cout << ConfigReader::Instance().GetValue("line") << '\n';

    /*
    std::unordered_set<char> constants = {'+', '-', '[', ']'};
    std::string axiom = "X";
    std::unordered_map<char, std::string> rules = {
        {'X', "F-[[X]+X]+F[+FX]-X"},
        {'F', "FF"},
    };

    Grammar g(constants, axiom, rules);
    LSystem l(g);

    std::string output = *l.Iterate(6);
    std::cout << output << '\n';
*/
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
