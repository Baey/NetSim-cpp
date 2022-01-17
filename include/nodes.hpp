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
#include "storage_types.hpp"
#include "helpers.hpp"
#include "config.hpp"

enum ElementType {
    LOADING_RAMP,
    STOREHOUSE,
    WORKER,
    LINK
};

class IPackageReceiver {
public:

    virtual IPackageStockpile::const_iterator begin() const = 0;

    virtual IPackageStockpile::const_iterator end() const = 0;

    virtual IPackageStockpile::const_iterator cbegin() const = 0;

    virtual IPackageStockpile::const_iterator cend() const = 0;

    virtual void receive_package(Package &&p) = 0;

    virtual ElementID get_id() const = 0;

    virtual ElementType get_receiver_type() const = 0;

    virtual ~IPackageReceiver() = default;
};

class Storehouse : public IPackageReceiver {
public:
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d = std::make_unique<PackageQueue>(PackageQueue(LIFO))) : id_(id) { d_ = std::move(d); }

    ElementID get_id() const override { return id_; }

    ElementType get_receiver_type() const override { return ElementType::STOREHOUSE; }

    void receive_package(Package &&p) override { d_->push(std::move(p)); }

    IPackageStockpile::const_iterator begin() const override { return d_->begin(); }

    IPackageStockpile::const_iterator end() const override { return d_->end(); }

    IPackageStockpile::const_iterator cbegin() const override { return d_->cbegin(); }

    IPackageStockpile::const_iterator cend() const override { return d_->cend(); }

private:
    ElementID id_;

    std::unique_ptr<IPackageStockpile> d_;

};

class ReceiverPreferences {
public:
    using preferences_t = std::map<IPackageReceiver *, double>;

    using const_iterator = preferences_t::const_iterator;

    using ProbabilityGenerator = std::function<double()>;

    explicit ReceiverPreferences(ProbabilityGenerator pg = probability_generator) : pg_(std::move(pg)) {}

    void add_receiver(IPackageReceiver *r);

    void remove_receiver(IPackageReceiver *r);

    IPackageReceiver *choose_receiver();

    const preferences_t &get_preferences() const { return preferences_t_; }

    const_iterator begin() const { return preferences_t_.begin(); }

    const_iterator end() const { return preferences_t_.end(); }

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

    void push_package(Package &&p);

    std::optional<Package> const &get_sending_buffer() const { return buffer_; }

    ReceiverPreferences receiver_preferences_;

protected:

    std::optional<Package> buffer_ = std::nullopt;
};

class Ramp : public PackageSender {
public:
    Ramp(ElementID id, TimeOffset di) : PackageSender(), id_(id), di_(di) {}

    void deliver_goods(Time t);

    TimeOffset get_delivery_interval() const { return di_; }

    ElementID get_id() const { return id_; }

//    ElementType get_receiver_type() const {return ElementType::Ramp; }

//    std::optional<Package> &get_sending_buffer();

    ElementID id_;

    TimeOffset di_;
};

class Worker : public PackageSender, public IPackageReceiver {
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q);

    ElementType get_receiver_type() const override { return ElementType::WORKER; }

    ElementID get_id() const override { return id_; }

    IPackageStockpile::const_iterator begin() const override { return q_->begin(); }

    IPackageStockpile::const_iterator end() const override { return q_->end(); }

    IPackageStockpile::const_iterator cbegin() const override { return q_->cbegin(); }

    IPackageStockpile::const_iterator cend() const override { return q_->cend(); }

    void receive_package(Package &&p) override { q_->push(std::move(p)); }

    void do_work(Time t);

    TimeOffset get_processing_duration() const { return pd_; }

    Time get_package_processing_start_time() const { return start_time_; }

    IPackageQueue *get_queue() const { return q_.get(); }

    std::optional<Package> const &get_processing_buffer() const { return processing_buffer_; }

private:
    ElementID id_;

    TimeOffset pd_;

    Time start_time_;

    std::unique_ptr<IPackageQueue> q_;

    std::optional<Package> processing_buffer_ = std::nullopt;

};

#endif //NETSIM_NODES_HPP
