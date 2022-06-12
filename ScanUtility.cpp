//
// Created by Roman Gostilo on 11.06.2022.
//

#include <thread>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include "ScanUtility.h"
#include "Scanner.h"
#include <iostream>

void utilscan::scan_directory(std::string &&path) {
    unsigned int thread_count = std::thread::hardware_concurrency();
    fs::directory_iterator it(path), eod;
    Scanner scanner;
    std::vector<std::thread *> thread_pool(thread_count, nullptr);
    unsigned int thread_number = 0;
    // scanning through directory
    BOOST_FOREACH(fs::path const &p, std::make_pair(it, eod)) {
                    std::cout << thread_number << std::endl;
                    if (thread_pool[thread_number]) {
                        thread_pool[thread_number]->join();
                        delete thread_pool[thread_number];
                        thread_pool[thread_number] = nullptr;
                    }
                    thread_pool[thread_number] = new std::thread(&Scanner::processFile, &scanner, p);
                    thread_number = (thread_number + 1) % thread_count;
                }
    // terminating threads
    for (std::thread *cur_th: thread_pool) {
        if (cur_th) {
            cur_th->join();
            delete cur_th;
            cur_th = nullptr;
        }
    }
    scanner.printReport();
}
