#include "board.h"

void Board::resetTable() {
    table.clear();
    for (int i = 0; i < 4; ++i) {
        std::array<Card*, 13> newSuiteList;
        for (int j = 0; j < 13; ++j) {newSuiteList[j] = nullptr;}
        table.push_back(newSuiteList);
    }
}

Board::Board() {
    // initializes the board
    resetTable();
    initPlayers();
}

void Board::initPlayers() {
    for (int i = 0; i < 4; ++i) {
        std::cout << "Is Player" << i + 1 << "  a human (h) or a computer (c)?" << std::endl;
        std::cout << ">";
        std::string playerType = "";
        while ((!(std::cin >> playerType)) || (playerType != "h" && playerType != "c" && playerType != "")) {
            // this is not in spec, but makes it more robust
            if (playerType == "") {
                // Ctrl-D Quit Signal
                throw QuitSignal{};
            }
            std::cout << "Please make your selection again: Can't interpret " << playerType << ".\n>";
        }
        if (playerType == "h") {
            auto newPlayer = std::make_shared<HumanPlayer>();
            auto player = newPlayer.get();
            player->currBoard = this;
            player->discardRankSum = 0;
            player->isHuman = true;
            players[i] = newPlayer;
        } else if (playerType == "c") {
            auto newPlayer = std::make_shared<ComputerPlayer>();
            auto player = newPlayer.get();
            player->currBoard = this;
            player->discardRankSum = 0;
            player->isHuman = false;
            players[i] = newPlayer;
        }
    }
}

void Board::printDeck() {
    for (int i = 1; i <= 52; ++i) {
        std::cout << shuffledDeck[i - 1].getName() << " ";
        if ((i != 0) && (i%13 == 0)) {std::cout << std::endl;}
    }
}

void Board::rageQuit(int playerIdx) {
    std::cout << "Player" << playerIdx + 1 << " ragequits. A computer will now take over." << std::endl;

    auto newPlayer = std::make_shared<ComputerPlayer>();
    newPlayer.get()->currBoard = this; // which is equal to player.currBoard
    newPlayer.get()->dealtCards = players[playerIdx]->dealtCards;
    newPlayer.get()->discardRankSum = players[playerIdx]->discardRankSum;
    newPlayer.get()->isHuman = false;
    players[playerIdx] = newPlayer;
}

void Board::shuffleDeck(int seed) {
    auto rng = std::default_random_engine{seed};
    std::shuffle(std::begin(shuffledDeck), std::end(shuffledDeck), rng);
}

void Board::dealCards() {
    for (int playerIdx = 0; playerIdx < 4; ++playerIdx) {
        players[playerIdx]->dealtCards.clear();
        for (int cardNum = 0; cardNum < 13; ++cardNum) {
            players[playerIdx]->dealtCards.push_back(shuffledDeck.at(13 * playerIdx + cardNum));
        }
    }
}

int Board::maxDiscardSum() {
    int maxSum = 0;
    for (int i = 0; i < 4; ++i) {
        int playerSum = players[i].get()->discardRankSum;
        if (playerSum > maxSum) {
            maxSum = playerSum;
        }
    }
    return maxSum;
}

char rankToValue(int rank) {
    if (rank == 1) {return 'A';}
    if (rank == 10) {return 'T';}
    if (rank == 11) {return 'J';}
    if (rank == 12) {return 'Q';}
    if (rank == 13) {return 'K';}
    return ('1' + rank - 1);
}

char enumToSuite(int suiteNum) {
    if (suiteNum == 0) {return 'C';}
    if (suiteNum == 1) {return 'D';}
    if (suiteNum == 2) {return 'H';}
    if (suiteNum == 3) {return 'S';}
    throw InvalidCardData{};
}

void Board::start(int seed) {

    // Fill Board::shuffledDeck
    for (int suite = 0; suite < 4; ++suite) {
        for (int rank = 1; rank <= 13; ++rank) {
            Card card{rankToValue(rank), enumToSuite(suite)};
            shuffledDeck.push_back(card);
        }
    }

    while (maxDiscardSum() < 80) {
        shuffleDeck(seed);
        dealCards();

        int playerIdxWith7S = 0;
        Card sevenSpades{'7', 'S'};
        // searching for the player which "owns" a 7 of Spades.
        for (int i = 0; i < 4; ++i) {
            bool found = false;
            for (int j = 0; j < 13; ++j) {
                Card card = players[i].get()->dealtCards[j];
                if (card == sevenSpades) {
                    playerIdxWith7S = i;
                    found = true;
                    break;
                }
            }
            if (found) {break;}
        }

        std::cout << "A new round begins. It's Player" << playerIdxWith7S + 1 << "'s turn to play." << std::endl;

        int currentPlayerIdx = playerIdxWith7S;
        // play game until cards run out
        while (players[currentPlayerIdx].get()->dealtCards.size() != 0) {
            // ^^^^^ Not all cards have been played yet by the player. (when this statement
            // evaluates to false, all players have played all cards.)
            bool printTable = true;
            while (true) {
                Action act = players[currentPlayerIdx].get()->getAction(table, printTable);
                // Consider throwing a "QuitSignal"

                if (act.isPlay) {
                    std::cout << "Player" << currentPlayerIdx + 1 << " plays " << act.card.getName() << ".\n";

                    // add card to table
                    auto card = std::make_shared<Card>();
                    card.get()->setSuite(act.card.getSuite());
                    card.get()->setValue(act.card.getValue());

                    smartCardPtrStore.push_back(card); // so that card doesn't get destroyed
                    table[Card::suiteToEnum(act.card.getSuite())][act.card.getRank() - 1] = card.get();

                    auto dealtCards = &(players[currentPlayerIdx].get()->dealtCards);

                    // remove card from player deck
                    int deckSize = dealtCards->size();
                    for (int i = 0; i < deckSize; ++i) {
                        if ((*dealtCards)[i] == *card.get()) {
                            dealtCards->erase(dealtCards->begin() + i);
                        }
                    }
                    break;
                } 
                else if (act.isDiscard) {
                    std::cout << "Player" << currentPlayerIdx + 1 << " discards " << act.card.getName() << ".\n";
                    // Add card's rank to the players discard sum
                    players[currentPlayerIdx].get()->discardRankSum += act.card.getRank();

                    auto dealtCards = &(players[currentPlayerIdx].get()->dealtCards);

                    // remove card from player deck
                    int deckSize = dealtCards->size();
                    for (int i = 0; i < deckSize; ++i) {
                        if ((*dealtCards)[i] == act.card) {
                            dealtCards->erase(dealtCards->begin() + i);
                        }
                    }
                    playerDiscardStash[currentPlayerIdx].push_back(act.card);
                    break;
                } 
                else if (act.isQuit) {
                    throw QuitSignal{};
                    break;
                } 
                else if (act.isRageQuit) {
                    rageQuit(currentPlayerIdx);
                    // break; // No break since computer need to play
                } 
                else if (act.isDeck) {
                    printDeck();
                    printTable = false;
                }
            }
            currentPlayerIdx = (currentPlayerIdx + 1) % 4;
        }
        
        // End of round summary
        for (int i = 0; i < 4; ++i) {
            int thisRoundScore = 0;
            std::cout << "Player" << i + 1 << "'s discards: ";
            for (Card discard : playerDiscardStash[i]) {
                std::cout << discard.getName() << " ";
                thisRoundScore += discard.getRank();
            }
            std::cout << std::endl;

            std::cout << "Player" << i + 1 << "'s score: ";

            // Sum of previous rounds' scores
            std::cout << players[i].get()->discardRankSum - thisRoundScore;

            for (Card discard : playerDiscardStash[i]) {std::cout << " + " << discard.getRank();}
            std::cout << " = " << players[i].get()->discardRankSum << std::endl;

            // clear discard list
            playerDiscardStash[i].clear();
        }
        
        // clear table
        resetTable();
    }

    // End of game summary (i.e. state winner(s))
    int minScore = INT32_MAX; // larger than any possible discardRankSum
    for (int playerIdx = 0; playerIdx < 4; ++playerIdx) {
        int playerScore = players[playerIdx].get()->discardRankSum;
        if (playerScore < minScore) {
            minScore = playerScore;
        }
    }

    for (int playerIdx = 0; playerIdx < 4; ++playerIdx) {
        if (players[playerIdx].get()->discardRankSum == minScore) {
            std::cout << "Player" << playerIdx + 1 << " wins!" << std::endl;
        }
    }
}
