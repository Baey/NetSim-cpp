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

    if (preferences_t_.size() == 0) {
        preferences_t_[r] = 1;
    }
    else {
        preferences_t_[r] = pg_() + 1;
        for (auto [receiver, p] : preferences_t_) {
            p = p/preferences_t_[r];
        }
    }
    /*Moim zdaniem powinno być to zrobione tak ale nie mam pewności. Jak ktoś potwierdzi tą wersję to proszę odkomentujcie.*/
/*    else {
        preferences_t_[r] = pg_();
        double sum_pf_ps = 0;
        for (auto [receiver, p] : preferences_t_) {
            sum_pf_ps += p;
        }
        for (auto [receiver, p] : preferences_t_) {
            p = p/sum_pf_ps;
        }
    }
}*/
}

void ReceiverPreferences::remove_receiver(IPackageReceiver *r) {
    //* Funkcja usuwająca odbiorcę z kontenera preferences_t_ i zmieniająca wrtości dystrybuanty
    //* dla każdego pozostałego odbiorcy tak aby suma wynosiła 1 *

    if (preferences_t_.size() != 0) {
         /*Być może powinno się to jakoś losować wszystko od nowa, albo redukować wartość dystrybuanty
         * dla każdego odbiorcy w kontenerze, ale doszedłem do wsniosku, że będzie łatwiej jeśli
         * dystrybuanta wcześniejszego odbiorcy w kontenerze po prostu osiągnie wartość tej dla usuwanego.*/
        auto it = preferences_t_.find(r);
        --it -> second = preferences_t_[r];
        preferences_t_.erase(r);
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
    for (auto [receiver, p] : preferences_t_) {
        if (p >= dist) return receiver;
    }
    return nullptr;
}

std::optional<Package> &PackageSender::get_sending_buffer() {
    /** Funkcja zwracająca zawartość buforu kiedy ten nie jest pusty, w przeciwnym przypadku zwraca nullptr **/
    return buffer_;
}

/*Myślę że ta funckja ma sporo sensu ale nie wiem czemu się wypieprza*/
void PackageSender::send_package() {
    if(buffer_){
        receiver_preferences_.choose_receiver()->receive_package(buffer_->get_id());
    }
}


void PackageSender::push_package(Package&& p) {
    /** Funkcja umieszczająca produkt w buforze **/
    if(not buffer_.has_value()) {
        buffer_.emplace(p); //<- nie wiem czemu to nie działa
    }
}

void Ramp::deliver_goods(Time t) {
    /** Funkcja przekazująca produkt gdy jest gotowy i tworząca nowy**/
    if(t % di_ == 0){
        push_package(Package(id_));
        Package new_package;
        id_ = new_package.get_id();
    }
}

/*Jak coś ta funckja działa dla 2 klasy Worker, którą napisałem w nodes.hpp, tylko jest w tym momencie zakomentowana*/

void Worker::receive_package(Package&& p) {
    PackageSender::push_package(std::move(p));
}


/*Napisałem też taką funckję ale nie rozumiem co za bardzo się nie podoba kompilatorowi w tym momencie
 * Funckje do_work będzie pogram widział gdy odkomentujemy */
void Worker::do_work(Time t) {
    if (t == 1) {
        receive_package(id_);
    }
    if (t%pd_ == 0) {
        send_package();
        receive_package(id_);
    }
}