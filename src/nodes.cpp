//
// Created by szczy on 04.01.2022.
//

#include "nodes.hpp"

Worker::Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q) : PackageSender() {
    id_ = id;
    pd_ = pd;
    q_ = std::move(q);
}

void ReceiverPreferences::add_receiver(IPackageReceiver *r) {
    /** Funkcja dodająca odbiorcę do kontenera preferences_t_ i zmieniająca wrtości prawdopodobieństwa
     * dla każdego odbiorcy tak aby suma wynosiła 1 **/
    preferences_t_.insert({r, 1});
    for (auto[receiver, p]: preferences_t_) {
        preferences_t_[receiver] = 1 / static_cast<double>(preferences_t_.size());
    }
}

void ReceiverPreferences::remove_receiver(IPackageReceiver *r) {
    /** Funkcja usuwająca odbiorcę z kontenera preferences_t_ i zmieniająca wrtości dystrybuanty
    * dla każdego pozostałego odbiorcy tak aby suma wynosiła 1 **/
    if (preferences_t_.size() != 0) {
        preferences_t_.erase(r);
        for (auto[receiver, p]: preferences_t_) {
            preferences_t_[receiver] = 1 / static_cast<double>(preferences_t_.size());
        }
    }
}

IPackageReceiver *ReceiverPreferences::choose_receiver() {
    /** Funkcja losująca wartość prawdopodobieństwa a następnie sprawdzająca, który z odbiorców w kontenerze
     * ma wartość dystrybuanty >= wylosowanemu prawdopodobieństwu **/
    double dist = pg_();
    double current_dist = 0;
    for (auto[receiver, p]: preferences_t_) {
        current_dist += p;
        if (current_dist >= dist) return receiver;
    }
    return nullptr;
}

void PackageSender::send_package() {
    if (buffer_) {
        receiver_preferences_.choose_receiver()->receive_package(std::move(buffer_.value()));
        buffer_.reset();
    }
}


void PackageSender::push_package(Package &&p) {
    /** Funkcja umieszczająca produkt w buforze **/
    if (not buffer_.has_value()) {
        buffer_ = std::move(p);
    }
}

void Ramp::deliver_goods(Time t) {
    /** Funkcja przekazująca produkt gdy jest gotowy i tworząca nowy**/
    if (t % di_ == 1) {
        push_package(Package());
    }
}

void Worker::do_work(Time t) {
    if (!processing_buffer_.has_value() && !q_->empty()) {
        processing_buffer_ = q_->pop();
        start_time_ = t;
    }
    if (t - start_time_ + 1 == pd_) {
        push_package(std::move(processing_buffer_.value()));
        processing_buffer_.reset();
    }
}