//
// Created by Roman Gostilo on 11.06.2022.
//

#include "Scanner.h"
#include <iostream>

namespace fs = boost::filesystem;
namespace ch = boost::chrono;

typedef unsigned int counter;

Scanner::Scanner() {
    start_point = ch::high_resolution_clock::now();
    scanned_total = 0;
    suspicious_JS = 0;
    suspicious_CMD = 0;
    suspicious_EXE = 0;
}

void Scanner::processFile(fs::path file_to_scan) {
    scanned_total++;
    std::string sus_line;
    std::cout << fs::extension(file_to_scan) << std::endl;
    if (fs::extension(file_to_scan) == ".js"){
        std::cout << "js file" << std::endl;
        sus_line = "<script>evil_script()</script>";
    }
    if (fs::extension(file_to_scan) == ".bat" or fs::extension(file_to_scan) == ".cmd"){
        std::cout << "cmd/bat file" << std::endl;
    }
    if (fs::extension(file_to_scan) == ".exe"){
        std::cout << "exe file" << std::endl;
    }
    scanFile(file_to_scan, sus_line);
}

void Scanner::scanFile(fs::path file_to_scan, std::string sus_line){
    fs::ifstream file(file_to_scan);
    std::string cur_str;
    while(getline(file, cur_str)){
//        std::cout << cur_str << std::endl;
        if (sus_line == cur_str){
            std::cout << file_to_scan << " sus file" << std::endl;
        }
    }
}

void Scanner::printReport() {
    std::cout << "====== Scan result ======" << std::endl;
    std::cout << "Processed files: " << scanned_total << std::endl;
    std::cout << "JS detects: " << suspicious_JS << std::endl;
    std::cout << "CMD detects: " << suspicious_CMD << std::endl;
    std::cout << "EXE detects: " << suspicious_EXE << std::endl;
    std::cout << "Errors: " << error_count << std::endl;
    std::cout << "Execution time: " << boost::chrono::duration_cast<boost::chrono::milliseconds>(
            ch::high_resolution_clock::now() - start_point) << std::endl;
    std::cout << "=========================" << std::endl;
};