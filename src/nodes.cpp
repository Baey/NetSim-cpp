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
}

void ReceiverPreferences::remove_receiver(IPackageReceiver *r) {
    /** Funkcja usuwająca odbiorcę z kontenera preferences_t_ i zmieniająca wrtości dystrybuanty
     * dla każdego pozostałego odbiorcy tak aby suma wynosiła 1 **/

    if (preferences_t_.size() != 0) {
        /* Być może powinno się to jakoś losować wszystko od nowa, albo redukować wartość dystrybuanty
         * dla każdego odbiorcy w kontenerze, ale doszedłem do wsniosku, że będzie łatwiej jeśli
         * dystrybuanta wcześniejszego odbiorcy w kontenerze po prostu osiągnie wartość tej dla usuwanego. */
        auto it = preferences_t_.find(r);
        --it -> second = preferences_t_[r];
        preferences_t_.erase(r);
    }
}

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

void PackageSender::send_package() {
    //TODO
}

void PackageSender::push_package(Package&& p) {
    /** Funkcja umieszczająca produkt w buforze **/
    if(not buffer_.has_value()) {
//    buffer_.emplace(p); <- nie wiem czemu to nie działa
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
