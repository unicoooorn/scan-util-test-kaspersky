cmake_minimum_required(VERSION 3.21)
project(test_assignment_moscow)

set(Boost_INCLUDE_DIR /usr/local/Cellar/boost/1.78.0_1/include/)
set(Boost_LIBRARY_DIR /usr/local/Cellar/boost/1.78.0_1/lib/)
find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 17)

add_executable(test_assignment_moscow main.cpp Scanner.cpp Scanner.h ScanUtility.cpp ScanUtility.h)
target_link_libraries(test_assignment_moscow PRIVATE
        "/usr/local/Cellar/boost/1.78.0_1/lib//libboost_filesystem.a"
        "/usr/local/Cellar/boost/1.78.0_1/lib//libboost_chrono.a"
        )
