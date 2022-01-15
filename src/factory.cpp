//
// Created by szczy on 04.01.2022.
//

#include <exception>
#include <sstream>
#include <iostream>
#include "factory.hpp"

bool has_reachable_storehouse(const PackageSender *sender, std::map<const PackageSender *, NodeColor> &node_colors) {
    if (node_colors[sender] == NodeColor::VERIFIED) {
        return true;
    }
    node_colors[sender] = NodeColor::VISITED;
    if (sender->receiver_preferences_.get_preferences().empty()) {
        throw std::logic_error("Sender has not got any receivers");
    }
    bool has_sender_at_least_one_receiver_other_than_himself = false;
    for (auto receiver: sender->receiver_preferences_.get_preferences()) {
        if (receiver.first->get_receiver_type() == ElementType::STOREHOUSE) {
            has_sender_at_least_one_receiver_other_than_himself = true;
        } else if (receiver.first->get_receiver_type() == ElementType::WORKER) {
            IPackageReceiver *receiver_ptr = receiver.first;
            auto worker_ptr = dynamic_cast<Worker *>(receiver_ptr);
            auto sendrecv_ptr = dynamic_cast<PackageSender *>(worker_ptr);
            if (sendrecv_ptr == sender) {
                continue;
            }
            has_sender_at_least_one_receiver_other_than_himself = true;
            if (node_colors[sendrecv_ptr] == NodeColor::UNVISITED) {
                has_reachable_storehouse(sendrecv_ptr, node_colors);
            }
        }
    }
    node_colors[sender] = NodeColor::VERIFIED;
    if (has_sender_at_least_one_receiver_other_than_himself) {
        return true;
    } else {
        throw std::logic_error("Error");
    }
}

bool Factory::is_consistent() {
    std::map<const PackageSender *, NodeColor> node_colors;
    for (auto &ramp: ramps_) {
        node_colors[&ramp] = NodeColor::UNVISITED;
    }
    for (auto &worker: workers_) {
        node_colors[&worker] = NodeColor::UNVISITED;
    }
    try {
        for (auto &ramp: ramps_) {
            has_reachable_storehouse(&ramp, node_colors);
        }
    } catch (std::logic_error &ex) {
        return false;
    }
    return true;
}

void Factory::do_deliveries(Time t) {
    for (auto &ramp: ramps_) {
        ramp.deliver_goods(t);
    }
}

void Factory::do_package_passing() {
    for (auto &ramp: ramps_) {
        ramp.send_package();
    }
    for (auto &worker: workers_) {
        worker.send_package();
    }
}


/*Nie jestem pewien czy nie napisałem tej funckji w nodes.cpp, dla Workera a nie dla fabryki*/
void Factory::do_work(Time t) {
    for (auto &worker: workers_) {
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
    std::for_each(ramps_.begin(), ramps_.end(), [&receiver](Ramp &ramp) {
        ramp.receiver_preferences_.remove_receiver(receiver);
    });

    std::for_each(workers_.begin(), workers_.end(), [&receiver](Worker &worker) {
        worker.receiver_preferences_.remove_receiver(receiver);
    });
}

//TODO
//Factory load_factory_structure(std::istream &is) {
//    return Factory();
//}

//TODO
//void save_factory_structure(Factory &factory, std::ostream &os) {
//
//}

ParsedLineData parse_line(std::string line) {
    ParsedLineData data;
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream token_stream(line);
    char delimiter = ' ';
    while (std::getline(token_stream, token, delimiter)) {
        tokens.push_back(token);
    }
    std::string r("LOADING_RAMP"), w("WORKER"), s("STOREHOUSE"), l("LINK"), c(";");
    if(tokens.front() == r){
        data.element_type_ = ElementType::LOADING_RAMP;
    }
    else if (tokens.front() == w){
        data.element_type_ = ElementType::WORKER;
    }
    else if (tokens.front() == s){
        data.element_type_ = ElementType::STOREHOUSE;
    }
    else if (tokens.front() == l){
        data.element_type_ = ElementType::LINK;
    }
    else if (tokens.front() != c){
        throw std::invalid_argument("Invalid element type");
    }
    for (auto it = std::next(tokens.begin()); it != tokens.end(); ++it) {
        std::vector<std::string> separated_keys_and_values;
        std::istringstream key_and_value(*it);
        char eq = '=';
        while (std::getline(key_and_value, token, eq)) {
            separated_keys_and_values.push_back(token);
        }
        if(separated_keys_and_values.size() != 2){
            throw std::invalid_argument("Too many \"=\" signs");
        }
        data.parameters_[separated_keys_and_values.front()] = separated_keys_and_values.back();
    }
    return data;
}
