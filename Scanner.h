//
// Created by Roman Gostilo on 11.06.2022.
//

#ifndef SCAN_UTIL_KASPERSKY_TEST_H
#define SCAN_UTIL_KASPERSKY_TEST_H

#include <boost/chrono.hpp>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;
namespace ch = boost::chrono;

typedef std::atomic<unsigned int> counter;

class Scanner {
    counter scanned_total;
    counter sus_JS_count;
    counter sus_CMD_count;
    counter sus_EXE_count;
    counter error_count;
    ch::high_resolution_clock::time_point start_point;
    bool scanFile(fs::path file_to_scan, std::string sus_line);
public:
    Scanner();
    void processFile(const fs::path &file_to_scan);
    void printReport() const;
};


#endif //SCAN_UTIL_KASPERSKY_TEST_H
