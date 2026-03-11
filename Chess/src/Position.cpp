#include "ChessGame.h"

Position::Position(int x, int y)
	: x(x), y(y) {
	if (Helpers::outOfBoard(x, y)) {
		Helpers::logError("Position construction failed -- Position not inside board parameters.");
		throw std::out_of_range("Coordinates are out of board");
	}
}

Position::Position(const Move& move)
	: Position(move.from.x, move.from.y) { }

bool Position::operator==(const Position& other) {
	return x == other.x && y == other.y;
}