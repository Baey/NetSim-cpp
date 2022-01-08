//
// Created by szczy on 04.01.2022.
//

#include "factory.hpp"

bool has_reachable_storehouse(const PackageSender* sender, std::map<const PackageSender*, NodeColor>& node_colors){
    //TODO
}

template<class Node>
void NodeCollection<Node>::remove_by_id(ElementID id) {
    auto it = find_by_id(id);
    if(it != container_.end()){
        container_.erase(it);
    }
}

template<class Node>
typename NodeCollection<Node>::iterator NodeCollection<Node>::find_by_id(ElementID id) {
    return std::find_if(container_.begin(), container_.end(), [&id](const auto& elem){ return (elem.id_ == id);});
}


bool Factory::is_consistant() {
    return false; //TODO
}

void Factory::do_deliveries(Time t) {
    //TODO
}

void Factory::do_package_passing() {
    //TODO
}

void Factory::do_work(Time t) {
    //TODO
}

template<class Node>
void Factory::remove_receiver(NodeCollection<Node> &collection, ElementID id) {
    //TODO
}
