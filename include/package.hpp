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

    explicit Package(ElementID elementID);

    Package(const Package& Package) = delete;

    Package(Package&& Package);

    Package& operator=(const Package& other) = delete;

    Package& operator=(Package&&) noexcept;

    bool operator==(const Package &other) const { return ElementID_ == other.ElementID_ ; };

    ElementID get_id() const { return ElementID_; }

    static std::set<ElementID> get_freed() { return freed_IDs_; }

    static std::set<ElementID> get_assigned() { return assigned_IDs_; }

    ~Package();

private:
    static std::set<ElementID> freed_IDs_;
    static std::set<ElementID> assigned_IDs_;

    ElementID ElementID_;

    static const ElementID undefinedID_ = -1;
};

#endif //NETSIM_CPP_PACKAGE_HPP
