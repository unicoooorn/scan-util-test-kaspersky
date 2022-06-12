//
// Created by Roman Gostilo on 11.06.2022.
//

#include "scan_utility.h"
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc == 1){
        std::cout << "scan_util: usage: scan_util [directory]" << std::endl;
        return 0;
    }
    util_scan::ScanDirectory(argv[1]);
}
