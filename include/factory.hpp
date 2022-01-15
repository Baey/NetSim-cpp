//
// Created by szczy on 04.01.2022.
//

#ifndef NETSIM_FACTORY_HPP
#define NETSIM_FACTORY_HPP

#include <iostream>
#include "types.hpp"
#include "storage_types.hpp"
#include "nodes.hpp"

enum NodeColor {
    UNVISITED,
    VISITED,
    VERIFIED
};

struct ParsedLineData {
    ElementType element_type_;
    std::map<std::string, std::string>  parameters_;
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

    NodeCollection<Node>::const_iterator find_by_id(ElementID id) const;

    iterator begin() { return container_.begin(); }

    iterator end() { return container_.end(); }

    const_iterator cbegin() const { return container_.cbegin(); }

    const_iterator cend() const { return container_.cend(); }

private:

    container_t container_;

};

class Factory {
public:

    // RAMP:

    void add_ramp(Ramp &&r) { ramps_.add(std::move(r)); }

    void remove_ramp(ElementID id) { ramps_.remove_by_id(id); }

    NodeCollection<Ramp>::iterator find_ramp_by_id(ElementID id) { return ramps_.find_by_id(id); }

    NodeCollection<Ramp>::const_iterator find_ramp_by_id(ElementID id) const { return ramps_.find_by_id(id); }

    NodeCollection<Ramp>::const_iterator ramp_cbegin() const { return ramps_.cbegin(); }

    NodeCollection<Ramp>::const_iterator ramp_cend() const { return ramps_.cend(); }

    // WORKER:

    void add_worker(Worker &&w) { workers_.add(std::move(w)); }

    void remove_worker(ElementID id);

    NodeCollection<Worker>::iterator find_worker_by_id(ElementID id) { return workers_.find_by_id(id); }

    NodeCollection<Worker>::const_iterator find_worker_by_id(ElementID id) const { return workers_.find_by_id(id); }

    NodeCollection<Worker>::const_iterator worker_cbegin() const { return workers_.cbegin(); }

    NodeCollection<Worker>::const_iterator worker_cend() const { return workers_.cend(); }

    // STOREHOUSE:

    void add_storehouse(Storehouse &&s) { storehouses_.add(std::move(s)); }

    void remove_storehouse(ElementID id);

    NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElementID id) {
        return storehouses_.find_by_id(id);
    }

    NodeCollection<Storehouse>::const_iterator
    find_storehouse_by_id(ElementID id) const { return storehouses_.find_by_id(id); }

    NodeCollection<Storehouse>::const_iterator storehouse_cbegin() const { return storehouses_.cbegin(); }

    NodeCollection<Storehouse>::const_iterator storehouse_cend() const { return storehouses_.cend(); }

    void remove_links(IPackageReceiver *receiver);

    //****************************************************************************************************************//

    bool is_consistent();

    void do_deliveries(Time t);

    void do_package_passing();

    void do_work(Time t);

private:

    template<class Node>
    void remove_receiver(NodeCollection<Node> &collection, ElementID id);

    NodeCollection<Ramp> ramps_;

    NodeCollection<Worker> workers_;

    NodeCollection<Storehouse> storehouses_;
};

template<class Node>
void Factory::remove_receiver(NodeCollection<Node> &collection, ElementID id) {
    Node *node = &(*collection.find_by_id(id));
    remove_links(node);
    collection.remove_by_id(id);
}

template<class Node>
typename NodeCollection<Node>::iterator NodeCollection<Node>::find_by_id(ElementID id) {
    return std::find_if(container_.begin(), container_.end(),
                        [&id](const auto &elem) { return (elem.get_id() == id); });
}

template<class Node>
typename NodeCollection<Node>::const_iterator NodeCollection<Node>::find_by_id(ElementID id) const {
    return std::find_if(container_.cbegin(), container_.cend(),
                        [&id](const auto &elem) { return (elem.get_id() == id); });
}

template<class Node>
void NodeCollection<Node>::remove_by_id(ElementID id) {
    auto it = find_by_id(id);
    if (it != container_.end()) {
        container_.erase(it);
    }
}
//bool has_reachable_storehouse(const PackageSender *sender, std::map<const PackageSender *, NodeColor> &node_colors);

Factory load_factory_structure(std::istream& is);

void save_factory_structure(Factory& worker, std::ostream& os);

ParsedLineData parse_line(std::string line);

#endif //NETSIM_FACTORY_HPP
