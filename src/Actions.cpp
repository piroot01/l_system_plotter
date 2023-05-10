#include "LSystemInterpreter/Actions.hpp"
#include "LSystemInterpreter/Data.hpp"
#include "LSystemInterpreter/Options.hpp"
#include <memory>

Actions::ActionInterface::~ActionInterface() = default;

template<typename ActionType>
void Actions::ActionRegistry::Register(const Data::ActionSet& actionSet) {
    for (const auto& action : actionSet.set)
        m_actionMap.emplace(action, std::make_shared<ActionType>());
}

const Actions::ActionInterface* Actions::ActionRegistry::FindAction(const Data::Action input) const {
    auto foudAction = m_actionMap.find(input);
    return foudAction != m_actionMap.end() ? foudAction->second.get() : nullptr;
}

// @TODO Finish basic operations
