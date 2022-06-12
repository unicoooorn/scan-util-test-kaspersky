//
// Created by Roman Gostilo on 11.06.2022.
//

#ifndef SCAN_UTIL_KASPERSKY_TEST_SCANNER_H
#define SCAN_UTIL_KASPERSKY_TEST_SCANNER_H

#include <boost/chrono.hpp>
#include <boost/filesystem.hpp>
#include <boost/thread.hpp>

namespace fs = boost::filesystem;
namespace ch = boost::chrono;

// using boost atomic to prevent race condition
typedef boost::atomic<unsigned int> counter;

class Scanner {
    counter scanned_total_;
    counter sus_JS_count_;
    counter sus_CMD_count_;
    counter sus_EXE_count_;
    counter error_count_;
    ch::high_resolution_clock::time_point start_point;
    // Scanner scans file for the sus line and returns true if the line found
    bool ScanFile(const fs::path &file_to_scan, const std::string &sus_line);
public:
    Scanner();
    // Scanner checks file extension and chooses a suspicious line to scan for
    void ProcessFile(const fs::path &file_to_scan);
    // Scanner can print the report any time user ask him to do so
    // always prints report at the end of the scanning
    //
    //  report format
    //  ====== Scan result ======
    //  Processed files: scanned_total_
    //  JS detects: sus_JS_count_
    //  CMD detects: sus_CMD_count_
    //  EXE detects: sus_EXE_count_
    //  Errors: error_count_
    //  Execution time: now() - start_point
    //=========================
    void PrintReport() const;
};


#endif //SCAN_UTIL_KASPERSKY_TEST_SCANNER_H
