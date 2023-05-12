#include <algorithm>
#include <memory>
#include <cmath>

#include "LSystemInterpreter/Actions.hpp"
#include "LSystemInterpreter/Data.hpp"
#include "LSystemInterpreter/Options.hpp"
#include "LSystemInterpreter/Exception.hpp"

namespace LSystemInterpreter {

Actions::ActionInterface::~ActionInterface() = default;

Actions::ActionInterface::ActionInterface() = default;

Actions::ActionRegistry::ActionRegistry() = default;

Actions::ActionRegistry::~ActionRegistry() = default;

Actions::ActionRegistry::ActionRegistry(const Actions::ActionRegistry& other) 
    : m_actionMap(other.m_actionMap) {}

Actions::ActionRegistry::ActionRegistry(Actions::ActionRegistry&& other) noexcept
    : m_actionMap(std::move(other.m_actionMap)) {}

Actions::ActionRegistry& Actions::ActionRegistry::operator=(const Actions::ActionRegistry& other) {
    if (this != &other)
        m_actionMap = other.m_actionMap;

    return *this;
}

Actions::ActionRegistry& Actions::ActionRegistry::operator=(Actions::ActionRegistry&& other) noexcept {
    if (this != &other)
        m_actionMap = std::move(other.m_actionMap);

    return *this;
}

const Actions::ActionInterface* Actions::ActionRegistry::FindAction(const Data::Action input) const {
    auto foudAction = m_actionMap.find(input);

    return foudAction != m_actionMap.end() ? foudAction->second.get() : nullptr;
}

void Actions::DrawALine::Execute(Data::Structure& structure, const Options::StructureBuilder& options) const {
    structure.position.position += Data::Point(std::cos(structure.position.angle_deg * Data::Pi / 180) * options.vectorNorm_px, std::sin(structure.position.angle_deg * Data::Pi / 180) * options.vectorNorm_px);
    structure.structure.back().line.push_back(structure.position.position);
}

void Actions::MoveForwardWithoutDrawing::Execute(Data::Structure& structure, const Options::StructureBuilder& options) const {
    structure.position.position += Data::Point(std::cos(structure.position.angle_deg * Data::Pi / 180) * options.vectorNorm_px, std::sin(structure.position.angle_deg * Data::Pi / 180) * options.vectorNorm_px);
}

void Actions::DoNothing::Execute(Data::Structure& structure, const Options::StructureBuilder& options) const {
    // literally do nothing :D
}

void Actions::RotateLeft::Execute(Data::Structure& structure, const Options::StructureBuilder& options) const {
    structure.position.angle_deg += options.stepAngle_deg;
}

void Actions::RotateRight::Execute(Data::Structure& structure, const Options::StructureBuilder& options) const {
    structure.position.angle_deg -= options.stepAngle_deg;
}

void Actions::Rotate180Deg::Execute(Data::Structure& structure, const Options::StructureBuilder& options) const {
    structure.position.angle_deg += 180.0;
}

void Actions::SaveCurrentState::Execute(Data::Structure& structure, const Options::StructureBuilder& options) const {
    structure.lifo.push_back(structure.position);
}

void Actions::MoveToLastSavedState::Execute(Data::Structure& structure, const Options::StructureBuilder& options) const {
    structure.position = structure.lifo.back();
    structure.lifo.pop_back();
}

// @TODO Finish basic operations

}
