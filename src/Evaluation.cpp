#include "Evaluation.h"
#include "Board.h"

int Evaluation::evaluateBoard(const Board& board, Board::Player player) {
    int score = 0;

    for (int row = 0; row < board.ROWS; ++row) {
        for (int col = 0; col < board.COLUMNS; ++col) {
            if (board.getCell(row, col) == player) {
                // Evaluate rows
                if (col <= board.COLUMNS - board.WIN_LENGTH) {
                    int count = 1;
                    for (int k = 1; k < board.WIN_LENGTH; ++k) {
                        if (board.getCell(row, col + k) == player) {
                            count++;
                        }
                    }
                    if (count == board.WIN_LENGTH) {
                        score += count;
                    }
                }

                // Evaluate columns
                if (row <= board.ROWS - board.WIN_LENGTH) {
                    int count = 1;
                    for (int k = 1; k < board.WIN_LENGTH; ++k) {
                        if (board.getCell(row + k, col) == player) {
                            count++;
                        }
                    }
                    if (count == board.WIN_LENGTH) {
                        score += count;
                    }
                }

                // Evaluate diagonals (top-left to bottom-right)
                if (row <= board.ROWS - board.WIN_LENGTH && col <= board.COLUMNS - board.WIN_LENGTH) {
                    int count = 1;
                    for (int k = 1; k < board.WIN_LENGTH; ++k) {
                        if (board.getCell(row + k, col + k) == player) {
                            count++;
                        }
                    }
                    if (count == board.WIN_LENGTH) {
                        score += count;
                    }
                }

                // Evaluate diagonals (top-right to bottom-left)
                if (row <= board.ROWS - board.WIN_LENGTH && col >= board.WIN_LENGTH - 1) {
                    int count = 1;
                    for (int k = 1; k < board.WIN_LENGTH; ++k) {
                        if (board.getCell(row + k, col - k) == player) {
                            count++;
                        }
                    }
                    if (count == board.WIN_LENGTH) {
                        score += count;
                    }
                }
            }
        }
    }

    return score;
}
