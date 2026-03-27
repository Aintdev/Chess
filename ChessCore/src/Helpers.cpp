#include "pch.h"
#include "ChessGame.h"

#include <algorithm>


void Helpers::toLower(std::string& s) {
    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) { return std::tolower(c); });
}