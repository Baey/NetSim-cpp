//
// Created by Błażej Szargut on 14/12/2021.
//

#ifndef NETSIM_CPP_STORAGE_TYPES_HPP
#define NETSIM_CPP_STORAGE_TYPES_HPP

#include <list>
#include <string>
#include <utility>
#include <vector>

#include "types.hpp"
#include "package.hpp"

enum PackageQueueType {
    LIFO,
    FIFO
};


class IPackageStockpile {

public:

    using const_iterator = std::list<Package>::const_iterator;

    void push(Package &package) { package_queue_.push_back(package); }

    bool empty() { return package_queue_.empty(); }

    std::size_t size() { return package_queue_.size(); }

    const_iterator begin() { return package_queue_.begin(); }

    const_iterator end() { return package_queue_.end(); }

    const_iterator cbegin() const { return package_queue_.cbegin(); }

    const_iterator cend() const { return package_queue_.cend(); }

    virtual ~IPackageStockpile() = default;

protected:

    std::list<Package> package_queue_;
};

/* Klasa IPackageQueue ma rozszerzać IPackageStockpile o metodę do usuwania elementu z kolejki i go zwracanie
 * oraz metodę służącą do określenia typu kolejki, dlatego uważam że IPackageQueue dziedziczy po IPackageStockpile */
class IPackageQueue : public IPackageStockpile {

public:

    Package pop();

    PackageQueueType get_queue_type() { return package_queue_type_; }

protected:

    PackageQueueType package_queue_type_;
};


/* Uważam, że klasa PackageQueue powinna dziedziczyć po IPackageQueue, bo jest ona implementacją interfejsu
 * jakim do obsługi kolejki. */
class PackageQueue : IPackageQueue {
public:

    //explicit PackageQueue(PackageQueueType package_queue_type) : package_queue_type_(package_queue_type) {}

    explicit PackageQueue(PackageQueueType type) { package_queue_type_ = type; }

    //void push(const Package &package);

    // PackageQueueType package_queue_type() const { return package_queue_type_; }
};

#endif //NETSIM_CPP_STORAGE_TYPES_HPP
