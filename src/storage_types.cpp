//
// Created by Błażej Szargut on 14/12/2021.
//
#include <list>
#include <storage_types.hpp>

/* Nie wiem co mu nie pasuje w typach w poniższych implementacjach */

const Package PackageQueue::pop() {
    if (package_queue_type_ == LIFO) {
        return package_queue_.pop_back();
    } else {
        return package_queue_.pop_front();
    }
}
/*Jak coś to jest inna implementacja LIFO i FIFO. Napisałem o tym trochę w storage_types.hpp . Jak się wam to spodoba
 * i ktoś potwieedzi, że to jest git to wystarczy to odkomentować*/


/*const Package PackageQueue::pop() {
    if(empty())
        throw std::runtime_error("Pile is empty!");

    int index = 0;
    // FIFO
    if(type == PackageQueueType::FIFO)
        index = 0;
        // LIFO
    else
        index = pile.size() - 1;

    Package p = pile[index];
    pile.erase(pile.begin() + index);

    return p;
}*/

void PackageQueue::push(const Package &package) {
    if (package_queue_type_ == LIFO) {
        package_queue_.emplace_back(package);
    } else {
        package_queue_.insert(package_queue_.front(), package);
    }
}

