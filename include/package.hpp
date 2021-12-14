//
// Created by Błażej Szargut on 14/12/2021.
//

#ifndef NETSIM_CPP_PACKAGE_HPP
#define NETSIM_CPP_PACKAGE_HPP

#include <vector>
#include <numeric>
#include <set>
#include "types.hpp"

class Package {
public:
    Package() {}
    Package(id) : elementId = id {}

    const ElementID get_id() const { return elementId; }
private:
    static set<ElementID> freed_IDs_;
    static set<ElementID> assigned_IDs_;

    ElementID elementId;
};

#endif //NETSIM_CPP_PACKAGE_HPP
