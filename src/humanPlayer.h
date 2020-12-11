#ifndef HUMAN_PLAYER
#define HUMAN_PLAYER

#include "player.h"

class HumanPlayer: public Player {
    private:
        bool toPrintState = true;
        void printState(std::vector<Card*[13]> table);
        bool existsLegalPlay(Board* board, std::vector<Card> cards, std::vector<Card*[13]> table);
    public:
        Action getAction(std::vector<Card*[13]> table) override;
};

#endif
