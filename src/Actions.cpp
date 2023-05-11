#include "LSystemInterpreter/Actions.hpp"
#include "LSystemInterpreter/Data.hpp"
#include "LSystemInterpreter/Options.hpp"
#include <algorithm>
#include <memory>

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
