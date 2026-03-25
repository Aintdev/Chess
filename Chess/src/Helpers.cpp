#include "ChessGame.h"
#include <iostream>
#include <algorithm>
#include <locale>

void Helpers::toLower(std::string& s) {
    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) { return std::tolower(c); });
}