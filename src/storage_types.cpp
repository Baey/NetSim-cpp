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

void PackageQueue::push(const Package &package) {
    if (package_queue_type_ == LIFO) {
        package_queue_.emplace_back(package);
    } else {
        package_queue_.insert(package_queue_.front(), package);
    }
}

