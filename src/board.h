#ifndef BOARD
#define BOARD

#include "player.h"
#include "humanPlayer.h"
#include "computerPlayer.h"

class Board {
    private:
        // The group of players in the game
        Player* players[4];

        // Adds a new player to the game. Must have less than 4
        //     players already
        void initPlayers();

        //
        std::vector<Card> shuffledDeck;
    public:
        // Initializes the board
        Board();

        ~Board() {}

        // The group of 4 suites of 13 cards each.
        //     nullptr representes an unplayed card.
        std::vector<std::array<Card*, 13>> table;

        void printDeck();

        // Player chooses to end their gaming, and is replaced by
        //   a ComputerPlayer
        void rageQuit(Player* player);
};

#endif
