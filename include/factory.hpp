//
// Created by szczy on 04.01.2022.
//

#ifndef NETSIM_FACTORY_HPP
#define NETSIM_FACTORY_HPP

#include <iostream>
#include "types.hpp"
#include "storage_types.hpp"
#include "nodes.hpp"

enum class NodeColor {
    UNVISITED,
    VISITED,
    VERIFIED
};

template<class Node>
class NodeCollection {
public:

    // Umieszczenie słowa kluczowego `typename` jest niezbędne aby poinformować
    // kompilator, że `Node` to nazwa typu.

    using container_t = typename std::list<Node>;

    using iterator = typename container_t::iterator;

    using const_iterator = typename container_t::const_iterator;

    void add(Node &&node) { container_.push_back(std::move(node)); }

    void remove_by_id(ElementID id);

    NodeCollection<Node>::iterator find_by_id(ElementID id);

    NodeCollection<Node>::const_iterator find_by_id(ElementID id);

    iterator begin() { return container_.begin(); }

    iterator end() { return container_.end(); }

    const_iterator cbegin() const { return container_.cbegin(); }

    const_iterator cend() const { return container_.cend(); }

private:

    container_t container_;

};

//FIXME:
// Nie wiem czemu, żebym mógł określić tutaj gdziekolwiek typ na klasy Ramp, Worker i Storehouse
// muszę dodawać słowo class - tak kazał kompilator - nie podoba mi się to
class Factory {
public:

    // RAMP:

    void add_ramp(class Ramp &&r) { ramps_.add(std::move(r)); }

    void remove_ramp(ElementID id) { ramps_.remove_by_id(id); }

    NodeCollection<class Ramp>::iterator find_ramp_by_id(ElementID id) { return ramps_.find_by_id(id); }

    //FIXME Ten sam problem jak powyżej w szablonie klasy:
    //NodeCollection<class Ramp>::const_iterator find_ramp_by_id(ElementID id) {return ramps_.find_by_id(id); }

    NodeCollection<class Ramp>::const_iterator ramp_cbegin() const { return ramps_.cbegin(); }

    NodeCollection<class Ramp>::const_iterator ramp_cend() const { return ramps_.cend(); }

    // WORKER:

    void add_worker(class Worker &&w) { workers_.add(std::move(w)); }

    void remove_worker(ElementID id);

    NodeCollection<class Worker>::iterator find_worker_by_id(ElementID id) { return workers_.find_by_id(id); }

    //FIXME Ten sam problem jak powyżej w szablonie klasy:
    //NodeCollection<class Worker>::const_iterator find_worker_by_id(ElementID id) {return workers_.find_by_id(id); }

    NodeCollection<class Worker>::const_iterator worker_cbegin() const { return workers_.cbegin(); }

    NodeCollection<class Worker>::const_iterator worker_cend() const { return workers_.cend(); }

    // STOREHOUSE:

    void add_storehouse(class Storehouse &&s) { storehouses_.add(std::move(s)); }

    void remove_storehouse(ElementID id);

    NodeCollection<class Storehouse>::iterator find_storehouse_by_id(ElementID id) {
        return storehouses_.find_by_id(id);
    }

    //FIXME Ten sam problem jak powyżej w szablonie klasy:
    //NodeCollection<class Storehouse>::const_iterator find_storehouse_by_id(ElementID id) {return storehouses_.find_by_id(id); }

    NodeCollection<class Storehouse>::const_iterator storehouse_cbegin() const { return storehouses_.cbegin(); }

    NodeCollection<class Storehouse>::const_iterator storehouse_cend() const { return storehouses_.cend(); }

    //****************************************************************************************************************//

    bool is_consistant();

    void do_deliveries(Time t);

    void do_package_passing();

    void do_work(Time t);

private:

    template<class Node>
    void remove_receiver(NodeCollection<Node> &collection, ElementID id);

    NodeCollection<class Ramp> ramps_;

    NodeCollection<class Worker> workers_;

    NodeCollection<class Storehouse> storehouses_;
};

bool has_reachable_storehouse(const PackageSender *sender, std::map<const PackageSender *, NodeColor> &node_colors);

#endif //NETSIM_FACTORY_HPP
