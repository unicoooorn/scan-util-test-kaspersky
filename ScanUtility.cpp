//
// Created by Roman Gostilo on 11.06.2022.
//

#include <thread>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include "ScanUtility.h"
#include "Scanner.h"

void utilscan::scan_directory(std::string &&path) {
    unsigned int thread_number = 2 * std::thread::hardware_concurrency();
    fs::directory_iterator it(path), eod;
    Scanner scanner;
    std::vector<std::thread *> thread_pool(thread_number, nullptr);
    int thread_counter = -1;
    // scanning through directory
    BOOST_FOREACH(fs::path const &p, std::make_pair(it, eod)) {
                    thread_counter++;
                    if (thread_pool[thread_counter]) {
                        thread_pool[thread_counter]->join();
                        delete thread_pool[thread_counter];
                        thread_pool[thread_counter] = nullptr;
                    }
                    thread_pool[thread_counter] = new std::thread(&Scanner::processFile, &scanner, p);
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
