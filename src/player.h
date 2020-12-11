#ifndef PLAYER
#define PLAYER

#include <vector>
#include <iostream>
#include "action.h"
#include "card.h"
//#include "board.h"

class Board;

class Player {
    friend class Board;
    protected:
        bool isHuman;
        Board* currBoard;
        std::vector<Card> dealtCards;
        int discardRankSum;

        // Checks if playing card is legal on the specified table
        bool isLegal(std::vector<Card*[13]> table, Card card);
    public:
        virtual Action getAction(std::vector<Card*[13]> table);
};


#endif
