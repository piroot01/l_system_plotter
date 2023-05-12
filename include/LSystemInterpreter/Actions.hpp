#pragma once

#include <unordered_map>
#include <unordered_set>
#include <memory>

#include "Data.hpp"
#include "Options.hpp"
#include "Exception.hpp"

namespace LSystemInterpreter {

namespace Actions {

class ActionInterface {
public:
    ActionInterface();
    virtual ~ActionInterface();

    virtual void Execute(Data::Structure& structure, const Options::StructureBuilder& options) const = 0;

    ActionInterface(const ActionInterface&) = delete;

    ActionInterface& operator=(const ActionInterface&) = delete;

};

class ActionRegistry {
public:
    ActionRegistry();
    ~ActionRegistry();

    template<typename ActionType>
    void Register(const Data::ActionSet& actionSet);

    const ActionInterface* FindAction(const Data::Action input) const;

    ActionRegistry(const ActionRegistry& other);
    ActionRegistry(ActionRegistry&& other) noexcept;

    ActionRegistry& operator=(const ActionRegistry& other);
    ActionRegistry& operator=(ActionRegistry&& other) noexcept;

private:
    std::unordered_map<Data::Action, std::shared_ptr<ActionInterface>> m_actionMap;

};

class DrawALine : public ActionInterface {
public:
    void Execute(Data::Structure& structure, const Options::StructureBuilder& options) const override;

};

class MoveForwardWithoutDrawing : public ActionInterface {
public:
    void Execute(Data::Structure& structure, const Options::StructureBuilder& options) const override;

};

class DoNothing : public ActionInterface {
public:
    void Execute(Data::Structure& structure, const Options::StructureBuilder& options) const override;

};

class RotateLeft : public ActionInterface {
public:
    void Execute(Data::Structure& structure, const Options::StructureBuilder& options) const override;

};

class RotateRight : public ActionInterface {
public:
    void Execute(Data::Structure& structure, const Options::StructureBuilder& options) const override;

};

class Rotate180Deg : public ActionInterface {
public:
    void Execute(Data::Structure& structure, const Options::StructureBuilder& options) const override;

};

class SaveCurrentState : public ActionInterface {
public:
    void Execute(Data::Structure& structure, const Options::StructureBuilder& options) const override;

};

class MoveToLastSavedState : public ActionInterface {
public:
    void Execute(Data::Structure& structure, const Options::StructureBuilder& options) const override;

};

// @brief All actions will be placed here
// @TODO Finish all basic operations

}

}
