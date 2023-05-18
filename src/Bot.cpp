#include "Bot.h"
#include <random>

Bot::Bot() {
    // Initialize any necessary member variables
}

int Bot::selectMove(const Board& board) {
    std::vector<int> validMoves;
    for (int column = 0; column < Board::COLUMNS; ++column) {
        if (board.isValidMove(column)) {
            validMoves.push_back(column);
        }
    }

    // Randomly select a valid move
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, validMoves.size() - 1);
    int randomIndex = dist(gen);
    return validMoves[randomIndex];
}
