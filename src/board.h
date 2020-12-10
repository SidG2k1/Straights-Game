#ifndef BOARD
#define BOARD

//#include <memory>
#include "humanPlayer.h"
#include "computerPlayer.h"

class Board {
    private:
        // The group of players in the game
        Player players[4];

        // Adds a new player to the game. Must have less than 4
        //     players already
        void initPlayers();

        //
        std::vector<Card> deck;
    public:
        // Initializes the board
        Board();

        // The group of 4 suites of 13 cards each.
        //     nullptr representes an unplayed card.
        std::vector<Card*[13]> table;

        // Checks if playing card is legal on this board
        bool isLegal(Card card);

        void printDeck();

        // Player chooses to end their gaming, and is replaced by
        //   a ComputerPlayer
        void rageQuit(Player* player);
};

#endif
