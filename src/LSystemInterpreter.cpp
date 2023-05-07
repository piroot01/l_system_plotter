#include <algorithm>
#include <memory>
#include <string>
#include <unordered_map>
#include <regex>
#include <unordered_set>
#include <iostream>

#include "ConfigReader.hpp"
#include "LSystem.hpp"
#include "LSystemInterpreter.hpp"

LSystemInterpreter::LSystemInterpreter(const std::shared_ptr<const std::string> lSystem) : m_lSystem(lSystem) {}

LSystemInterpreter::LSystemInterpreter(const LSystemInterpreter& other)
    : m_config(other.m_config), m_lSystem(other.m_lSystem) {}

LSystemInterpreter::LSystemInterpreter(LSystemInterpreter&& other) noexcept
    : m_config(std::move(other.m_config)), m_lSystem(std::move(other.m_lSystem)) {}

LSystemInterpreter& LSystemInterpreter::operator=(const LSystemInterpreter& other) {
    if (this != &other) {
        m_config = other.m_config;
        m_lSystem = other.m_lSystem;
    }
    return *this;
}

LSystemInterpreter& LSystemInterpreter::operator=(LSystemInterpreter&& other) noexcept {
    if (this != &other) {
        m_config = std::move(other.m_config);
        m_lSystem = std::move(other.m_lSystem);
    }
    return *this;
}

LSystemInterpreter::~LSystemInterpreter() = default;

void insertValues(const boost::property_tree::ptree& values, std::unordered_set<char>&& optVal) {
    for (const auto& value : values) {
        try {
            optVal.insert(value.second.get_value<char>());
        } catch (const boost::property_tree::ptree_bad_data& e) {
            throw ConfigReaderException("Failed to cast value to char: " + std::string(e.what()));
        }
    }
}

LSystemInterpreter::LSystemInterpreter(const std::shared_ptr<const std::string>& lSystem, const ConfigReader& config) : m_lSystem(lSystem) {
    for (const auto& opt : m_config) {
        std::string optName = configSectionName + std::string(".") + opt.first;

        if (!config.IsInConfig(optName))
            continue;

        std::unordered_set<char> optVal;
        const auto& values = config.GetRawValues(optName);
        insertValues(values, std::move(optVal));
        m_config[opt.first] = std::move(optVal);
    }
}

void LSystemInterpreter::PrintConfig() const {
    for (const auto& tag : m_config) {
        std::cout << tag.first << ": ";

        for (const auto& opt : tag.second)
            std::cout << opt << ", ";

        std::cout << std::endl;
    }

    std::cout << *m_lSystem << '\n';
}
