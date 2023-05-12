#include <memory>

#include "LSystemInterpreter/Interpreter.hpp"
#include "LSystemInterpreter/Actions.hpp"
#include "LSystemInterpreter/Data.hpp"
#include "LSystemInterpreter/DefaultOptions.hpp"
#include "LSystemInterpreter/Options.hpp"
#include "LSystemInterpreter/Exception.hpp"
#include "Actions.tcc"

namespace LSystemInterpreter {

Interpreter::StructureBuilder::StructureBuilder() {
    m_options = DefaultOptions::StructureBuilder();
    InitializeStructure();
}

Interpreter::StructureBuilder::StructureBuilder(const Options::StructureBuilder& options) {
    m_options = options;
    InitializeStructure();
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

void Interpreter::StructureBuilder::InitializeStructure() {
    m_structure.position.position = {0, 0};
    m_structure.position.angle_deg = m_options.initAngle_deg;
    m_structure.structure.emplace_back(Data::Line(Data::Point(0, 0)));
}

Interpreter::Interpreter::Interpreter(const std::shared_ptr<const Data::RawLSystem>& rawLSystem)
    : m_rawLSystem(rawLSystem) {
    m_actions.Register<Actions::DrawALine>(DefaultOptions::Interpreter::draw_a_line);
    m_actions.Register<Actions::MoveForwardWithoutDrawing>(DefaultOptions::Interpreter::move_forward_without_drawing);
    m_actions.Register<Actions::DoNothing>(DefaultOptions::Interpreter::do_nothing);
    m_actions.Register<Actions::RotateLeft>(DefaultOptions::Interpreter::rotate_left);
    m_actions.Register<Actions::RotateRight>(DefaultOptions::Interpreter::rotate_right);
    m_actions.Register<Actions::Rotate180Deg>(DefaultOptions::Interpreter::rotate_180_deg);
    m_actions.Register<Actions::SaveCurrentState>(DefaultOptions::Interpreter::save_current_state);
    m_actions.Register<Actions::MoveToLastSavedState>(DefaultOptions::Interpreter::move_to_last_saved_state);

    // @TODO Do other actions
}

Interpreter::Interpreter::Interpreter(const std::shared_ptr<const Data::RawLSystem>& rawLSystem, const Options::Interpreter& options)
    : m_rawLSystem(rawLSystem) {
    m_actions.Register<Actions::DrawALine>(options.drawALine);
    m_actions.Register<Actions::MoveForwardWithoutDrawing>(options.moveForwardWithoutDrawing);
    m_actions.Register<Actions::DoNothing>(options.doNothing);
    m_actions.Register<Actions::RotateLeft>(options.rotateLeft);
    m_actions.Register<Actions::RotateRight>(options.rotateRight);
    m_actions.Register<Actions::Rotate180Deg>(options.rotate180Deg);
    m_actions.Register<Actions::SaveCurrentState>(options.saveCurrentState);
    m_actions.Register<Actions::MoveToLastSavedState>(options.moveToLastSavedState);

    // @TODO Do other actions
}

void Interpreter::Interpreter::Execute(StructureBuilder& structureBuilder) {
    structureBuilder.LoadRegistry(m_actions);

    for (const Data::Action& action : *m_rawLSystem)
        structureBuilder.Execute(action);
}

}
