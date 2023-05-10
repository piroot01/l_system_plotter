#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <vector>

#include "LSystem.hpp"
#include "ConfigReader.hpp"
#include "LSystemInterpreterDefaults.hpp"

constexpr const char* configInterpreterSection = "l_system_interpreter";
constexpr const char* configBuilderSection = "l_system_builder";

struct Point {
    double x;
    double y;

};

struct Line {
    std::vector<Point> line;

};

struct Position {
    Point position;
    double angle_deg;

};

struct LSystemStructure {
    std::vector<Line> m_structure;
    Position pos;

};

class LSystemBuilder {
public:
    LSystemBuilder();
    LSystemBuilder(const ConfigReader& config);
    void SetStructure(const std::shared_ptr<LSystemStructure>& structure);

    void DrawALine() const;
    void MoveForwardWithoutDrawing() const;
    void DoNothing() const;
    void RotateLeft() const;
    void RotateRight() const;
    void Rotate180Deg() const;
    void SaveCurrentState() const;
    void MoveToLastSavedState() const;

private:
    double m_initAngle_deg = LSystemBuilderDefaults::init_angle_deg;
    double m_vectorNorm_px = LSystemBuilderDefaults::vector_norm_px;
    double m_stepAngle_deg = LSystemBuilderDefaults::step_angle_deg;

    std::shared_ptr<LSystemStructure> m_structure;

};

struct LSystemAction {
    std::unordered_set<char> actionSet;
    std::function<void(const LSystemBuilder&)> actionFunc;

};

class LSystemInterpreter {
public:
    explicit LSystemInterpreter(const std::shared_ptr<const std::string> lSystem);
    LSystemInterpreter(const std::shared_ptr<const std::string>& lSystem, const ConfigReader& config);
    LSystemInterpreter(const LSystemInterpreter& other);
    LSystemInterpreter(LSystemInterpreter&& other) noexcept;
    LSystemInterpreter& operator=(const LSystemInterpreter& other);
    LSystemInterpreter& operator=(LSystemInterpreter&& other) noexcept;
    ~LSystemInterpreter();

    void Interpret(LSystemBuilder& builder);
    void PrintConfig() const;

private:
    std::unordered_map<std::string, LSystemAction> m_actionConfig;
    std::shared_ptr<const std::string> m_lSystem;
    LSystemStructure m_structure;

};
