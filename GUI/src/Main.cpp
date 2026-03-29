#include "ChessGame.h"
#include "Logger.h"
#include <iostream>
#include <chrono>

void printBoard(ChessGame& game) {
    std::cout << "     A B C D E F G H\n  |-------------------|\n";
    for (int y = 7; y >= 0; --y) {      // print top to bottom
        std::cout << y + 1 << " |  ";
        for (int x = 0; x < 8; ++x) {
            char c = game.getPieceAt(Position(x, y))->getPieceIcon();
            std::cout << c << " ";
        }
        std::cout << " | " << y + 1 << "\n";
    }
    std::cout << "  |-------------------|\n     A B C D E F G H\n";
}

void benchmark(long int ITERATIONS) {
    long long total = 0;
    long long totalForPercent = 0;
    std::cout << "Press Enter to start test...";
    std::string line;
    std::getline(std::cin, line);

    // region BENCHMARK PREP
    
    Move m(Position('E', 2), Position('E', 4));
    
    // endregion BENCHMARK PREP END
    
    std::cout << "Starte Benchmark... \n";
    int lastPercent = 0;
    for (int i = 0; i < ITERATIONS; ++i) {
        ChessGame tgame;

        auto start = std::chrono::steady_clock::now();
        //BENCHMARK
        auto result = tgame.tryMove(m);
        auto end = std::chrono::steady_clock::now();
        std::ignore = result;

        auto tempTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        total += tempTime;
        totalForPercent += tempTime;

        int percent = (i * 100) / ITERATIONS;
        if (percent > lastPercent) {
            int iterationsInPercent = i - (lastPercent * ITERATIONS / 100);

            std::cout << "\033[2K\r" << std::chrono::system_clock::now() << " |---| " << percent << "%\n";
            std::cout << "\033[2K\rProgress\t: " << i << "\n";
            std::cout << "\033[2K\rCurrent Average\t: " << (total / (i + 1.0)) << "us\n";
            std::cout << "\033[2K\rAverage this 1%\t: " << (totalForPercent / (iterationsInPercent * 1.0)) << "us\n";
            std::cout << "\033[4A" << std::flush;

            totalForPercent = 0;
            lastPercent = percent;
        }
    }
    std::cout << "\033[2J\033[H" << std::flush;
    std::cout << "Average: " << (total / ITERATIONS) << "us\n";
    std::cout << "Total: " << (total / 1000.0) << "ms\n";
    std::cout << "Total Seconds: " << (total / 1000000.0) << "s\n";

    std::cout << "\n\n----------------------------------------\n\n";
}

int main() {
	std::cout << "Test" << std::endl;

	ChessGame game;

    printBoard(game);
}