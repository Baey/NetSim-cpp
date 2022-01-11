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

    Package(ElementID elementID);

    Package(const Package &Package) = delete;

    Package(Package &&package) noexcept { elementID_ = std::exchange(package.elementID_, undefinedID_); }

    Package &operator=(const Package &other) = delete;

    Package &operator=(Package &&) noexcept;

    bool operator==(const Package &other) const { return elementID_ == other.elementID_; };

    ElementID get_id() const { return elementID_; }

    static std::set<ElementID> get_freed() { return freed_IDs_; }

    static std::set<ElementID> get_assigned() { return assigned_IDs_; }

    ~Package();

private:

    static const ElementID undefinedID_;

    static std::set<ElementID> freed_IDs_;

    static std::set<ElementID> assigned_IDs_;

    ElementID elementID_;
};

#endif //NETSIM_CPP_PACKAGE_HPP
