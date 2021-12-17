//
// Created by Błażej Szargut on 14/12/2021.
//

#ifndef NETSIM_CPP_STORAGE_TYPES_HPP
#define NETSIM_CPP_STORAGE_TYPES_HPP

#include <list>
#include <string>
#include <utility>

#include "types.hpp"
#include "package.hpp"

enum PackageQueueType {
    LIFO, FIFO
};

/* Uważam, że klasa PackageQueue powinna dziedziczyć po IPackageQueue, bo jest ona implementacją interfejsu
 * jakim do obsługi kolejki. */
class PackageQueue : IPackageQueue {
public:
    explicit PackageQueue(PackageQueueType package_queue_type) : package_queue_type_(std::move(queue_type)) {}

    /* Ma być dostosowanie tego typu metod w zależności od tego z jakim typem kolejki mamy do czynienia (LIFO/FIFO),
    * ale na ten moment nie wiem jak najsensowniej byłoby się tym zająć, więc implementuję tylko dla LIFO. */
    void push(const Package &package) { package_queue_.emplace_back(package); }

    const PackageQueue &const pop() { return package_queue_.pop_back(); }

    PackageQueueType string_queue() const { return package_queue_type_; }

private:
    std::list<Package> package_queue_;
    std::string package_queue_type_;
};

class IPackageStockpile {
public:
    /* Miał być alias const_iterator zdefiniowany w jako publiczny w tej klasie.
     * Nie wiem czy to powinno tak wyglądać no ale na razie tak zostawiam, bo wg Cliona inne klasy to widzą. */

    virtual ~IPackageStockpile() = default; // Defaultowy destruktor wirtualny

    void push();

    std::size_t size();

    bool empty();

    const_iterator begin();

    const_iterator end();

    const_iterator const cbegin();

    const_iterator const cend();

private:
};

/* Klasa IPackageQueue ma rozszerzać IPackageStockpile o metodę do usuwania elementu z kolejki i go zwracanie
 * oraz metodę służącą do określenia typu kolejki, dlatego uważam że IPackageQueue dziedziczy po IPackageStockpile */
class IPackageQueue : IPackageStockpile {
public:
    virtual Package pop() = 0;

private:

    virtual PackageQueueType get_queue_type() = 0;
};

#endif //NETSIM_CPP_STORAGE_TYPES_HPP
