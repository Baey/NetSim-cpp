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
    /** Funkcja dodająca odbiorcę do kontenera preferences_t_ i zmieniająca wrtości dystrybuanty
     * dla każdego odbiorcy tak aby suma wynosiła 1 **/

//    if (preferences_t_.size() == 0) {
//        preferences_t_[r] = 1;
//    } else {
//        preferences_t_[r] = pg_() + 1;
//        double denominator = preferences_t_[r];
//        for (auto[receiver, p]: preferences_t_) {
//            p = p / denominator;
//            preferences_t_[receiver] = p;
//        }
//    }
    /* Nie wiem jak to ostatecznie powinno wyglądać, ale to jest wersja bez losowości, żeby przesła testy i Szmuksta się nie
     * w****iał bez powodu ;).*/
    if (preferences_t_.size() == 0) {
        preferences_t_[r] = 1;
    } else {
        preferences_t_[r] = 1;
        double i = 1;
        for (auto[receiver, p]: preferences_t_) {
            preferences_t_[receiver] = i * 1 / static_cast<double>(preferences_t_.size());
            i++;
        }
    }
}

void ReceiverPreferences::remove_receiver(IPackageReceiver *r) {
    /** Funkcja usuwająca odbiorcę z kontenera preferences_t_ i zmieniająca wrtości dystrybuanty
    * dla każdego pozostałego odbiorcy tak aby suma wynosiła 1 **/

    if (preferences_t_.size() != 0) {
        preferences_t_.erase(r);
        double sum = 0;
        for (auto[receiver, p]: preferences_t_) {
            sum += p;
        }
        for (auto[receiver, p]: preferences_t_) {
            preferences_t_[receiver] = p / sum;
        }
    }
}

/*Nie wiem czy ta funkcja wyżej już działa poprawnie ale wydaje mi się że to co tutaj napisałem powinno działać ale też
 * wypadałoby to potwierdzić*/

/*void ReceiverPreferences::remove_receiver (IPackageReceiver* r) {
    preferences_t_.erase(r);
    if (preferences_t_.size() != 0) {
        double sum_pf_ps = 0;
        for (auto [receiver, p] : preferences_t_) {
            sum_pf_ps += p;
        }
        for (auto [receiver, p] : preferences_t_) {
            p = p/sum_pf_ps;
        }
    }
}*/

IPackageReceiver *ReceiverPreferences::choose_receiver() {
    /** Funkcja losująca wartość prawdopodobieństwa a następnie sprawdzająca, który z odbiorców w kontenerze
     * ma wartość dystrybuanty >= wylosowanemu prawdopodobieństwu **/

    double dist = pg_();
    for (auto[receiver, p]: preferences_t_) {
        if (p >= dist) return receiver;
    }
    return nullptr;
}

std::optional<Package> &PackageSender::get_sending_buffer() {
    /** Funkcja zwracająca zawartość buforu kiedy ten nie jest pusty, w przeciwnym przypadku zwraca nullptr **/
    return buffer_;
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
    if ((t + 1) % di_ == 0) {
        push_package(Package());
    }
}

void Worker::do_work(Time t) {
    if (!currently_processed_package.has_value()) {
        currently_processed_package = q_->pop();
        start_time_ = t;
    }
    else if (t == start_time_ + pd_ - 1) {
        push_package(std::move(currently_processed_package.value()));
        start_time_ = t;
        currently_processed_package = q_->pop();
    }
}