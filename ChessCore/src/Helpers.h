#pragma once
#include "pch.h"
#include "Piece.h"

using Arr8By8 = std::array<std::array<Piece, 8>, 8>;
namespace Helpers {
    void toLower(std::string& s);
    Arr8By8 initDefaultBoard();
}