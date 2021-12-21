//
// Created by Błażej Szargut on 14/12/2021.
//

#include "types.hpp"
#include "package.hpp"
#include "storage_types.hpp"

Package PackageQueue::pop() {
    if (!package_queue_.empty()) {
        /* To jest FIFO - różnica jest tylko dla metody pop! */
        if (package_queue_type_ == PackageQueueType::FIFO) {
            Package package = package_queue_.front();
            package_queue_.erase(package_queue_.begin());
            return package;
        }
            /* To jest LIFO - różnica jest tylko dla metody pop! */
        else {
            Package package = package_queue_.back();
            package_queue_.erase(package_queue_.end());
            return package;
        }
    }
    else return Package(0);
}

