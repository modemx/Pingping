#include "modemx.h"
#include <iostream>
#include <windows.h>
#include <stdlib.h>

std::vector<std::string> splitstring(std::string line, char limiter) {
    std::vector<std::string> strings;

    int counter = 0;
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == limiter) {
            strings.push_back(line.substr(counter, i - counter));
            counter = i + 1;
        }
    }
    strings.push_back(line.substr(counter, line.size() - counter));
    //for (auto& s : strings) std::cout << s << "\n";

    return strings;
}

int seatsort(std::string line, char c, int maxpos) {
    int xpos = 0;
    for (int i = 0; i < line.size() - 1; i++) {
        if (line[i] == c) {
            maxpos = (maxpos + xpos) / 2;
        }

        else {
            xpos = ((xpos + maxpos) / 2 ) + 1;
        }    
    }

    if (line[line.size() - 1] == c) {
        return xpos;
    }
    else {
        return maxpos;
    }
}

std::string getClipboard() {
    if (!OpenClipboard(nullptr)) {
        std::cout << "error" << "\n";
        return "";
    }

    HANDLE hData = GetClipboardData(CF_TEXT);
    if (hData == nullptr) {
        std::cout << "error" << "\n";
        return "";
    }
    char* pszText = static_cast<char*>(GlobalLock(hData));
    if (pszText == nullptr) {
        std::cout << "error" << "\n";
        return "";
    }
    
    std::string sendIp(pszText);
    GlobalUnlock(hData);
    CloseClipboard();
    
    return sendIp;
}

bool ValidateIp(std::string ipstring) {
    std::string ip = ipstring;
    int dotcount = 0;
    int numbercount = 0;
    int firstoc = 0;
    int secondoc = 0;
    int thirdoc = 0;
    int fourthoc = 0;
    
    std::vector<std::string> octsplit = splitstring(ip, '.');
    
    if (octsplit.size() != 4) {
        return false;
    }
    
    firstoc = std::atoi(octsplit[0].c_str());
    secondoc = std::atoi(octsplit[1].c_str());
    thirdoc = std::atoi(octsplit[2].c_str());
    fourthoc = std::atoi(octsplit[3].c_str());

    if (firstoc <= 255 && secondoc <= 255 && thirdoc <= 255 && fourthoc <= 255) {
        return true;
    }
    else {
        return false;
    }

}

void pingIp(std::string ip) {
    system(("ping " + ip).c_str());
}