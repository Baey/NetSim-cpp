//
// Created by Błażej Szargut on 14/12/2021.
//

#ifndef NETSIM_CPP_STORAGE_TYPES_HPP
#define NETSIM_CPP_STORAGE_TYPES_HPP

#include <list>
#include <string>

#include "types.hpp"
#include "package.hpp"

/* Uważam, że klasa PackageQueue powinna dziedziczyć po IPackageQueue, bo jest ona implementacją interfejsu
 * jakim do obsługi kolejki. */
class PackageQueue : IPackageQueue {
public:
    /* Ma być dostosowanie tego typu metod w zależności od tego z jakim typem kolejki mamy do czynienia (LIFO/FIFO),
    * ale na ten moment nie wiem jak najsensowniej byłoby się tym zająć, więc implementuję tylko dla LIFO. */
    void push(const Package product) { queue_.emplace_back(product); }

    const PackageQueue &const pop() { return queue_.pop_back(); }

private:
    std::list<Package> queue_;
};

class IPackageStockpile {
public:
    /* Miał być alias const_iterator zdefiniowany w jako publiczny w tej klasie.
     * Nie wiem czy to powinno tak wyglądać no ale na razie tak zostawiam, bo wg Cliona inne klasy to widzą. */
    using const_iterator = std::list<Package>::const_iterator;

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
    virtual Package pop();

    /* Nie wiem za bardzo na ten moment jakiego typu ma zwracać wynik funkcja określająca typ kolejki.
     * Coś tam w instrukcji było o parsowaniu pliku ze schematem fabryki i określania typu na podstawie
     * np. ciągu znaków "LIFO", więc ustawiam na razie na string. */
    std::string queue_type();
};

#endif //NETSIM_CPP_STORAGE_TYPES_HPP
