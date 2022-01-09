//
// Created by szczy on 04.01.2022.
//

#ifndef NETSIM_NODES_HPP
#define NETSIM_NODES_HPP

#include <list>
#include <map>
#include <memory>
#include <optional>
#include <utility>
#include "types.hpp"
#include "package.hpp"
#include "storage_types.hpp"
#include "helpers.hpp"

enum ReceiverType {
    Worker,
    Storehouse,
    Ramp
};

class IPackageReceiver {
public:

    virtual IPackageStockpile::const_iterator begin() = 0;

    virtual IPackageStockpile::const_iterator end() = 0;

    virtual IPackageStockpile::const_iterator cbegin() const = 0;

    virtual IPackageStockpile::const_iterator cend() const = 0;

    virtual void receive_package(Package&& p) = 0;

    virtual ElementID get_receiver_id() const = 0;

    virtual ReceiverType get_receiver_type() const = 0;

    virtual ~IPackageReceiver() = default;

protected:

    std::list<Package> package_queue_;
};

class Storehouse : IPackageReceiver, IPackageStockpile {
public:
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d) : id_(id) { d_ = std::move(d); }

    ElementID get_receiver_id() const { return id_; }

    ReceiverType get_receiver_type() const {return ReceiverType::Storehouse; }

    void receive_package(Package&& p) { d_->push(p); }

private:
    ElementID id_;

    std::unique_ptr<IPackageStockpile> d_;

};

class ReceiverPreferences {
public:
    using preferences_t = std::map<IPackageReceiver *, double>;

    using const_iterator = preferences_t::const_iterator;

    using ProbabilityGenerator = std::function<double()>;

    ReceiverPreferences(ProbabilityGenerator pg = default_probability_generator) : pg_(std::move(pg)) {}

    void add_receiver(IPackageReceiver *r);

    void remove_receiver(IPackageReceiver *r);

    IPackageReceiver *choose_receiver();

    preferences_t& get_preferences() {return preferences_t_; }

    const_iterator begin() { return preferences_t_.begin(); }

    const_iterator end() { return preferences_t_.end(); }

    const_iterator cbegin() const { return preferences_t_.cbegin(); }

    const_iterator cend() const { return preferences_t_.cend(); }

protected:
    ProbabilityGenerator pg_;

    preferences_t preferences_t_;
};

class PackageSender {
public:
    PackageSender() = default;

    PackageSender(PackageSender &&) = default;

    void send_package();

    void push_package(Package&& p);

    std::optional<Package> &get_sending_buffer();

protected:
    ReceiverPreferences receiver_preferences_;

    std::optional<Package> buffer_ = std::nullopt;
};

class Ramp : PackageSender {
public:
    Ramp(ElementID id, TimeOffset di) : PackageSender(), id_(id), di_(di) {}

    void deliver_goods(Time t);

    TimeOffset get_deliver_interval() const { return di_; }

    ElementID get_id() const { return id_; }

    ReceiverType get_receiver_type() const {return ReceiverType::Ramp; }

    std::optional<Package> &get_sending_buffer();

    ElementID id_;

    TimeOffset di_;
};

class Worker : public PackageSender, IPackageReceiver, IPackageQueue {
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q);

    ReceiverType get_receiver_type() const {return ReceiverType::Worker; }

    ElementID get_receiver_id() const { return id_; }

    void receive_package(Package&& p) { q_->push(p); }

    void do_work(Time t);

    TimeOffset get_processing_duration() const { return pd_; }

    Time get_package_processing_start_time() const { return start_time_; }

private:
    ElementID id_;

    TimeOffset pd_;

    Time start_time_;

    std::unique_ptr<IPackageQueue> q_;

    Package currently_processed_package;

};

//Nie podoba mi sie coś w tamtej klasie Worker i myślę że powinna wyglądać o tak jak poniżej.
// Dla poniższej funkcji napisałem też w nodes.cpp funckję receive_package, ale jest zakomentowana
//ponieważ dla powyższego workera poprostu się wywala

//class Worker : public IPackageReceiver, public PackageSender {
//public:
//    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q);
//    ElementID get_id() const override {return id_;};
//    ReceiverType get_receiver_type() const override {return ReceiverType::Worker; }
//    void do_work(Time t);
//    void receive_package(Package&& p) override;
//    TimeOffset get_processing_duration() {return pd_;};
//    Time get_package_processing_start_time() ; //TODO
//
//private:
//    ElementID id_;
//    TimeOffset pd_;
//    std::unique_ptr<IPackageQueue> q_;
//    ReceiverType receiver_type_;
//};


#endif //NETSIM_NODES_HPP
