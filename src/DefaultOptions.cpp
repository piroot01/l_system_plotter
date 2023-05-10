#include "LSystemInterpreter/DefaultOptions.hpp"

const Data::ActionSet DefaultOptions::Interpreter::draw_a_line = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U'};
const Data::ActionSet DefaultOptions::Interpreter::move_forward_without_drawing = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u'};
const Data::ActionSet DefaultOptions::Interpreter::do_nothing = {'V', 'W', 'X', 'Y', 'Z', 'v', 'w', 'x', 'y', 'z'};
const Data::ActionSet DefaultOptions::Interpreter::rotate_left = {'+'};
const Data::ActionSet DefaultOptions::Interpreter::rotate_right = {'-'};
const Data::ActionSet DefaultOptions::Interpreter::rotate_180_deg = {'|'};
const Data::ActionSet DefaultOptions::Interpreter::save_current_state = {'['};
const Data::ActionSet DefaultOptions::Interpreter::move_to_last_saved_state = {']'};

constinit double DefaultOptions::StructureBuilder::init_angle_deg = 0;
constinit double DefaultOptions::StructureBuilder::vector_norm_px = 10;
constinit double DefaultOptions::StructureBuilder::step_angle_deg = 45;

