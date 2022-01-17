//
// Created by szmuksta on 11.01.2022.
//
#include <iostream>
#include "reports.hpp"

void generate_structure_report(const Factory &f, std::ostream &os) {
    os << "\n" << "== LOADING RAMPS ==" << "\n" << "\n";
    std::for_each(f.ramp_cbegin(), f.ramp_cend(), [&](auto &ramp) {
        os << "LOADING RAMP #" << ramp.get_id() << "\n" << "  Delivery interval: " << ramp.get_delivery_interval()
           << "\n";
        os << "  Receivers:" << "\n";
        for (auto &receiver_preferences: ramp.receiver_preferences_) {
            if (receiver_preferences.first->get_receiver_type() == WORKER) {
                os << "    worker #" << receiver_preferences.first->get_id() << "\n";
            } else {
                os << "    storehouse #" << receiver_preferences.first->get_id() << "\n";
            }
        }
        os << "\n";
    });
    os << "\n" << "== WORKERS ==" << "\n" << "\n";
    std::for_each(f.worker_cbegin(), f.worker_cend(), [&](auto &worker) {
        os << "WORKER #" << worker.get_id() << "\n" << "  Processing time: " << worker.get_processing_duration()
           << "\n";
        os << "  Queue type: ";
        if (worker.get_queue()->get_queue_type() == LIFO) {
            os << "LIFO" << "\n";
        } else {
            os << "FIFO" << "\n";
        }
        os << "  Receivers:" << "\n";
        auto sorted_receivers = sort_map(worker.receiver_preferences_);
        for (auto &receiver_preferences: worker.receiver_preferences_) {
            if (receiver_preferences.first->get_receiver_type() == WORKER) {
                os << "    worker #" << receiver_preferences.first->get_id() << "\n";
            } else {
                os << "    storehouse #" << receiver_preferences.first->get_id() << "\n";
            }
        }
        os << "\n";
    });
    os << "\n" << "== STOREHOUSES ==" << "\n" << "\n";
    std::for_each(f.storehouse_cbegin(), f.storehouse_cend(), [&](auto &store) {
        os << "STOREHOUSE #" << store.get_id() << "\n" << "\n";

    });
}

void generate_simulation_turn_report(const Factory &f, std::ostream &os, Time t) {
    f.find_worker_by_id(1);
    os << ' ';
    t += 1;
//    os << "=== [ Turn: " << std::to_string(t) << " ] ===" << "\n" << "\n";
//    os << "== WORKERS ==" << "\n";
//    os << "" << "\n";
//    std::for_each(f.worker_cbegin(), f.worker_cend(), [&](auto &worker) {
//        os << "WORKER #" << worker.get_id() << "\n" << "  PBuffer: #" << worker.get_processing_buffer() << " (pt = "
//           << worker.get_processing_duration() << ")" << "\n";
//        if (worker.get_queue()->empty()) {
//            os << "  Queue: (empty)\n";
//        } else {
//            os << "  Queue:";
//            for (auto j = worker.get_queue()->cbegin(); j != worker.get_queue()->cend(); j++) {
//                if (j == worker.get_queue()->cbegin()) {
//                    os << " #" << j->get_id();
//                } else {
//                    os << ", #" << j->get_id();
//                }
//            }
//            os << "\n";
//
//            if (bool(worker.get_queue()->get_sending_buffer())) {
//                os << "  SBuffer: #" << worker.get_queue()->get_sending_buffer()->get_id() << "\n";
//            } else {
//                os << "  SBuffer: (empty)\n";
//            }
//        }
//    });
}

std::vector<std::pair<IPackageReceiver *, double>> sort_map(const ReceiverPreferences& receiver_preferences) {
    typedef std::pair<IPackageReceiver *, double> pair;
    std::vector<pair> sorted_receivers;
    std::copy(receiver_preferences.begin(),
              receiver_preferences.end(),
              std::back_inserter<std::vector<pair>>(sorted_receivers));

    std::sort(sorted_receivers.begin(), sorted_receivers.end(),
              [](const pair &l, const pair &r)
              {
                  return l.first->get_id() < r.first->get_id();
              });
    std::sort(sorted_receivers.begin(), sorted_receivers.end(),
              [](const pair &l, const pair &r)
              {
                  return l.first->get_receiver_type() < r.first->get_receiver_type();
              });
    return sorted_receivers;
}
