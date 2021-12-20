//
// Created by Błażej Szargut on 14/12/2021.
//

#include "types.hpp"
#include "package.hpp"
#include "storage_types.hpp"


/* Nie wiem co mu nie pasuje w typach w poniższych implementacjach */

//const Package PackageQueue::pop() {
//    if (package_queue_type_ == LIFO) {
//        return package_queue_.pop_back();
//    } else {
//        return package_queue_.pop_front();
//    }
//}
/*Jak coś to jest inna implementacja LIFO i FIFO. Napisałem o tym trochę w storage_types.hpp . Jak się wam to spodoba
 * i ktoś potwieedzi że to jest dobrze to wystarczy to odkomentowac plus pliki w storage_types.hpp*/

Package PackageQueue::pop() {
    /* To jest FIFO - różnica jest tylko dla metody pop! */
    if (package_queue_type_ == PackageQueueType::FIFO) {
        Package package = package_queue_.front();
        package_queue_.erase(package_queue_.begin());
        return package;
    }
        /* To jest LIFO - różnica jest tylko dla metody pop! */
    else if (package_queue_type_ == PackageQueueType::LIFO) {
        Package package = package_queue_.back();
        package_queue_.erase(package_queue_.end());
        return package;
    }
}

//void PackageQueue::push(const Package &package) {
//    if (package_queue_type_ == LIFO) {
//        package_queue_.emplace_back(package);
//    } else {
//        package_queue_.insert(package_queue_.front(), package);
//    }
//}

