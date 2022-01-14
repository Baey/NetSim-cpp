#ifndef NODES_MOCKS_HPP_
#define NODES_MOCKS_HPP_


#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "config.hpp"

#include "nodes.hpp"

class MockReceiver : public IPackageReceiver {
public:
    MOCK_METHOD1(receive_package, void(Package&&));

    MOCK_CONST_METHOD0(begin, IPackageStockpile::const_iterator());

    MOCK_CONST_METHOD0(cbegin, IPackageStockpile::const_iterator());

    MOCK_CONST_METHOD0(end, IPackageStockpile::const_iterator());

    MOCK_CONST_METHOD0(cend, IPackageStockpile::const_iterator());

<<<<<<< HEAD
//    #ifdef WITH_RECEIVER_TYPE
    MOCK_CONST_METHOD0(get_receiver_type, ElementType());
//    #endif
=======
    #ifdef WITH_RECEIVER_TYPE
    MOCK_CONST_METHOD0(get_receiver_type, ReceiverType());
    #endif
>>>>>>> 6a77555d0cab570d8ffb2aa7c47cdd303a45f109

    MOCK_CONST_METHOD0(get_id, ElementID());
};

#endif /* MOCKS_GLOBAL_FUNCTIONS_MOCK_HPP_ */
