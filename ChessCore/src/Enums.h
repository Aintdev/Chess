#pragma once
#include "pch.h"

enum class PieceType { NONE, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING };
enum class Color { NONE, WHITE, BLACK };
enum class Extra { NONE, DOUBLE };
enum class MoveType { NONE, HORIZONTAL, VERTICAL, DIAGONAL, LSHAPE };