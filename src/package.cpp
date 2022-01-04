//
// Created by Błażej Szargut on 14/12/2021.
//
#include "package.hpp"
#include "types.hpp"
#include <set>

/* Podobno tak powinno być zgodnie z dobrymi praktykami */
std::set<ElementID> Package::freed_IDs_;
std::set<ElementID> Package::assigned_IDs_;

Package::Package() {
    if (!freed_IDs_.empty()) {
        ElementID_ = *(freed_IDs_.begin());
        /* Poprawka -> trzeba jeszcze dodać ID do zbioru przypisanych identyfikatorów */
        assigned_IDs_.insert(*(freed_IDs_.begin()));
        freed_IDs_.erase(freed_IDs_.begin());
    } else if (!assigned_IDs_.empty()) {
        ElementID_ = *(assigned_IDs_.end()) + 1;
        assigned_IDs_.insert(ElementID_);
    } else {
        ElementID_ = 0;
        assigned_IDs_.insert(0);
    }
}

Package::Package(const ElementID elementID) {
    ElementID_ = elementID;
    assigned_IDs_.insert(elementID);
}

Package::~Package() {
    if (ElementID_ != undefinedID_) {
        assigned_IDs_.erase(assigned_IDs_.find(ElementID_));
        /* Należy również dodać usunięte ID do zbioru zwolnionych identyfikatorów */
        freed_IDs_.insert(ElementID_);
    }
}

Package &Package::operator=(Package &&package) noexcept {
    ElementID_ = package.ElementID_; // Dodać ifa
    package.ElementID_ = undefinedID_;
    return *this;
}

Package::Package(Package &&Package) {
    ElementID_ = Package.ElementID_;
    Package.ElementID_ = undefinedID_;
}
