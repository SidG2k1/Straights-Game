#ifndef BOARD
#define BOARD

#include "player.h"
#include "humanPlayer.h"
#include "computerPlayer.h"
#include "smartComputer.h"

#include <algorithm>
#include <random>
#include <memory>

class Board {
    private:
        // The group of players in the game
        std::array<std::shared_ptr<Player>, 4> players;

        // clears the table
        void resetTable();
        
        // Adds a new player to the game. Must have less than 4
        //     players already
        void initPlayers(bool enableBonus);

        std::vector<Card> shuffledDeck;

        // Shuffles Board::shuffledDeck with the given seed
        void shuffleDeck(int seed);

        // Deals cards from shuffledDeck to the players (and clears their dealt card list)
        void dealCards();

        // Returns the maximum Player::discardRankSum among all Board::players
        int maxDiscardSum();

        // The pile of discards from each player
        std::array<std::vector<Card>, 4> playerDiscardStash;
        
        std::vector<std::shared_ptr<Card>> smartCardPtrStore;
    public:
        // Initializes the board
        Board(bool enableBonus);

        ~Board() {}

        // The group of 4 suites of 13 cards each.
        //     nullptr representes an unplayed card.
        std::vector<std::array<Card*, 13>> table;

        void printDeck();

        // Player chooses to end their gaming, and is replaced by
        //   a ComputerPlayer
        void rageQuit(int playerIdx);

        // This is the primary method of play.
        void start(int seed, bool enableBonus);
};

class QuitSignal{};

#endif
