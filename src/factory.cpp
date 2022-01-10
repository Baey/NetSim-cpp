//
// Created by szczy on 04.01.2022.
//

#include <exception>
#include "factory.hpp"

bool has_reachable_storehouse(const PackageSender* sender, std::map<const PackageSender*, NodeColor>& node_colors){
    if(node_colors[sender] == NodeColor::VERIFIED){
        return true;
    }
    node_colors[sender] = NodeColor::VISITED;
    if(sender->receiver_preferences_.get_preferences().empty()){
        throw std::logic_error("Sender has not got any receivers");
    }
    bool has_sender_at_least_one_receiver_other_than_himself = false;
    for(auto receiver : sender->receiver_preferences_.get_preferences()){
        if(receiver.first->get_receiver_type() == ReceiverType::Storehouse){
            has_sender_at_least_one_receiver_other_than_himself = true;
        }
        else if(receiver.first->get_receiver_type() == ReceiverType::Worker){
            IPackageReceiver* receiver_ptr = receiver.first;
            auto worker_ptr = dynamic_cast<class Worker*>(receiver_ptr);
            auto sendrecv_ptr = dynamic_cast<PackageSender*>(worker_ptr);
            if(sendrecv_ptr == sender){
                continue;
            }
            has_sender_at_least_one_receiver_other_than_himself = true;
            if(node_colors[sendrecv_ptr] == NodeColor::UNVISITED){
                has_reachable_storehouse(sendrecv_ptr,node_colors);
            }
        }
    }
    node_colors[sender] = NodeColor::VERIFIED;
    if(has_sender_at_least_one_receiver_other_than_himself){
        return true;
    }
    else{
        throw std::logic_error("Error");
    }
}

bool Factory::is_consistant() {
    std::map<const PackageSender*,  NodeColor> node_colors;
    //FIXME:
    // Nie wiem jak dostać się w tych pętlach do PackageSender* - na razie komentuję błędy
    for(auto &ramp : ramps_){
        node_colors[&ramp] = NodeColor::UNVISITED;
    }
//    std::for_each(ramps_.cbegin(), ramps_.cend(), [&node_colors](class Ramp& r){
//        node_colors[&r] = NodeColor::UNVISITED;
//    })
    for(auto &worker : workers_){
        node_colors[&worker] = NodeColor::UNVISITED;
    }
    try {
        for(auto &ramp : ramps_){
            has_reachable_storehouse(&ramp, node_colors);
        }
    } catch(std::logic_error& ex){
        return false;
    }
    return true;
}

void Factory::do_deliveries(Time t) {
    for (auto &ramp : ramps_) {
        ramp.deliver_goods(t);
    }
}

void Factory::do_package_passing() {
    for (auto &ramp : ramps_) {
        ramp.send_package();
    }
    for (auto &worker : workers_) {
        worker.send_package();
    }
}


/*Nie jestem pewien czy nie napisałem tej funckji w nodes.cpp, dla Workera a nie dla fabryki*/
void Factory::do_work(Time t) {
    for (auto &worker : workers_) {
        worker.do_work(t);
    }
}

void Factory::remove_worker(ElementID id) {
//    remove_receiver(ramps_, id);
    remove_receiver(workers_, id);
//    workers_.remove_by_id(id);
}

void Factory::remove_storehouse(ElementID id) {
    remove_receiver(storehouses_, id);
//    storehouses_.remove_by_id(id);
}

void Factory::remove_links(IPackageReceiver *receiver) {
    std::for_each(ramps_.begin(), ramps_.end(), [&receiver](class Ramp& ramp) {
        ramp.receiver_preferences_.remove_receiver(receiver);
    });

    std::for_each(workers_.begin(), workers_.end(), [&receiver](class Worker& worker) {
        worker.receiver_preferences_.remove_receiver(receiver);
    });
}
