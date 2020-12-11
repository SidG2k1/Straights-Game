#include "board.h"

Board::Board() {
    // initializes the board.
    for (int i = 0; i < 4; ++i) {
        std::array<Card*, 13> newSuiteList;
        for (int j = 0; j < 13; ++j) {newSuiteList[j] = nullptr;}
        table.push_back(newSuiteList);
    }
    initPlayers();
}

void Board::initPlayers() {
    for (int i = 0; i < 3; ++i) {
        std::cout << "Is Player" << i + 1 << "  a human (h) or a computer (c)?" << std::endl;
        std::cout << ">";
        std::string playerType;
        while ((!(std::cin >> playerType)) || (playerType != "h" && playerType != "c")) {
            // this is not in spec, but makes it more robust
            std::cout << "Please make your selection again: Can't interpret " << playerType << ".\n>";
        }
        if (playerType == "h") {
            HumanPlayer player;
            players[i] = &player;
        } else if (playerType == "c") {
            ComputerPlayer player;
            players[i] = &player;
        }
    }
}

void Board::printDeck() {
    for (int i = 0; i < 52; ++i) {
        std::cout << shuffledDeck[i].getName() << " ";
        if ((i != 0) && (i%13 == 0)) {std::cout << std::endl;}
    }
}

void Board::rageQuit(Player* player) {
    int playerIdx = 0;
    for (; playerIdx <= 4; ++playerIdx) {
        if (players[playerIdx]->dealtCards == player->dealtCards) {
            // Dealt Cards is uniquely identifying
            std::cout << "Player " << playerIdx + 1 << "ragequits. A computer will now take over." << std::endl;
            break;
        }
    }
    ComputerPlayer newPlayer;
    newPlayer.currBoard = this; // which is equal to player.currBoard
    newPlayer.dealtCards = players[playerIdx]->dealtCards;
    newPlayer.discardRankSum = players[playerIdx]->discardRankSum;
    newPlayer.isHuman = false;
    players[playerIdx] = &newPlayer;
}
