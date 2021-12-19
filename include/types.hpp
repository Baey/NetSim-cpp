//
// Created by Błażej Szargut on 14/12/2021.
//

#ifndef NETSIM_CPP_TYPES_HPP
#define NETSIM_CPP_TYPES_HPP
#include <list>
#include "package.hpp"

/* Alias na unsigned int. Można pomyśleć czy zamiast u int nie dać size_t, chociaż obydwa typy
 * chyba są dokładnie tym samym, więc pewnie nie będzie róźnicy. W ogóle, czy size_t to nie
 * alias na unsigned int??? */
using ElementID = unsigned int;
using const_iterator = std::list<Package>::const_iterator; // Mój Clion nie widzi Package i nie wiem czemu ;(

#endif //NETSIM_CPP_TYPES_HPP
