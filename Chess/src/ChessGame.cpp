#include "ChessGame.h"
#include "DefaultBoard.h"

ChessGame::ChessGame() : board(initDefaultBoard()) {} // do initializer list

bool ChessGame::tryMove(const Move& move) {
    std::vector<Move> movesVector = generateMoves(board[move.from.x][move.from.y].color);
    auto it = std::find(movesVector.begin(), movesVector.end(), move);

    if (it == movesVector.end())
        return false;

    if (!board[move.from.x][move.from.y].exists()) return false;
    board[move.to.x][move.to.y] = board[move.from.x][move.from.y];
    board[move.from.x][move.from.y] = { PieceType::NONE, Color::NONE };
    return true;
}

bool ChessGame::tryMove(const Position& from, const Position& to) {
    const Move mv = Move(from, to);
    return tryMove(mv); // call existing movePiece(int,int,int,int)
}

const Piece* ChessGame::getPieceAt(const Position& pos) const
{
    if (!pos.inBoard()) return nullptr;
    return &board[pos.x][pos.y];
}

template<typename Func>
void ChessGame::forEachSquare(Func f) {
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            f(Position(x, y));
        }
    }
}