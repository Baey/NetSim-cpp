//
// Created by szmuksta on 11.01.2022.
//

#ifndef NETSIM_REPORTS_HPP
#define NETSIM_REPORTS_HPP

#include <iostream>
#include "types.hpp"
#include "storage_types.hpp"
#include "nodes.hpp"
#include "factory.hpp"

void generate_structure_report(const Factory& worker, std::ostream& os);

void generate_simulation_turn_report(const Factory& f, std::ostream& os, Time t);

std::vector<std::pair<IPackageReceiver *, double>> sort_map(const ReceiverPreferences& receiver_preferences);

class SpecificTurnsReportNotifier {
public:
    SpecificTurnsReportNotifier(std::set<Time> turns) : turns_(turns) {}

    bool should_generate(Time t) { return turns_.find(t) != turns_.end(); }

private:
    std::set<Time> turns_;
};

class IntervalReportNotifier {
public:
    IntervalReportNotifier(TimeOffset to) : to_(to) {}

    bool should_generate(Time t) { return t % to_ == 1; }

private:
    TimeOffset to_;
};
#endif //NETSIM_REPORTS_HPP
