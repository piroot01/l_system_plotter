#include <unordered_set>

#include "LSystemInterpreter/Data.hpp"

Data::Point::Point()
    : x(0), y(0) {}

Data::Point::Point(const Data::Real x, const Data::Real y)
    : x(x), y(y) {}

Data::Point::~Point() = default;

Data::Point::Point(const Data::Point& other) : x(other.x), y(other.y) {}

Data::Point& Data::Point::operator=(const Data::Point& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
    }

    return *this;
}

Data::Line::Line()
    : line({}) {}

Data::Line::Line(const std::initializer_list<Data::Point>& initList)
    : line(initList) {}

Data::Line::~Line() = default;

Data::Line::Line(const Line& other)
    : line(other.line) {}

Data::Line& Data::Line::operator=(const Data::Line& other) {
    if (this != &other)
        line = other.line;

    return *this;
}

Data::Position::Position()
    : position(0, 0), angle_deg(0) {}

Data::Position::Position(const Data::Point& position, const Data::Real angle_deg) 
    : position(position.x, position.y), angle_deg(angle_deg) {}

Data::Position::~Position() = default;

Data::Position::Position(const Data::Position& other)
    : position(other.position), angle_deg(other.angle_deg) {}

Data::Position& Data::Position::operator=(const Data::Position& other) {
    if (this != &other) {
        position = other.position;
        angle_deg = other.angle_deg;
    }

    return *this;
}

Data::Structure::Structure()
    : structure({}), position({}) {}

Data::Structure::Structure(const Data::Position& position)
    : structure({}), position(position) {}

Data::Structure::~Structure() = default;

Data::Structure::Structure(const Data::Structure& other)
    : structure(other.structure), position(other.position) {}

Data::Structure& Data::Structure::operator=(const Data::Structure &other) {
    if (this != &other) {
        structure = other.structure;
        position = other.position;
    }

    return *this;
}

Data::ActionSet::ActionSet()
    : set({}) {}

Data::ActionSet::ActionSet(const std::initializer_list<Data::Action>& initList)
    : set(initList) {}

Data::ActionSet::~ActionSet() = default;

Data::ActionSet::ActionSet(const Data::ActionSet& other)
    : set(other.set) {}

Data::ActionSet& Data::ActionSet::operator=(const Data::ActionSet& other) {
    if (this != &other)
        set = other.set;

    return *this;
}
