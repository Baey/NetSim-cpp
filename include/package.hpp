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

    /* Customowy destruktor, który jest konieczny żeby operowanie na feed_IDs_ i assigned_IDs_ miało
     * jakikolwiek sens. Mam nadzieję, że jak się robi własny destruktor to nie trzeba jakoś ręcznie zwlaniać
     * miejsca w pamięci przypisanego do danej instancji. */
    ~Package() { assigned_IDs_.erase(assigned_IDs_.find(ElementID_)); }

    ElementID get_id() const { return ElementID_; }

    /* Chciałem zdefiniować ten operator z dwoma argumentami i zwroćić boola z porównania ich pól .ElementID
     * ale się wkurzał Clion, że za dużo argumentów, więc przypomniałem sobie o istnieniu czegoś takiego jak this.
     * Pojęcia nie mam czy to jest dobrze, wyjdzie w praniu. */
    bool operator==(const Package &lhs) const { return lhs.ElementID_ == this->ElementID_; };
private:
    static std::set<ElementID> freed_IDs_;
    static std::set<ElementID> assigned_IDs_;

    ElementID ElementID_;
};

#endif //NETSIM_CPP_PACKAGE_HPP
