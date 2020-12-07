#ifndef PLAYER
#define PLAYER

#include <vector>
#include <iostream>
#include "action.h"
#include "card.h"
#include "board.h"

class Player {
    protected:
        bool isHuman;
        Board* currBoard;
        std::vector<Card> dealtCards;
        int discardRankSum;
    public:
        virtual Action getAction();
};


#endif
