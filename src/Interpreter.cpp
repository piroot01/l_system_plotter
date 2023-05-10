#include "LSystemInterpreter/Interpreter.hpp"
#include "LSystemInterpreter/Actions.hpp"
#include "LSystemInterpreter/Data.hpp"
#include "LSystemInterpreter/DefaultOptions.hpp"
#include "LSystemInterpreter/Options.hpp"

Interpreter::StructureBuilder::StructureBuilder() {
    m_options = DefaultOptions::StructureBuilder();
}

Interpreter::StructureBuilder::StructureBuilder(const Options::StructureBuilder& options) {
    m_options = options;
}

const Data::Structure& Interpreter::StructureBuilder::GetStructure() const {
    return m_structure;
}

void Interpreter::StructureBuilder::Execute(const Data::Action action) {
    const Actions::ActionInterface* foundAction = m_actions->FindAction(action);

    // @TODO Exception handling
    if (foundAction)
        foundAction->Execute(m_structure, m_options);
}
