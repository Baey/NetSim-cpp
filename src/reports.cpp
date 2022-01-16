//
// Created by szmuksta on 11.01.2022.
//
#include <iostream>
#include "reports.hpp"

void generate_structure_report(const Factory& f, std::ostream& os) {
    os << "\n" << "== LOADING RAMPS ==" << "\n" <<"\n";
    std::for_each(f.ramp_cbegin(), f.ramp_cend(), [&](auto &ramp){
        os << "LOADING RAMP #" << ramp.get_id() << "\n" << "  Delivery interval: " << ramp.get_delivery_interval() << "\n";
        os << "  Receivers:" << "\n";
        for (auto &receiver_preferences : ramp.receiver_preferences_) {
            if (receiver_preferences.first->get_receiver_type() == WORKER) {
                os << "    worker #" << receiver_preferences.first->get_id() << "\n";
            }
            else {
                os << "    storehouse #" << receiver_preferences.first->get_id() << "\n";
            }
        }
        os << "\n";
    });
    os << "\n" << "== WORKERS ==" << "\n" << "\n";
    std::for_each(f.worker_cbegin(), f.worker_cend(), [&](auto &worker){
        os << "WORKER #" << worker.get_id() << "\n" << "  Processing time: " << worker.get_processing_duration() << "\n";
        os << "  Queue type: " ;
        if(worker.get_queue()->get_queue_type() == LIFO) {
            os << "LIFO" << "\n";
        }
        else {
            os << "FIFO" << "\n";
        }
        os << "  Receivers:" << "\n";
        for (auto &receiver_preferences : worker.receiver_preferences_) {
            if (receiver_preferences.first->get_receiver_type() == WORKER) {
                os << "    worker #" << receiver_preferences.first->get_id() << "\n";
            }
            else {
                os << "    storehouse #" << receiver_preferences.first->get_id() << "\n";
            }
        }
        os << "\n";
    });
    os << "\n" << "== STOREHOUSES ==" << "\n" << "\n";
    std::for_each(f.storehouse_cbegin(), f.storehouse_cend(), [&](auto &store){
        os << "STOREHOUSE #" << store.get_id() << "\n" << "\n";

    });
}

void generate_simulation_turn_report(const Factory& f, std::ostream& os, Time t) {
    t = t + 1;
    f.worker_cbegin();
    os << "Dupa";
    /*os << "=== [ Turn: # ] ===" << "\n";
    os << "" << "\n";
    os << "== WORKERS ==" << "\n";
    os << "" << "\n";
    std::for_each(f.worker_cbegin(), f.worker_cend(), [&](auto &worker){
        os << "WORKER #" << worker.get_id() << "\n" << "  PBuffer: #" << worker. << "\n" << "  Queue: #" << worker. << "\n" << "  SBuffer: #" << worker. << "\n";*/
}