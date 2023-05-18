#ifndef BOARD_H
#define BOARD_H

#include <vector>

class Board {
public:
    enum class Player {
        None,
        Human,
        Bot
    };

    static const int ROWS = 6;
    static const int COLUMNS = 7;
    static const int WIN_LENGTH = 4;

    Board();
    void reset();
    bool isFull() const;
    bool isValidMove(int column) const;
    bool makeMove(int column, Player player);
    Player checkForWinner() const;
    void printBoard() const;
    Player getCurrentPlayer();
    Player getCell(int row, int col) const;
    bool isGameOver() const;

private:
    std::vector<std::vector<Player>> board;
    Player currentPlayer;
};

#endif // BOARD_H
