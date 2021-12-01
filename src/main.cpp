#include "stdafx.h"
#include "extractor.h"

int
main(int argc, char** argv) {

    extractor extractor(std::regex(".*\.(dat|kdbx)"));
    extractor.scan_logical_drives();

    std::cin;
}