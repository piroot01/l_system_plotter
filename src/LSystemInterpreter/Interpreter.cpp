#include <memory>

#include "LSystemInterpreter/Interpreter.hpp"
#include "LSystemInterpreter/Actions.hpp"
#include "LSystemInterpreter/Data.hpp"
#include "LSystemInterpreter/DefaultOptions.hpp"
#include "LSystemInterpreter/Options.hpp"
#include "LSystemInterpreter/Exception.hpp"

namespace LSystemInterpreter {

Interpreter::StructureBuilder::StructureBuilder() {
    m_options = DefaultOptions::StructureBuilder();
    m_structure.position.position = {0, 0};
    m_structure.position.angle_deg = m_options.initAngle_deg;
    m_structure.structure.emplace_back(Data::Line(Data::Point(0, 0)));
}

Interpreter::StructureBuilder::StructureBuilder(const Options::StructureBuilder& options) {
    m_options = options;
}

const Data::Structure& Interpreter::StructureBuilder::GetStructure() const {
    return m_structure;
}

void Interpreter::StructureBuilder::Execute(const Data::Action action) {
    const Actions::ActionInterface* foundAction = m_actions->FindAction(action);

    if (foundAction)
        foundAction->Execute(m_structure, m_options);
    else
        throw Exception("Invalid action.");
}

void Interpreter::StructureBuilder::LoadRegistry(const Actions::ActionRegistry& registry) {
    m_actions = &registry;
}

Interpreter::Interpreter::Interpreter(const std::shared_ptr<const Data::RawLSystem>& rawLSystem)
    : m_rawLSystem(rawLSystem) {
    m_actions.Register<Actions::DrawALine>(DefaultOptions::Interpreter::draw_a_line);

    // @TODO Do other actions
}

Interpreter::Interpreter::Interpreter(const std::shared_ptr<const Data::RawLSystem>& rawLSystem, const Options::Interpreter& options)
    : m_rawLSystem(rawLSystem) {
    m_actions.Register<Actions::DrawALine>(options.drawALine);

    // @TODO Do other actions
}

void Interpreter::Interpreter::Execute(StructureBuilder& structureBuilder) {
    structureBuilder.LoadRegistry(m_actions);

    for (const Data::Action& action : *m_rawLSystem)
        structureBuilder.Execute(action);
}

}
