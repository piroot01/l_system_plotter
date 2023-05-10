#pragma once

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <memory>

namespace Data {

using RawLSystem = std::string;
using Action = char;

// @TODO Add copy constructors and move constructors

class Point {
public:
    double x;
    double y;

};

class Line {
public:
    std::vector<Point> line;

};

class Position {
public:
    Point position;
    double angle_deg;

};

class Structure {
    std::vector<Line> structure;
    Position position;

};

class ActionSet {
public:
    ActionSet(const std::initializer_list<Action>& initList);

    std::unordered_set<Action> set;

};

}
