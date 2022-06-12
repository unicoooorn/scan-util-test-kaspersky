cmake_minimum_required(VERSION 3.21)
project(test_assignment_moscow)

set(Boost_INCLUDE_DIR /usr/local/Cellar/boost/1.78.0_1/include/)
set(Boost_LIBRARY_DIR /usr/local/Cellar/boost/1.78.0_1/lib/)
find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 17)

add_executable(scan_util main.cpp scanner.cpp scanner.h scan_utility.cpp scan_utility.h)
target_link_libraries(scan_util PRIVATE
        "/usr/local/Cellar/boost/1.78.0_1/lib//libboost_filesystem.a"
        "/usr/local/Cellar/boost/1.78.0_1/lib//libboost_chrono.a"
        "/usr/local/Cellar/boost/1.78.0_1/lib//libboost_thread-mt.a"
        )
