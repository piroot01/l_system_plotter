#pragma once

#include <unordered_set>

namespace LSystemInterpreterDefaults {
    const std::unordered_set<char> draw_a_line = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U'};
    const std::unordered_set<char> move_forward_without_drawing = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u'};
    const std::unordered_set<char> do_nothing = {'V', 'W', 'X', 'Y', 'Z', 'v', 'w', 'x', 'y', 'z'};
    const std::unordered_set<char> rotate_left = {'+'};
    const std::unordered_set<char> rotate_right = {'-'};
    const std::unordered_set<char> rotate_180_deg = {'|'};
    const std::unordered_set<char> save_current_state = {'['};
    const std::unordered_set<char> move_to_last_saved_state =  {']'};
}

namespace LSystemBuilderDefaults {
    constexpr double init_angle_deg = 0;
    constexpr double vector_norm_px = 10;
    constexpr double step_angle_deg = 45;
}
