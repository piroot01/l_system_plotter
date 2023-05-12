#include "LSystemInterpreter/Options.hpp"
#include "LSystemInterpreter/DefaultOptions.hpp"

namespace LSystemInterpreter {

Options::StructureBuilder::StructureBuilder() = default;

Options::StructureBuilder::~StructureBuilder() = default;

Options::StructureBuilder::StructureBuilder(const Options::StructureBuilder& other)
    : initAngle_deg(other.initAngle_deg), vectorNorm_px(other.vectorNorm_px), stepAngle_deg(other.stepAngle_deg) {}

Options::StructureBuilder& Options::StructureBuilder::operator=(const DefaultOptions::StructureBuilder& other) {
    initAngle_deg = other.init_angle_deg;
    vectorNorm_px = other.vector_norm_px;
    stepAngle_deg = other.step_angle_deg;

    return *this;
}

Options::StructureBuilder& Options::StructureBuilder::operator=(const Options::StructureBuilder& other) {
    initAngle_deg = other.initAngle_deg;
    vectorNorm_px = other.vectorNorm_px;
    stepAngle_deg = other.stepAngle_deg;

    return *this;
}

}
