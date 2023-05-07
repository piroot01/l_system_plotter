#pragma once

#define L_SYSTEM_H_
#ifdef L_SYSTEM_H_

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <optional>

class Grammar {
public:
    Grammar(const std::unordered_set<char>& constances, const std::string& axiom, const std::unordered_map<char, std::string>& rules);
    ~Grammar() = default;
    Grammar(const Grammar& other);
    Grammar(Grammar&& other) noexcept;

    const std::unordered_set<char>& GetConstances() const;
    const std::string& GetAxiom() const;
    const std::unordered_map<char, std::string>& GetRules() const;

    Grammar& operator=(const Grammar& other);
    Grammar& operator=(Grammar&& other) noexcept;

private:
    std::unordered_set<char> m_constances;
    std::string m_axiom;
    std::unordered_map<char, std::string> m_rules;

};

class LSystem {
public:
    LSystem(const Grammar& grammar);
    LSystem(const std::unordered_set<char>& constances, const std::string& axiom, const std::unordered_map<char, std::string>& rules);
    ~LSystem() = default;
    LSystem(const LSystem&) = delete;
    LSystem(LSystem&&) = delete;

    void SetNumberOfIterations(const uint16_t iterCount = 1);
    std::shared_ptr<const std::string> Iterate(const uint16_t iterCount = 1);

    LSystem& operator=(const LSystem&) = delete;
    LSystem& operator=(LSystem&&) = delete;

private:
    Grammar m_grammar;
    uint16_t m_iterCount;

};

#endif
