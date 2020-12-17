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

        // The associated board for the player
        Board* currBoard;

        // The cards in the players "hand"
        std::vector<Card> dealtCards;

        // The score so far for the player
        int discardRankSum;

        // Checks if playing card is legal on the specified table
        bool isLegal(std::vector<std::array<Card*, 13>> table, Card card);
    public:
        virtual ~Player() = 0;

        // Return an action for the player to play on the specified table
        virtual Action getAction(std::vector<std::array<Card*, 13>> table, bool printTable = true);
};


#endif
