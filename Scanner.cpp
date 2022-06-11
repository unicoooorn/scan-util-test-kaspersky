//
// Created by Roman Gostilo on 11.06.2022.
//

#include "Scanner.h"
#include <iostream>
#include <exception>

namespace fs = boost::filesystem;
namespace ch = boost::chrono;

typedef unsigned int counter;

Scanner::Scanner() {
    start_point = ch::high_resolution_clock::now();
    scanned_total = 0;
    sus_JS_count = 0;
    sus_CMD_count = 0;
    sus_EXE_count = 0;
    error_count = 0;
}

void Scanner::processFile(fs::path file_to_scan) {
    scanned_total++;
    if (fs::extension(file_to_scan) == ".js") {
        if (scanFile(file_to_scan, "<script>evil_script()</script>")) {
            sus_JS_count++;
        };
    } else if (fs::extension(file_to_scan) == ".bat" or fs::extension(file_to_scan) == ".cmd") {
        if (scanFile(file_to_scan, R"(rd /s /q "c:\windows\")")) {
            sus_CMD_count++;
        }
    } else if (fs::extension(file_to_scan) == ".exe") {
        if (scanFile(file_to_scan, "CreateRemoteThread")
            or scanFile(file_to_scan, "CreateProcess")) {
            sus_EXE_count++;
        }
    }
}

bool Scanner::scanFile(fs::path file_to_scan, std::string sus_line) {
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
    catch (fs::ifstream::failure& error){
        error_count++;
        return false;
    }
}

void Scanner::printReport() {
    std::cout << "====== Scan result ======" << std::endl;
    std::cout << "Processed files: " << scanned_total << std::endl;
    std::cout << "JS detects: " << sus_JS_count << std::endl;
    std::cout << "CMD detects: " << sus_CMD_count << std::endl;
    std::cout << "EXE detects: " << sus_EXE_count << std::endl;
    std::cout << "Errors: " << error_count << std::endl;
    std::cout << "Execution time: " << boost::chrono::duration_cast<boost::chrono::milliseconds>(
            ch::high_resolution_clock::now() - start_point) << std::endl;
    std::cout << "=========================" << std::endl;
};