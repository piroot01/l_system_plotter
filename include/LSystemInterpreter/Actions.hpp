#pragma once

#include <unordered_map>
#include <unordered_set>
#include <memory>

#include "Data.hpp"
#include "Options.hpp"

namespace Actions {

class ActionInterface {
public:
    virtual ~ActionInterface();
    virtual void Execute(Data::Structure& structure, const Options::StructureBuilder& options) const = 0;

    // @TODO class copy and assingn constructors

};

class ActionRegistry {
public:
    template<typename ActionType>
    void Register(const Data::ActionSet& actionSet);

    const ActionInterface* FindAction(const Data::Action input) const;

    // @TODO Rule of five

private:
    std::unordered_map<Data::Action, std::shared_ptr<ActionInterface>> m_actionMap;

};

// @brief All actions will be placed here
// @TODO Finish all basic operations

class DrawALine : public ActionInterface {
public:
    DrawALine();

    void Execute(Data::Structure& structure, const Options::StructureBuilder& options) const override;

};

}
