#include "LSystemInterpreter/Options.hpp"
#include "LSystemInterpreter/DefaultOptions.hpp"

namespace LSystemInterpreter {

Options::StructureBuilder& Options::StructureBuilder::operator=(const DefaultOptions::StructureBuilder& lhs) {
    initAngle_deg = lhs.init_angle_deg;
    vectorNorm_px = lhs.vector_norm_px;
    stepAngle_deg = lhs.step_angle_deg;

    return *this;
}

Options::StructureBuilder& Options::StructureBuilder::operator=(const Options::StructureBuilder& lhs) {
    initAngle_deg = lhs.initAngle_deg;
    vectorNorm_px = lhs.vectorNorm_px;
    stepAngle_deg = lhs.stepAngle_deg;

    return *this;
}

}
