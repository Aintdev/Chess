#include "ChessGame.h"
#include "iostream"
#include <cstdlib>

bool ChessGame::pieceCanMoveLikeThat(const Move& move) const {
    const Piece& srcP = board[move.fromX][move.fromY];
    using enum PieceType;

    // TODO LIST ->>>>>>>>>>>>>>> REDO ENTIRE SECTION BASED ON THIS: https://chatgpt.com/c/69a38f04-ac9c-832d-9dd3-1ef26d8e3fce 
    switch (srcP.type) {
    case PAWN:   return canPawnMove(move);
    case ROOK:   return canRookMove(move);
    //case KNIGHT: return canKnightMove(move);
    //case BISHOP: return canBishopMove(move);
    //case QUEEN:  return canQueenMove(move);
    //case KING:   return canKingMove(move);
    default: return false;
    }
    
}

bool ChessGame::pathClear(const Move& move) const {
    int deltaX = move.toX - move.fromX;
    int deltaY = move.toY - move.fromY;
    int absDeltaX = std::abs(deltaX);
    int absDeltaY = std::abs(deltaY);
    if (!((deltaX == 0) || (deltaY == 0) || (absDeltaX == absDeltaY)))
        return false;

    int directionX = (deltaX == 0) ? 0 : ((deltaX > 0) ? 1 : -1);
    int directionY = (deltaY == 0) ? 0 : ((deltaY > 0) ? 1 : -1);
    int stepNumber = std::max(absDeltaX, absDeltaY);

    for (int i = 1; i < stepNumber; ++i) {
        int x = move.fromX + i * directionX;
        int y = move.fromY + i * directionY;
        if (getPieceAt(x, y)->exists()) return false;
    }

    return true;
}

/// -------------------
/// CAN __________ MOVE
/// -------------------

bool ChessGame::canPawnMove(const Move& move) const {
    const Piece& src = board[move.fromX][move.fromY];
    const Piece& tgt = board[move.toX][move.toY];
    int dir = (src.color == Color::WHITE) ? 1 : -1;
    // Check if canPawnMove was called correctly
    if (!src.exists() || src.type != PieceType::PAWN) {
        Helpers::logError("Function 'ChessGame::canPawnMove' was called incorrectly cause either: Source Piece doesnt exists | or | Source Piece Type isnt 'Pawn'");
        return false; 
    }
    // Forward move
    if (
        move.fromX == move.toX && // it doesnt move horizontally
        move.fromY + dir == move.toY && // Piece can move in that direction and only moves one
        !tgt.exists() // Target does not have a Piece
        ) return true;
    // Inital two-square move
    else if (
        !src.hasMoved && // has not moved yet
        move.fromX == move.toX && // it doesnt move horizontally
        move.fromY + (2 * dir) == move.toY && // moves two forward
        !tgt.exists() && //tgt doesnt have a piece on it
        pathClear(move) //the piece in the middle is empty
        ) return true;
    // Capture Move´& Enpassant
    else if (
        (move.toX - move.fromX) == 1 && //move is one to the right or left
        move.fromY + dir == move.toY) { // move moves one forward
        const Piece& enpTGT = board[move.toX][move.toY - dir];
        if (// Normal Take
            tgt.exists() && !tgt.isColor(src.color) // target has to exist and be opposite color
            ) return true;

        else if (
            enpTGT.type == PieceType::PAWN && // Target that did the double forward is a Pawn
            !enpTGT.isColor(src.color) &&  // Target is of the opposite Color
            tgt.enPassantable // block i want to move to is actually enPassantable  and someone didnt just do two one moves.
            ) return true;
    }
    // Invalid Move
    return false;
}

bool ChessGame::canRookMove(const Move& move) const {
    const Piece& src = board[move.fromX][move.fromY];
    const Piece& tgt = board[move.toX][move.toY];
    MoveType type = move.getMoveType();
    using enum MoveType;
    if (!src.exists() || src.type != PieceType::ROOK) {
        Helpers::logError("Function 'ChessGame::canRookMove' was called incorrectly cause either: Source Piece doesnt exists | or | Source Piece Type isnt 'Rook'");
        return false;
    }

    return (type == HORIZONTAL || type == VERTICAL) &&
        pathClear(move) &&
        !tgt.isColor(src.color);
}

bool ChessGame::canBishopMove(const Move& move) const {
    const Piece& src = board[move.fromX][move.fromY];
    const Piece& tgt = board[move.toX][move.toY];
    MoveType type = move.getMoveType();
    using enum MoveType;
    if (!src.exists() || src.type != PieceType::BISHOP) {
        Helpers::logWarn("Function 'ChessGame::canBishopMove' was called incorrectly cause either: Source Piece doesnt exists | or | Source Piece Type isnt 'Bishop'");
        return false;
    }

    return (type == DIAGONAL) &&
        pathClear(move) &&
        !tgt.isColor(src.color);
}

bool ChessGame::canQueenMove(const Move& move) const {
    const Piece& src = board[move.fromX][move.fromY];
    const Piece& tgt = board[move.toX][move.toY];
    MoveType type = move.getMoveType();
    using enum MoveType;
    if (!src.exists() || src.type != PieceType::QUEEN) {
        Helpers::logWarn("Function 'ChessGame::canQueenMove' was called incorrectly cause either: Source Piece doesnt exists | or | Source Piece Type isnt 'Queen'");
        return false;
    }

    return (type >= HORIZONTAL && type <= DIAGONAL) &&
        pathClear(move) &&
        !tgt.isColor(src.color);
}