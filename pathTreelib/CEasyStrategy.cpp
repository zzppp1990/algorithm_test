#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "CEasyStrategy.h"


void CEasyStrategy::Init(std::string input) {
    m_sInputStr = input;
}

int CEasyStrategy::getFileAbsPath() {
    std::istringstream iss(m_sInputStr);
    std::vector<std::string> dirs;
    std::string str;
    while (getline(iss, str)) {
        dirs.push_back(str);
    }
    std::vector<int> pathLen(dirs.size()+1,0);
    int maxLen = 0;
    for (const std::string& s : dirs) {
        int i = 0;
        while (i < s.size() && s[i] == '\t') ++i;
        pathLen[i + 1] = pathLen[i] + s.size() - i+1;
        if (s.find('.') != std::string::npos) {
            maxLen = std::max(maxLen, pathLen[i + 1] - 1);
        }
    }
    return maxLen;
}

