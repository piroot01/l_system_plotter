#include <cstdint>
#include <string>
#include <unordered_map>
#include <iostream>
#include <unordered_set>
#include <memory>
#include <vector>

#include "LSystem.hpp"
#include "Timer.hpp"

Grammar::Grammar(const std::unordered_set<char>& constances, const std::string& axiom, const std::unordered_map<char, std::string>& rules) : m_constances(constances), m_axiom(axiom), m_rules(rules) {}

Grammar::Grammar(const Grammar& other) : m_constances(other.m_constances), m_axiom(other.m_axiom), m_rules(other.m_rules) {}

Grammar::Grammar(Grammar&& other) noexcept : m_constances(std::move(other.m_constances)), m_axiom(std::move(other.m_axiom)), m_rules(std::move(other.m_rules)) {}

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

Grammar::~Grammar() = default;

const std::unordered_set<char>& Grammar::GetConstances() const {
    return m_constances;
}

const std::string& Grammar::GetAxiom() const {
    return m_axiom;
}

const std::unordered_map<char, std::string>& Grammar::GetRules() const {
    return m_rules;
}

LSystem::LSystem(const Grammar& grammar) : m_grammar(grammar) {}

LSystem::LSystem(const std::unordered_set<char>& constances, const std::string& axiom, const std::unordered_map<char, std::string>& rules) : m_grammar(constances, axiom, rules) {}

LSystem::~LSystem() = default;

void LSystem::SetNumberOfIterations(const uint16_t iterCount) {
    this->m_iterCount = iterCount;
}

std::shared_ptr<const std::string> LSystem::Iterate(const uint16_t iterCount) {
    Timer t;
    auto currentState = std::make_shared<std::string>(m_grammar.GetAxiom());

    const auto& constances = m_grammar.GetConstances();
    const auto& rules = m_grammar.GetRules();

    for (uint16_t i = 0; i < iterCount; ++i) {
        std::string nextGeneration;
        nextGeneration.reserve(currentState->size() * 2);

        for (const auto& j : *currentState) {
            std::string_view ruleOrConst;
            ruleOrConst = (constances.find(j) == constances.end()) ? rules.at(j) : std::string_view(&j, 1);
            nextGeneration.append(ruleOrConst);
        }

        currentState->swap(nextGeneration);
        nextGeneration.clear();
    }

    return currentState;
}
