#include "LSystemInterpreter/Actions.hpp"

namespace LSystemInterpreter {

template<typename ActionType>
void Actions::ActionRegistry::Register(const Data::ActionSet& actionSet) {
    if (actionSet.set.empty())
        throw Exception("ActionSet is empty.");

    for (const auto& action : actionSet.set)
        m_actionMap.emplace(action, std::make_shared<ActionType>());
}

}

