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

    virtual void push(Package &&package) = 0;

    virtual bool empty() = 0;

    virtual std::size_t size() = 0;

    virtual const_iterator begin() = 0;

    virtual const_iterator end() = 0;

    virtual const_iterator cbegin() const = 0;

    virtual const_iterator cend() const = 0;

    virtual ~IPackageStockpile() = default;

};

/* Klasa IPackageQueue ma rozszerzać IPackageStockpile o metodę do usuwania elementu z kolejki i go zwracanie
 * oraz metodę służącą do określenia typu kolejki, dlatego uważam że IPackageQueue dziedziczy po IPackageStockpile */
class IPackageQueue : public IPackageStockpile {

public:

    virtual Package pop() = 0;

    virtual PackageQueueType get_queue_type() = 0;

};


/* Uważam, że klasa PackageQueue powinna dziedziczyć po IPackageQueue, bo jest ona implementacją interfejsu
 * jakim do obsługi kolejki. */
class PackageQueue : public IPackageQueue {
public:

    explicit PackageQueue(PackageQueueType package_queue_type) : package_queue_type_(package_queue_type) {}

    Package pop() override;

    PackageQueueType get_queue_type() override { return package_queue_type_; }

    void push(Package &&package) override { package_queue_.push_back(std::move(package)); }

    bool empty() override { return package_queue_.empty(); }

    std::size_t size() override { return package_queue_.size(); }

    const_iterator begin() override { return package_queue_.begin(); }

    const_iterator end() override { return package_queue_.end(); }

    const_iterator cbegin() const override { return package_queue_.cbegin(); }

    const_iterator cend() const override { return package_queue_.cend(); }

private:

    std::list<Package> package_queue_;

    PackageQueueType package_queue_type_;
};

#endif //NETSIM_CPP_STORAGE_TYPES_HPP
