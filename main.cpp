#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <string>
#include "Scanner.h"
#include <iostream>

namespace fs = boost::filesystem;

int main(int argc, char *argv[]) {
    fs::directory_iterator it("/Users/romangostilo/Desktop/Учёба/kasp/"), eod;

    Scanner scanner;
    BOOST_FOREACH(fs::path const &p, std::make_pair(it, eod)) {
                    scanner.processFile(p);
                }
    scanner.printReport();
    return 0;
}
