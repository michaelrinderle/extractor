#ifndef EXTRACTOR_H
#define EXTRACTOR_H
#pragma once
#include "stdafx.h"


class extractor {

public:
    std::regex pattern;
    std::vector<std::string> targets;

    extractor(std::regex pattern);
    std::vector<char> get_logical_drives();
    void scan_logical_drives();
    void iterate_directory(std::string directory);

private:
    std::vector<char> drive_labels;
    std::vector<std::string> file_matches;
};

#endif // EXTRACTOR_H
