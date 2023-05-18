#ifndef EVALUATION_H
#define EVALUATION_H

#include "Board.h"

class Evaluation {
public:
    static int evaluateBoard(const Board& board, Board::Player player);
};

#endif // EVALUATION_H
