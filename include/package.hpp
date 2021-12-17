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
    Package();

    explicit Package(const ElementID id) : ElementID_(id) {}

    ElementID get_id() const { return ElementID_; }

    /* Tak podobno definiujemy operatory w c++ */
    bool operator==(const Package &lhs, const Package &rhs) { return lhs.ElementID_ == rhs.ElementID_; };
private:
    static std::set <ElementID> freed_IDs_;
    static std::set <ElementID> assigned_IDs_;

    ElementID ElementID_;
};

#endif //NETSIM_CPP_PACKAGE_HPP
