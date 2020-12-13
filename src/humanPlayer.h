#ifndef HUMAN_PLAYER
#define HUMAN_PLAYER

#include "player.h"

class HumanPlayer: public Player {
    private:
        // Prints the lines from "Cards on the table:" to "Legal plays:" inclusive
        void printState(std::vector<std::array<Card*, 13>> table);

        // Checks if there is any legal play in cards for the table table.
        bool existsLegalPlay(Board* board, std::vector<Card> cards, std::vector<std::array<Card*, 13>> table);
    public:

        // Fetches the player action
        Action getAction(std::vector<std::array<Card*, 13>> table, bool printTable = true) override;
};

#endif
