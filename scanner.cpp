//
// Created by Roman Gostilo on 11.06.2022.
//

#include "scanner.h"
#include <iostream>
#include <exception>

namespace fs = boost::filesystem;
namespace ch = boost::chrono;

Scanner::Scanner() {
    start_point = ch::high_resolution_clock::now();
    scanned_total_ = 0;
    sus_JS_count_ = 0;
    sus_CMD_count_ = 0;
    sus_EXE_count_ = 0;
    error_count_ = 0;
}

// file processing and passing into scanning function
void Scanner::ProcessFile(const fs::path &file_to_scan) {
    scanned_total_++;
    // checks for extension and calls ScanFile to scan for suspicious line
    if (fs::extension(file_to_scan) == ".js") {
        if (ScanFile(file_to_scan, "<script>evil_script()</script>")) {
            sus_JS_count_++;
        };
    } else if (fs::extension(file_to_scan) == ".bat"
               or fs::extension(file_to_scan) == ".cmd") {
        if (ScanFile(file_to_scan, R"(rd /s /q "c:\windows\")")) {
            sus_CMD_count_++;
        }
    } else if (fs::extension(file_to_scan) == ".exe") {
        if (ScanFile(file_to_scan, "CreateRemoteThread")
            or ScanFile(file_to_scan, "CreateProcess")) {
            sus_EXE_count_++;
        }
    }
}

// scanning file for suspicious line
bool Scanner::ScanFile(const fs::path &file_to_scan, const std::string &sus_line) {
    try {
        fs::ifstream file(file_to_scan);
        std::string cur_str;
        while (getline(file, cur_str)) {
            if (sus_line == cur_str) {
                return true;
            }
        }
        return false;
    }
    catch (fs::ifstream::failure &error) {
        error_count_++;
        return false;
    }
}

void Scanner::PrintReport() const {
    std::cout << "====== Scan result ======" << std::endl;
    std::cout << "Processed files: " << scanned_total_ << std::endl;
    std::cout << "JS detects: " << sus_JS_count_ << std::endl;
    std::cout << "CMD detects: " << sus_CMD_count_ << std::endl;
    std::cout << "EXE detects: " << sus_EXE_count_ << std::endl;
    std::cout << "Errors: " << error_count_ << std::endl;

    auto working_time = ch::duration_cast<ch::milliseconds>(
            ch::high_resolution_clock::now() - start_point);
    std::cout << "Execution time: " << std::setw(2) << std::setfill('0') <<
              ch::duration_cast<boost::chrono::minutes>(working_time).count() << ':' <<
              std::setw(2) <<
              ch::duration_cast<boost::chrono::seconds>(working_time).count() % 60 << ':' <<
              std::setw(2) <<
              ch::duration_cast<boost::chrono::milliseconds>(working_time).count() % 60 << std::endl;
    std::cout << "=========================" << std::endl;
};