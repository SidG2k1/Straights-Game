#ifndef HUMAN_PLAYER
#define HUMAN_PLAYER

#include "player.h"

class HumanPlayer: public Player {
    private:
        void printState();
    public:
        Action getAction() override;
};

#endif
