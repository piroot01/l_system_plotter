#pragma once

#include "DefaultOptions.hpp"

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

    // @TODO Finish this :D

};

}
