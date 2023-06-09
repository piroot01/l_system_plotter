#include "LSystem.hpp"
#include <cstdint>
#include <string>
#include <unordered_map>
#include <iostream>
#include <unordered_set>
#include <memory>

LSystem::LSystem(const std::unordered_set<char>& constances, const std::string& axiom, const std::unordered_map<char, std::string>& rules)
    : m_constances(constances), m_axiom(axiom), m_rules(rules) {
    SetNumberOfIterations(m_defaultIterCount);
}

void LSystem::SetNumberOfIterations(uint16_t iterCount) {
    this->m_iterCount = iterCount;
}

void LSystem::Iterate(void) {
    m_derivation = m_axiom;

    for (uint16_t i = 0; i < m_iterCount; i++) {
        std::string next_derivation;
        for (const auto& j : m_derivation) {
            if (m_constances.find(j) == m_constances.end()) 
                next_derivation += m_rules[j];
            else
                next_derivation += j;
        }
        m_derivation = std::move(next_derivation);
    }
}

void LSystem::Print(void) {
    std::cout << m_derivation << '\n';
}

std::shared_ptr<std::string> LSystem::Get(void) {
    return std::make_shared<std::string>(m_derivation);
}
