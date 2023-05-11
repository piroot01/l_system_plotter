#include <unordered_set>

#include "LSystemInterpreter/Data.hpp"

Data::ActionSet::ActionSet()
    : set({}) {}

Data::ActionSet::ActionSet(const std::initializer_list<Action>& initList)
    : set(initList) {}

Data::ActionSet::ActionSet(const Data::ActionSet& other)
    : set(other.set) {}

Data::ActionSet& Data::ActionSet::operator=(const Data::ActionSet& other) {
    if (this != &other)
        set = other.set;

    return *this;
}
