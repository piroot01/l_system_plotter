#include "Timer.hpp"
#include "LSystem.hpp"

#include "LSystemInterpreter/Interpreter.hpp"

using namespace LSystemInterpreter;

int main(int argv, char* argc[]) {
    Timer t;

    std::unordered_set<char> constants = {'+', '-', '[', ']'};
    std::string axiom = "X";
    std::unordered_map<char, std::string> rules = {
        {'X', "F-[[X]+X]+F[+FX]-X"},
        {'F', "FF"},
    };

    Grammar g(constants, axiom, rules);
    LSystem l(g);

    Interpreter::Interpreter interpreter(l.Iterate(3));

}
