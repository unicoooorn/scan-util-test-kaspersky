//
// Created by Roman Gostilo on 11.06.2022.
//

#ifndef TEST_ASSIGNMENT_MOSCOW_SCANNER_H
#define TEST_ASSIGNMENT_MOSCOW_SCANNER_H

#include <boost/chrono.hpp>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;
namespace ch = boost::chrono;

typedef unsigned int counter;

class Scanner {
    counter scanned_total;
    counter suspicious_JS;
    counter suspicious_CMD;
    counter suspicious_EXE;
    counter error_count;

    ch::high_resolution_clock::time_point start_point;
public:
    Scanner();
    void processFile(fs::path file_to_scan);
    void scanFile(fs::path file_to_scan, std::string sus_line);
    void printReport();
};


#endif //TEST_ASSIGNMENT_MOSCOW_SCANNER_H
