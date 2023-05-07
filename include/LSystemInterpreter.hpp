#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "LSystem.hpp"
#include "ConfigReader.hpp"
#include "LSystemInterpreterDefaults.hpp"

constexpr const char* configSectionName = "l_system_interpreter";

class LSystemInterpreter {
public:
    explicit LSystemInterpreter(const std::shared_ptr<const std::string> lSystem);
    LSystemInterpreter(const std::shared_ptr<const std::string>& lSystem, const ConfigReader& config);
    LSystemInterpreter(const LSystemInterpreter& other);
    LSystemInterpreter(LSystemInterpreter&& other) noexcept;
    LSystemInterpreter& operator=(const LSystemInterpreter& other);
    LSystemInterpreter& operator=(LSystemInterpreter&& other) noexcept;
    ~LSystemInterpreter();

    void PrintConfig(void) const;

private:
    std::unordered_map<std::string, std::unordered_set<char>> m_config = {
        {"draw_a_line", LSystemInterpreterDefaults::draw_a_line},
        {"move_forward_without_drawing", LSystemInterpreterDefaults::move_forward_without_drawing},
        {"do_nothing", LSystemInterpreterDefaults::do_nothing},
        {"rotate_left", LSystemInterpreterDefaults::rotate_left},
        {"rotate_right", LSystemInterpreterDefaults::rotate_right},
        {"rotate_180_degrees", LSystemInterpreterDefaults::rotate_180_degrees},
        {"save_current_state", LSystemInterpreterDefaults::save_current_state},
        {"move_to_last_saved_state", LSystemInterpreterDefaults::move_to_last_saved_state},
    };

    std::shared_ptr<const std::string> m_lSystem;

};
