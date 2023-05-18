#include "ReinforcementLearning.h"
#include <random>
#include <algorithm>

ReinforcementLearning::ReinforcementLearning()
    : learningRate(0.1),
      discountFactor(0.9),
      explorationRate(1.0),
      minExplorationRate(0.01),
      explorationDecayRate(0.01) {
    // Initialize any necessary member variables
}

void ReinforcementLearning::train(int numEpisodes) {
    for (int episode = 0; episode < numEpisodes; ++episode) {
        Board board;
        std::string currentState = stateToString(board);

        while (!board.isGameOver()) {
            int action;
            if (explore()) {
                action = selectMove(board); // Exploration
            } else {
                action = exploit(board); // Exploitation
            }

            Board::Player currentPlayer = (episode % 2 == 0) ? Board::Player::Bot : Board::Player::Human;
            board.makeMove(action, currentPlayer);

            std::string nextState = stateToString(board);
            double reward = (board.isGameOver()) ? -1.0 : 0.0;

            updateQValue(currentState, action, reward, nextState);

            currentState = nextState;
        }

        // Decay exploration rate after each episode
        explorationRate = std::max(minExplorationRate, explorationRate - explorationDecayRate);
    }
}

int ReinforcementLearning::selectMove(const Board& board) {
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

std::string ReinforcementLearning::stateToString(const Board& board) const {
    std::string state;
    for (int row = 0; row < Board::ROWS; ++row) {
        for (int col = 0; col < Board::COLUMNS; ++col) {
            switch (board.getCell(row, col)) {
                case Board::Player::None:
                    state += '0';
                    break;
                case Board::Player::Human:
                    state += '1';
                    break;
                case Board::Player::Bot:
                    state += '2';
                    break;
            }
        }
    }
    return state;
}

bool ReinforcementLearning::explore() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(gen) <= explorationRate;
}

int ReinforcementLearning::exploit(const Board& board) const {
    std::string state = stateToString(board);
    auto it = qTable.find(state);
    if (it != qTable.end()) {
        const std::vector<double>& qValues = it->second;
        auto maxIt = std::max_element(qValues.begin(), qValues.end());
        return std::distance(qValues.begin(), maxIt);
    }
    // If the state is not found in the Q-table, select a random move
    return selectMove(board);
}

void ReinforcementLearning::updateQValue(const std::string& state, int action, double reward, const std::string& nextState) {
    auto it = qTable.find(state);
    if (it == qTable.end()) {
        // Initialize Q-values for the current state if it doesn't exist
        qTable[state] = std::vector<double>(Board::COLUMNS, 0.0);
    }

    const std::vector<double>& qValues = qTable[state];
    double oldQValue = qValues[action];

    auto nextIt = qTable.find(nextState);
    double maxNextQValue = (nextIt != qTable.end()) ? *std::max_element(nextIt->second.begin(), nextIt->second.end()) : 0.0;

    // Update the Q-value using the Q-learning formula
    double newQValue = oldQValue + learningRate * (reward + discountFactor * maxNextQValue - oldQValue);

    // Update the Q-value in the Q-table
    qTable[state][action] = newQValue;
}
