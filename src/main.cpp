#include <iostream>
#include "Board.h"
#include "Bot.h"
#include "Utilities.h"

int main() {
    // Instantiate the board and bot objects
    Board board;
    Bot bot;

    // Print welcome message and instructions
    std::cout << "Welcome to Connect Four!\n";
    std::cout << "You are playing against the bot.\n";
    std::cout << "Enter the column number (1-7) to make a move.\n";

    // Game loop
    while (!board.isGameOver()) {
        // Print the current board state
        std::cout << "Current Board:\n";
        board.printBoard();

        // Player's turn
        int playerMove;
        std::cout << "Your turn. Enter the column number: ";
        std::cin >> playerMove;

        // Validate and apply the player's move
        while (!board.isValidMove(playerMove)) {
            std::cout << "Invalid move. Please try again: ";
            std::cin >> playerMove;
        }
        board.makeMove(playerMove, Board::Player::Human);

        // Check if the player wins
        if (board.isGameOver()) {
            std::cout << "Congratulations! You win!\n";
            break;
        }

        // Bot's turn
        int botMove = bot.selectMove(board);

        // Apply the bot's move
        board.makeMove(botMove, Board::Player::Bot);
        std::cout << "Bot's Move: " << botMove << std::endl;

        // Check if the bot wins
        if (board.isGameOver()) {
            std::cout << "The bot wins!\n";
            break;
        }
    }

    // Print the final board state
    std::cout << "Final Board:\n";
    board.printBoard();

    std::cout << "Game Over!\n";

    return 0;
}
