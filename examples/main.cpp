#include <hpdf_types.h>
#include <memory>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

#include "LSystemInterpreter/Data.hpp"
#include "LSystemInterpreter/Options.hpp"
#include "Utils/Timer.hpp"
#include "LSystemCreator/LSystem.hpp"
#include "LSystemInterpreter/Interpreter.hpp"

#include <LibHaruFacade/Colors.hpp>
#include <LibHaruFacade/HpdfApi.hpp>

using namespace LSystemInterpreter;

int main(int argv, char* argc[]) {
    Timer t;

    /*
    std::unordered_set<char> constants = {'+', '-', '[', ']'};
    std::string axiom = "X";
    std::unordered_map<char, std::string> rules = {
        {'X', "F-[[X]+X]+F[+FX]-X"},
        {'F', "FF"},
    };

    Grammar g(constants, axiom, rules);
    LSystem l(g);
    */

    Hpdf test("out.pdf");
    test.AddPage(100, 100);

    Painter p(test(0));

    std::string lsys("F+F--F+F+F+F--F+F--F+F--F+F+F+F--F+F+F+F--F+F+F+F--F+F--F+F--F+F+F+F--F+F--F+F--F+F+F+F--F+F--F+F--F+F+F+F--F+F+F+F--F+F+F+F--F+F--F+F--F+F+F+F--F+F");
    
    Data::Structure s;
    Options::StructureBuilder builderOpt;
    builderOpt.initAngle_deg = 0;
    builderOpt.stepAngle_deg = 60;
    builderOpt.vectorNorm_px = 3;

    Interpreter::StructureBuilder builder(builderOpt);
    Interpreter::Interpreter interpreter(std::make_shared<std::string>(lsys));
    interpreter.Execute(builder);
    s = builder.GetStructure();

    float min_x = s.structure[0].line[0].x;
    float min_y = s.structure[0].line[0].y;
    float max_x = s.structure[0].line[0].x;
    float max_y = s.structure[0].line[0].y;

    for (const auto& i : s.structure) {
        for (const auto& j : i.line) {
            min_x = std::min(min_x, j.x);
            max_x = std::max(max_x, j.x);
            min_y = std::min(min_y, j.y);
            max_y = std::max(max_y, j.y);
        }
    }

    std::cout << "MAX: {" << max_x << ", " << max_y << "}\n";
    std::cout << "MIN: {" << min_x << ", " << min_y << "}\n";
    std::cout << "CENTER: {" << (max_x - min_x) / 2 << ", " << (max_y - min_y) / 2 << "}\n";

    p.Line(s.structure, 2, Colors::PastelPurple, HPDF_ROUND_END, HPDF_ROUND_JOIN);
    //p.Line({0, 0}, {100, 100}, 1, Colors::Blue);
    //p.Line({0, 100}, {100, 0}, 1, Colors::Blue);

    int num1= 0;
    for (const auto& i : s.structure) {
        std::cout << "[ Line " << num1++ << " ]\n";
        for (const auto& j : i.line) {
            std::cout << "{" << j.x << ", " << j.y << "},\n";
        }   
    }

    return 0;
}

