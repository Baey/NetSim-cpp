cmake_minimum_required(VERSION 3.13)
project(NetSim)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors -Werror=switch)

include_directories(
        include
)

#Add the google test subdirectory
add_subdirectory(NetSim_test/lib)

#include googletest/include dir
#include_directories(NetSim_tests/lib/googletest/include)

#include the googlemock/include dir
#include_directories(NetSim_tests/lib/googlemock/include)

##Define your executable
#add_executable(EXECUTABLE_NAME ${SOURCE_FILES})
#
##Link with GoogleTest
#target_link_libraries(EXECUTABLE_NAME gtest gtest_main)
#
##Link with GoogleMock
#target_link_libraries(EXECUTABLE_NAME gmock gmock_main)


set(SOURCE_FILES
        include/types.hpp
        include/package.hpp
        include/storage_types.hpp
        include/nodes.hpp
        include/helpers.hpp
        include/factory.hpp
        include/reports.hpp
        include/simulation.hpp

        src/package.cpp
        src/storage_types.cpp
        src/nodes.cpp
        src/factory.cpp
        src/helpers.cpp
        src/reports.cpp
        src/simulation.cpp
        )

#add_executable(my_project_debug ${SOURCE_FILES} main.cpp)

set(SOURCES_FILES_TESTS
        NetSim_test/tests/test_Factory
        NetSim_test/tests/test_factory_io.cpp
        NetSim_test/tests/test_nodes.cpp
        NetSim_test/tests/test_package.cpp
        NetSim_test/tests/test_storage_types.cpp
        NetSim_test/tests/test_reports.cpp
        NetSim_test/tests/test_simulate.cpp
        )

add_executable(NetSim_test ${SOURCE_FILES} ${SOURCES_FILES_TESTS} NetSim_test/tests/main_gtest.cpp)

target_include_directories(NetSim_test PUBLIC
        NetSim_test/lib/googlemock/include
        NetSim_test/lib/googletest/include
        NetSim_test/mocks
        )

#add_subdirectory(NetSim_tests/lib)

target_link_libraries(NetSim_test gmock)

add_executable(NetSim ${SOURCE_FILES})