#include "ChessGame.h"

Move::Move(const Position& from, const Position& to)
    : from(from), to(to), moveType(getMoveType()) {

    if (!from.inBoard() || !to.inBoard())
        throw std::out_of_range("Move coordinates are out of board");
}

MoveType Move::getMoveType() const {
    int dx = abs(to.x - from.x);
    int dy = abs(to.y - from.y);

    if (!dx && dy)                                      return MoveType::VERTICAL;
    if (dx && !dy)                                      return MoveType::HORIZONTAL;
    if (dx == dy)                                       return MoveType::DIAGONAL;
    if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2))   return MoveType::LSHAPE;
    return MoveType::NONE;
}

bool Move::operator==(const Move& other) const {
    return from.x == other.from.x &&
        from.y == other.from.y &&
        to.x == other.to.x &&
        to.y == other.to.y;
}