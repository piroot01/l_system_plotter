#include <cstdint>
#include <string>
#include <unordered_map>
#include <iostream>
#include <unordered_set>
#include <memory>
#include <optional>

#include "LSystem.hpp"
#include "Timer.hpp"

Grammar& Grammar::operator=(const Grammar& other) {
    if (this != &other) {
        m_constances = other.m_constances;
        m_axiom = other.m_axiom;
        m_rules = other.m_rules;
    }

    return *this;
}

Grammar& Grammar::operator=(Grammar&& other) noexcept {
    if (this != &other) {
        m_constances = std::move(other.m_constances);
        m_axiom = std::move(other.m_axiom);
        m_rules = std::move(other.m_rules);
    }

    return *this;
}

const std::unordered_set<char>& Grammar::GetConstances() const {
    return m_constances;
}

const std::string& Grammar::GetAxiom() const {
    return m_axiom;
}

const std::unordered_map<char, std::string>& Grammar::GetRules() const {
    return m_rules;
}

void LSystem::SetNumberOfIterations(const uint16_t iterCount) {
    this->m_iterCount = iterCount;
}

std::shared_ptr<const std::string> LSystem::Iterate(const uint16_t iterCount) {
    Timer t;
    auto currentState = std::make_shared<std::string>(m_grammar.GetAxiom());

    const auto& constances = m_grammar.GetConstances();
    const auto& rules = m_grammar.GetRules();

    for (uint16_t i = 0; i < iterCount; i++) {
        std::string nextGeneration;
        nextGeneration.reserve(currentState->size() * 2);

        for (const auto& j : *currentState) {
            std::string_view ruleOrConst;

            if (constances.find(j) == constances.end()) 
                ruleOrConst = rules.at(j);
            else
                ruleOrConst = std::string_view(&j, 1);

            nextGeneration.append(ruleOrConst);
        }

        currentState->swap(nextGeneration);
        nextGeneration.clear();
    }

    return currentState;
}

