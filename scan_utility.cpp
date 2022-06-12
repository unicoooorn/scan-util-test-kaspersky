//
// Created by Roman Gostilo on 11.06.2022.
//

#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "scan_utility.h"
#include "scanner.h"
#include <iostream>



void util_scan::ScanDirectory(std::string &&path) {
    // checking whether directory exists or not
    if (!fs::exists( path))
    {
        std::cout << "No such directory: " << path << std::endl;
        return;
    }
    // scan through directory
    boost::asio::thread_pool thread_pool(boost::thread::hardware_concurrency());
    Scanner scanner;
    fs::directory_iterator it(path), eod;
    BOOST_FOREACH(fs::path const &p, std::make_pair(it, eod)) {
                    boost::asio::post(thread_pool, std::bind(&Scanner::ProcessFile, &scanner, p));
                }
    thread_pool.join();
    scanner.PrintReport();
}
