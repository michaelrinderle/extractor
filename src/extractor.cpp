#include "extractor.h"

extractor::extractor(std::regex pattern)
{
    this->pattern = pattern;
}

std::vector<char>
extractor::get_logical_drives() {
    DWORD drives = 100;
    char lpBuffer[100];
    DWORD dwResult = GetLogicalDriveStrings(drives, (LPSTR)lpBuffer);

    if (dwResult > 0 && dwResult <= MAX_PATH)
    {
        char* szSingleDrive = lpBuffer;
        while (*szSingleDrive)
        {
            drive_labels.push_back(szSingleDrive[0]);
            szSingleDrive += strlen(szSingleDrive) + 1;
        }
    }
    return drive_labels;
}

void
extractor::scan_logical_drives()
{
    if (drive_labels.size() == 0) {
        this->get_logical_drives();
    }

    for (auto& drive : drive_labels) {
        std::string full_path;
        full_path.push_back(drive);
        full_path += ":";
        this->iterate_folder(full_path);
    }
}

void
extractor::iterate_directory(std::string directory)
{
    std::string tmp = directory + "\\*";
    WIN32_FIND_DATA data;
    HANDLE h_find = FindFirstFile((LPCSTR)tmp.c_str(), &data);
    if (h_find != INVALID_HANDLE_VALUE) {


        std::vector<std::string> dirs;

        do {
            if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                if ((!lstrcmp(data.cFileName, ".")) || (!lstrcmp(data.cFileName, "..")))
                    continue;
            }

            tmp = directory + "\\" + std::string(data.cFileName);


            if (std::regex_match(tmp, this->pattern)) {
                std::cout << tmp << std::endl;
            }


            if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                dirs.push_back(tmp);
            }

        } while (FindNextFile(h_find, &data));

        FindClose(h_find);

        for (auto& dir : dirs) {
            this->iterate_folder(dir);
        }
    }
}

