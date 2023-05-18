#include "Training.h"

Training::Training() {
    // Initialize any necessary member variables
}

void Training::trainBot(int numEpisodes) {
    bot.train(numEpisodes);
}
