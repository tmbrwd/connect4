#ifndef BOT_H
#define BOT_H

#include "Board.h"

class Bot {
public:
    Bot();

    int selectMove(const Board& board);

private:
    // Add any necessary private member variables or helper methods here
};

#endif // BOT_H
