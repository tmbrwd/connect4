#ifndef REINFORCEMENTLEARNING_H
#define REINFORCEMENTLEARNING_H

#include "Board.h"
#include <unordered_map>
#include <vector>

class ReinforcementLearning {
public:
    ReinforcementLearning();
    void train(int numEpisodes);
    int selectMove(const Board& board);

private:
    std::unordered_map<std::string, std::vector<double>> qTable;
    double learningRate;
    double discountFactor;
    double explorationRate;
    double minExplorationRate;
    double explorationDecayRate;
    std::string stateToString(const Board& board) const;
    bool explore();
    int exploit(const Board& board) const;
    void updateQValue(const std::string& state, int action, double reward, const std::string& nextState);
};

#endif // REINFORCEMENTLEARNING_H
