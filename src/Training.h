#ifndef TRAINING_H
#define TRAINING_H

#include "Board.h"
#include "ReinforcementLearning.h"

class Training {
public:
    Training();
    void trainBot(int numEpisodes);

private:
    Board board;
    ReinforcementLearning bot;
};

#endif // TRAINING_H
