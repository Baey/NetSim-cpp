//
// Created by Błażej Szargut on 14/12/2021.
//
#include "types.hpp"
#include "package.hpp"
#include "storage_types.hpp"
#include <iostream>
int main(){
    Package p1, p2, p3, p4;
    Package p5 = p1;
    std::cout << p1.get_id() << ' ' << p2.get_id() << ' ' << p3.get_id() << ' ' << p4.get_id() << ' ' << p5.get_id() <<std::endl;
    PackageQueue queue_1(LIFO);
    PackageQueue queue_2(FIFO);
    queue_1.push(p4);
    queue_1.push(p3);
    queue_1.push(p2);
    queue_1.push(p1);
    queue_1.pop();
    queue_2.push(p4);
    queue_2.push(p3);
    queue_2.push(p2);
    queue_2.push(p1);
    queue_2.pop();
    for(const auto & it : queue_1) {
        std::cout << it.get_id() << ' ';
    }
    for(const auto & it : queue_2) {
        std::cout << it.get_id() << ' ';
    }
    return 1;
}

