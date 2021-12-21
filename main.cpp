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
    std::cout << p1.get_id() << ' ' << p2.get_id() << ' ' << p3.get_id() << ' ' << p4.get_id() << ' ' << p5.get_id();
    PackageQueue q(LIFO);
//    q.push(p1);
}

