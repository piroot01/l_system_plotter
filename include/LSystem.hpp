#pragma once

#define L_SYSTEM_H_
#ifdef L_SYSTEM_H_

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <memory>

class LSystem {
public:
    LSystem(const std::unordered_set<char>& m_constances, const std::string& axiom, const std::unordered_map<char, std::string>& rules);

    void SetNumberOfIterations(uint16_t iterCount);
    void Iterate(void);
    void Print(void);
    std::shared_ptr<std::string> Get(void);

private:
    std::unordered_set<char> m_constances;
    std::string m_axiom;
    std::unordered_map<char, std::string> m_rules;

    uint16_t m_iterCount;

    const uint16_t m_defaultIterCount = 1;

    std::string m_derivation;
};

#endif
