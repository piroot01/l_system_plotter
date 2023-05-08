#include <algorithm>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <regex>
#include <unordered_set>
#include <iostream>

#include "ConfigReader.hpp"
#include "LSystem.hpp"
#include "LSystemInterpreter.hpp"

LSystemBuilder::LSystemBuilder() = default;

LSystemBuilder::LSystemBuilder(const ConfigReader& config) {
    m_initAngle_deg = config.GetRawValues(configBuilderSection).get<double>(".init_angle_deg");
    m_initAngle_deg = config.GetRawValues(configBuilderSection).get<double>(".vector_norm_deg");
    m_initAngle_deg = config.GetRawValues(configBuilderSection).get<double>(".step_angle_deg");
}

void LSystemBuilder::SetStructure(const std::shared_ptr<LSystemStructure>& structure) {
    m_structure = structure;
}

LSystemInterpreter::LSystemInterpreter(const std::shared_ptr<const std::string> lSystem) : m_lSystem(lSystem) {
    m_actionConfig = {
        {"draw_a_line", {LSystemInterpreterDefaults::draw_a_line, [](const LSystemBuilder& builder) { builder.DrawALine(); }}},
        {"move_forward_without_drawing", {LSystemInterpreterDefaults::move_forward_without_drawing, [](const LSystemBuilder& builder) { builder.MoveForwardWithoutDrawing(); }}},
        {"do_nothing", {LSystemInterpreterDefaults::do_nothing, [](const LSystemBuilder& builder) { builder.DoNothing(); }}},
        {"rotate_left", {LSystemInterpreterDefaults::rotate_left, [](const LSystemBuilder& builder) { builder.RotateLeft(); }}},
        {"rotate_right", {LSystemInterpreterDefaults::rotate_right, [](const LSystemBuilder& builder) { builder.RotateRight(); }}},
        {"rotate_180_deg", {LSystemInterpreterDefaults::rotate_180_deg, [](const LSystemBuilder& builder) { builder.Rotate180Deg(); }}},
        {"save_current_state", {LSystemInterpreterDefaults::save_current_state, [](const LSystemBuilder& builder) { builder.SaveCurrentState(); }}},
        {"move_to_last_saved_state", {LSystemInterpreterDefaults::move_to_last_saved_state, [](const LSystemBuilder& builder) { builder.MoveToLastSavedState(); }}},
    };

}

LSystemInterpreter::LSystemInterpreter(const LSystemInterpreter& other)
    : m_actionConfig(other.m_actionConfig), m_lSystem(other.m_lSystem) {}

LSystemInterpreter::LSystemInterpreter(LSystemInterpreter&& other) noexcept
    : m_actionConfig(std::move(other.m_actionConfig)), m_lSystem(std::move(other.m_lSystem)) {}

LSystemInterpreter& LSystemInterpreter::operator=(const LSystemInterpreter& other) {
    if (this != &other) {
        m_actionConfig = other.m_actionConfig;
        m_lSystem = other.m_lSystem;
    }
    return *this;
}

LSystemInterpreter& LSystemInterpreter::operator=(LSystemInterpreter&& other) noexcept {
    if (this != &other) {
        m_actionConfig = std::move(other.m_actionConfig);
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

LSystemInterpreter::LSystemInterpreter(const std::shared_ptr<const std::string>& lSystem, const ConfigReader& config) : LSystemInterpreter(lSystem) {
    for (const auto& opt : m_actionConfig) {
        std::string optName = configInterpreterSection + std::string(".") + opt.first;

        if (!config.IsInConfig(optName))
            continue;

        std::unordered_set<char> optVal;
        const auto& values = config.GetRawValues(optName);
        insertValues(values, std::move(optVal));
        m_actionConfig[opt.first].actionSet = std::move(optVal);
    }
}

void LSystemInterpreter::Interpret(LSystemBuilder& builder) {
    builder.SetStructure(std::make_shared<LSystemStructure>(m_structure));

    for (const auto& action : *m_lSystem) {
        std::string found_category;
        bool found = false;

        for (const auto& iter : m_actionConfig) {
            if (iter.second.actionSet.find(action) != iter.second.actionSet.end()) {
                found_category = iter.first;
                found = true;
                break;
            }
        }

        if (found) {
            m_actionConfig[found_category].actionFunc(builder);
        }
    }
}

void LSystemInterpreter::PrintConfig(void) const {
    for (const auto& tag : m_actionConfig) {
        std::cout << tag.first << ": ";

        for (const auto& opt : tag.second.actionSet)
            std::cout << opt << ", ";

        std::cout << std::endl;
    }

    std::cout << *m_lSystem << '\n';
}
