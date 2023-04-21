#pragma once

#define L_SYSTEM_H_
#ifdef L_SYSTEM_H_

#include <vector>
#include <string>

class LSystem {
public:
    LSystem(const std::vector<char>& alphabet, const std::string axiom, const std::vector<std::string>& rules);

private:
    std::vector<char> m_alphabet;
    std::string m_axiom;
    std::vector<std::string>& rules;

};

#endif
