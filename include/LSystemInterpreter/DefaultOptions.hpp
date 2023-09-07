#pragma once

#include "Data.hpp"

namespace LSystemInterpreter {

namespace DefaultOptions {

class Interpreter {
public:
	static const Data::ActionSet draw_a_line;
    static const Data::ActionSet move_forward_without_drawing;
    static const Data::ActionSet do_nothing;
    static const Data::ActionSet rotate_left;
    static const Data::ActionSet rotate_right;
    static const Data::ActionSet rotate_180_deg;
    static const Data::ActionSet save_current_state;
    static const Data::ActionSet move_to_last_saved_state;

    // @TODO Add adidional settings

};

class StructureBuilder {
public:
    static constinit double init_angle_deg;
    static constinit double vector_norm_px;
    static constinit double step_angle_deg;

    // @TODO Add adidional settings

};

}

}
