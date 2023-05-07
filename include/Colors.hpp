#pragma once

#include <cstdint>
#include <string>

struct Color {
    Color(const uint8_t r, const uint8_t g, const uint8_t b) : red(r / 255.0f), green(g / 255.0f), blue(b / 255.0f) {}
    float red;
    float green;
    float blue;

};

class Colors {
public:
    static const Color Blue;
    static const Color Green;
    static const Color White;
    static const Color Black;
    static const Color Brown;
    static const Color Red;
    static const Color PastelBlue;
    static const Color PastelGreen;
    static const Color PastelRed;
    static const Color PastelYellow;
    static const Color PastelPurple;
    static const Color PastelGray;
    static const Color PastelPink;
    static const Color PastelOrange;
    static const Color PastelBlack;
};
