#pragma once

#include "DefaultOptions.hpp"
#include "Data.hpp"

namespace LSystemInterpreter {

namespace Options {

class StructureBuilder {
public:
    double initAngle_deg;
    double vectorNorm_px;
    double stepAngle_deg;

    StructureBuilder& operator=(const DefaultOptions::StructureBuilder& lhs);
    StructureBuilder& operator=(const Options::StructureBuilder& lhs);

    // @TODO Add assign and move operator

};

class Interpreter {
public:
    Data::ActionSet drawALine;

    // @TODO Rest of options

};

}

}
