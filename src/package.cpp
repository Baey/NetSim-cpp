//
// Created by Błażej Szargut on 14/12/2021.
//

#include <package.hpp>

Package::Package() {
    if (!freed_IDs_.empty()) {
        ElementID_ = *(freed_IDs_.begin());
        /* Poprawka -> trzeba jeszcze dodać ID do zbioru przypisanych identyfikatorów */
        assigned_IDs_.insert(*(freed_IDs_.begin()));
        freed_IDs_.erase(freed_IDs_.begin());
    }
    else if (!assigned_IDs_.empty()) {
        ElementID_ = *(assigned_IDs_.end())++;
        assigned_IDs_.insert(*(assigned_IDs_.end())++);
    }
    else {
        ElementID_ = 0;
        assigned_IDs_.insert(0);
    }
}

Package::Package(const ElementID elementID) {
    ElementID_ = elementID;
    assigned_IDs_.insert(elementID);
}

