#include "ChessGame.h"

Move::Move(unsigned int ifromX, unsigned int ifromY, unsigned int itoX, unsigned int itoY)
    : fromX(ifromX), fromY(ifromY), toX(itoX), toY(itoY), moveType(getMoveType()) {

    if (Helpers::outOfBoard(ifromX, ifromY) ||
        Helpers::outOfBoard(itoX, itoY))
        throw std::out_of_range("Move coordinates are out of board");
}

MoveType Move::getMoveType() const {
    int dx = abs(toX - fromX);
    int dy = abs(toY - fromY);

    if (dx == 0 && dy != 0)                             return MoveType::VERTICAL;
    if (dx != 0 && dy == 0)                             return MoveType::HORIZONTAL;
    if (dx == dy)                                       return MoveType::DIAGONAL;
    if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2))   return MoveType::LSHAPE;
    return MoveType::NONE;
}

bool Move::operator==(const Move& other) const {
    return fromX == other.fromX &&
        fromY == other.fromY &&
        toX == other.toX &&
        toY == other.toY;
}