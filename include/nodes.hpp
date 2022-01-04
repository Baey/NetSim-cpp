//
// Created by szczy on 04.01.2022.
//

#ifndef NETSIM_NODES_HPP
#define NETSIM_NODES_HPP

class ReceiverPreferences {

};

class IPackageReceiver {
public:

    using const_iterator = std::list<Package>::const_iterator;

    using preferences_t = std::map<IPackageReceiver*, double>;

    using const_iterator = preferences_t::const_iterator;

    const_iterator begin() { return package_queue_.begin(); }

    const_iterator end() { return package_queue_.end(); }

    const_iterator cbegin() const { return package_queue_.cbegin(); }

    const_iterator cend() const { return package_queue_.cend(); }

    get_preferences()

    virtual ~IPackageReceiver() = default;

protected:

    std::list<Package> package_queue_;
};

class Storehouse {
    std::unique_ptr<IPackageStockpile>
};

class PackageSender {
public:

    PackageSender(PackageSender&&)
};

class Ramp {
public:
    deliver_goods(t: Time)
};

class Worker {

};

#endif //NETSIM_NODES_HPP
