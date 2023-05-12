#pragma once

#include "DefaultOptions.hpp"
#include "Data.hpp"

namespace LSystemInterpreter {

namespace Options {

class StructureBuilder {
public:
    StructureBuilder();
    ~StructureBuilder();

    StructureBuilder(const StructureBuilder& other);

    StructureBuilder& operator=(const DefaultOptions::StructureBuilder& other);
    StructureBuilder& operator=(const Options::StructureBuilder& other);

public:
    double initAngle_deg;
    double vectorNorm_px;
    double stepAngle_deg;

};

class Interpreter {
public:
    Data::ActionSet drawALine;
    Data::ActionSet moveForwardWithoutDrawing;
    Data::ActionSet doNothing;
    Data::ActionSet rotateLeft;
    Data::ActionSet rotateRight;
    Data::ActionSet rotate180Deg;
    Data::ActionSet saveCurrentState;
    Data::ActionSet moveToLastSavedState;

};

}

}
