#include "board.h"

Board::Board() {
    // initializes the board.
    for (int i = 0; i < 4; ++i) {
        Card* newSuiteList[13];
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
            std::cout << "Please make your selection again\n>";
        }
        if (playerType == "h") {
            HumanPlayer player;
            players[i] = player;
        } else if (playerType == "c") {
            ComputerPlayer player;
            players[i] = player;
        }
    }
}

bool Board::isLegal(Card card) {
    if (card.getRank() == 7) {return true;}
    else {
        Card** deck = table[card.suiteToEnum(card.getSuite())];
        int cardIdx = card.getRank() - 1;
        if (cardIdx == 12 && deck[11] != nullptr) {
            // king case
            return true;
        } else if (cardIdx == 0 && deck[1] != nullptr) {
            // ace case
            return true;
        } else if (cardIdx >= 1 && cardIdx <= 11) {
            // 2 <= Card <= Queen
            if (deck[cardIdx + 1] != nullptr) {
                return true;
            } else if (deck[cardIdx - 1] != nullptr) {
                return true;
            }
        }
        return false;
    }
}

void Board::printDeck() {
    for (int i = 0; i < 52; ++i) {
        std::cout << deck[i].getName() << " ";
        if ((i != 0) && (i%13 == 0)) {std::cout << std::endl;}
    }
}

void Board::rageQuit(Player* player) {
    int playerIdx = 0;
    for (int i = 0; playerIdx <= 4; ++playerIdx) {
        if (players[playerIdx].dealtCards == player->dealtCards) {
            // Dealt Cards is uniquely identifying
            break;
        }
    }
    ComputerPlayer newPlayer;
    newPlayer.currBoard = this;
    newPlayer.dealtCards = players[playerIdx].dealtCards;
    newPlayer.discardRankSum = players[playerIdx].discardRankSum;
    newPlayer.isHuman = false;
    players[playerIdx] = newPlayer;
}