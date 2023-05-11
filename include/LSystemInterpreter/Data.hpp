#pragma once

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <memory>

namespace LSystemInterpreter {

namespace Data {

using RawLSystem = std::string;
using Action = char;
using Real = double;

constexpr double Pi = 3.1415926535;

class Point {
public:
    Point();
    Point(const Real x, const Real y);
    ~Point();

    Point(const Point& other);

    Point& operator=(const Point& other);

public:
    Real x;
    Real y;

};

class Line {
public:
    Line();
    Line(const Point& start);
    Line(const std::initializer_list<Point>& initList);
    ~Line();

    Line(const Line& other);

    Line& operator=(const Line& other);

public:
    std::vector<Point> line;

};

class Position {
public:
    Position();
    Position(const Point& position, const Real angle_deg);
    ~Position();

    Position(const Position& other);

    Position& operator=(const Position& other);

public:
    Point position;
    Real angle_deg;

};

class Structure {
public:
    Structure();
    Structure(const Position& position);
    ~Structure();

    Structure(const Structure& other);

    Structure& operator=(const Structure& other);

public:
    std::vector<Line> structure;
    Position position;

};

class ActionSet {
public:
    ActionSet();
    ActionSet(const std::initializer_list<Action>& initList);
    ~ActionSet();

    ActionSet(const ActionSet& other);

    ActionSet& operator=(const ActionSet& other);

public:
    std::unordered_set<Action> set;

};

}

}
