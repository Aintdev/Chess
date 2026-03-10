#include "ChessGame.h"

Move::Move(unsigned int ifromX, unsigned int ifromY, unsigned int itoX, unsigned int itoY)
    : fromX(ifromX), fromY(ifromY), toX(itoX), toY(itoY) {

    if (Helpers::outOfBoard(ifromX, ifromY) ||
        Helpers::outOfBoard(itoX, itoY))
        throw std::out_of_range("Move coordinates are out of board");
    getMoveType();
}

MoveType Move::getMoveType() const {
    bool itMovesVertical = fromY != toY;
    bool itMovesHorizontal = fromX != toX;
    bool itMovesBoth = itMovesHorizontal && itMovesVertical;

    if (!itMovesBoth) {
        if (!itMovesVertical && itMovesHorizontal)
            return MoveType::HORIZONTAL;
        else if (itMovesVertical && !itMovesHorizontal)
            return MoveType::VERTICAL;
    }
}

bool Move::operator==(const Move& other) const {
    return fromX == other.fromX &&
        fromY == other.fromY &&
        toX == other.toX &&
        toY == other.toY;
}