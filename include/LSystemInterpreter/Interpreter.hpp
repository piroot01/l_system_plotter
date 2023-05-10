#pragma once

#include <memory>
#include <unordered_map>

#include "Actions.hpp"
#include "Options.hpp"
#include "DefaultOptions.hpp"
#include "Data.hpp"

namespace Interpreter {

class StructureBuilder {
public:
    StructureBuilder();
    StructureBuilder(const Options::StructureBuilder& options);

    const Data::Structure& GetStructure() const;

    // @TODO Rule of five

private:
    void Execute(const Data::Action action);
    void LoadRegistry(const Actions::ActionRegistry& registry);

private:
    const Actions::ActionRegistry* m_actions;
    Data::Structure m_structure;
    Options::StructureBuilder m_options;

public:
    friend class Interpreter;

};

class Interpreter {
public:
    explicit Interpreter(const std::shared_ptr<const Data::RawLSystem>);
    Interpreter(const std::shared_ptr<const Data::RawLSystem>, const Options::Interpreter& options);
    void Execute(StructureBuilder& structureBuilder);

    // @TODO Rule of five

private:
    std::shared_ptr<const Data::RawLSystem> m_rawLSystem;
    Actions::ActionRegistry m_actions;

};

}
