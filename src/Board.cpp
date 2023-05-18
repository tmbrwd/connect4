#include "Board.h"
#include <iostream>

Board::Board() {
    reset();
}

void Board::reset() {
    board.clear();
    board.resize(ROWS, std::vector<Player>(COLUMNS, Player::None));
    currentPlayer = Player::Human;
}

bool Board::isFull() const {
    for (int col = 0; col < COLUMNS; ++col) {
        if (board[0][col] == Player::None) {
            return false;
        }
    }
    return true;
}

bool Board::isValidMove(int column) const {
    if (column < 0 || column >= COLUMNS) {
        return false;
    }
    return board[0][column] == Player::None;
}

bool Board::makeMove(int column, Player player) {
    if (!isValidMove(column)) {
        return false;
    }

    for (int row = ROWS - 1; row >= 0; --row) {
        if (board[row][column] == Player::None) {
            board[row][column] = player;
            return true;
        }
    }

    return false;
}

Board::Player Board::checkForWinner() const {
    // Check rows
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col <= COLUMNS - WIN_LENGTH; ++col) {
            Player player = board[row][col];
            if (player != Player::None) {
                bool win = true;
                for (int k = 1; k < WIN_LENGTH; ++k) {
                    if (board[row][col + k] != player) {
                        win = false;
                        break;
                    }
                }
                if (win) {
                    return player;
                }
            }
        }
    }

    // Check columns
    for (int col = 0; col < COLUMNS; ++col) {
        for (int row = 0; row <= ROWS - WIN_LENGTH; ++row) {
            Player player = board[row][col];
            if (player != Player::None) {
                bool win = true;
                for (int k = 1; k < WIN_LENGTH; ++k) {
                    if (board[row + k][col] != player) {
                        win = false;
                        break;
                    }
                }
                if (win) {
                    return player;
                }
            }
        }
    }

    // Check diagonals (top-left to bottom-right)
    for (int row = 0; row <= ROWS - WIN_LENGTH; ++row) {
        for (int col = 0; col <= COLUMNS - WIN_LENGTH; ++col) {
            Player player = board[row][col];
            if (player != Player::None) {
                bool win = true;
                for (int k = 1; k < WIN_LENGTH; ++k) {
                    if (board[row + k][col + k] != player) {
                        win = false;
                        break;
                    }
                }
                if (win) {
                    return player;
                }
            }
        }
    }

    // Check diagonals (top-right to bottom-left)
    for (int row = 0; row <= ROWS - WIN_LENGTH; ++row) {
        for (int col = WIN_LENGTH - 1; col < COLUMNS; ++col) {
            Player player = board[row][col];
            if (player != Player::None) {
                bool win = true;
                for (int k = 1; k < WIN_LENGTH; ++k) {
                    if (board[row + k][col - k] != player) {
                        win = false;
                        break;
                    }
                }
                if (win) {
                    return player;
                }
            }
        }
    }

    // Check for a draw
    if (isFull()) {
        return Player::None;
    }

    // No winner yet
    return Player::None;
}

void Board::printBoard() const {
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLUMNS; ++col) {
            char symbol;
            switch (board[row][col]) {
                case Player::None:
                    symbol = '-';
                    break;
                case Player::Human:
                    symbol = 'X';
                    break;
                case Player::Bot:
                    symbol = 'O';
                    break;
            }
            std::cout << symbol << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

Board::Player Board::getCurrentPlayer() {
    return currentPlayer;
}

Board::Player Board::getCell(int row, int col) const {
    return board[row][col];
}

bool Board::isGameOver() const {
    return checkForWinner() != Player::None || isFull();
}
