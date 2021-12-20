//
// Created by Błażej Szargut on 14/12/2021.
//

#ifndef NETSIM_CPP_STORAGE_TYPES_HPP
#define NETSIM_CPP_STORAGE_TYPES_HPP

#include "package.hpp"
#include "types.hpp"

#include <list>

enum PackageQueueType {
    LIFO,
    FIFO
};

class IPackageStockpile {
    /*Okej starałem się ogarnąć to LIFO i FIFO, ale nie wiem czy ma to sens więc fajnie jakby to
     * zostało sprawdzone przez kogoś bardziej kompetentego odemnie bo jednak jest to kod, który dostałem od kogoś.
     * generalnie aby to działało to trzeba stworzyć (przynajmniej ja to tak rozumiem) vector, kóry będzie stosem.
     * Sam nie do końca wiem jak to działa, a implementacja jest dalsza w pliku storage_types.cpp  . Tam też kod jest
     * zakomentowany i jak ktoś z was to potwierdzi to wtedy można to odkomentwoać*/

public:
    /* Miał być alias const_iterator zdefiniowany w jako publiczny w tej klasie.
     * Nie wiem czy to powinno tak wyglądać no ale na razie tak zostawiam, bo wg Cliona inne klasy to widzą. */

    void push(Package &package) { package_queue_.push_back(package); }

    bool empty() { return package_queue_.empty(); }

    std::size_t size() { return package_queue_.size(); }

    const_iterator begin() { return package_queue_.begin(); }

    const_iterator end() { return package_queue_.end(); }

    const_iterator cbegin() const { return package_queue_.cbegin(); }

    const_iterator cend() const { return package_queue_.cend(); }

    virtual ~IPackageStockpile() = default; // Defaultowy destruktor wirtualny

protected:

    std::list<Package> package_queue_;
};

/* Klasa IPackageQueue ma rozszerzać IPackageStockpile o metodę do usuwania elementu z kolejki i go zwracanie
 * oraz metodę służącą do określenia typu kolejki, dlatego uważam że IPackageQueue dziedziczy po IPackageStockpile */
class IPackageQueue : public IPackageStockpile {

public:

    virtual Package pop() = 0;

    PackageQueueType get_queue_type() { return package_queue_type_; }

protected:

    PackageQueueType package_queue_type_;
};


/* Uważam, że klasa PackageQueue powinna dziedziczyć po IPackageQueue, bo jest ona implementacją interfejsu
 * jakim do obsługi kolejki. */
class PackageQueue : IPackageQueue {
public:

    //explicit PackageQueue(PackageQueueType package_queue_type) : package_queue_type_(package_queue_type) {}

    PackageQueue(PackageQueueType type) { package_queue_type_ = type; }

    /* Ma być dostosowanie tego typu metod w zależności od tego z jakim typem kolejki mamy do czynienia (LIFO/FIFO),
    * ale na ten moment nie wiem jak najsensowniej byłoby się tym zająć, więc implementuję tylko dla LIFO. */

    //void push(const Package &package);

    Package pop();

    // PackageQueueType package_queue_type() const { return package_queue_type_; }
};

#endif //NETSIM_CPP_STORAGE_TYPES_HPP
