//
// Created by szczy on 04.01.2022.
//

#include "nodes.hpp"

Worker::Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q) : PackageSender() {
    id_ = id;
    pd_ = pd;
    q_ = std::move(q);
}

