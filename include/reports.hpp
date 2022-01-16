//
// Created by szmuksta on 11.01.2022.
//

#ifndef NETSIM_REPORTS_HPP
#define NETSIM_REPORTS_HPP

#include "types.hpp"
#include "storage_types.hpp"
#include "nodes.hpp"
#include "factory.hpp"
#include <iostream>

void generate_structure_report(const Factory& worker, std::ostream& os);

void generate_simulation_turn_report(const Factory& f, std::ostream& os, Time t);

#endif //NETSIM_REPORTS_HPP
