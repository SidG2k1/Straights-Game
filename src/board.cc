#include "board.h"

void Board::resetTable() {
    // clears the table and fills with nullptrs
    table.clear();
    for (int i = 0; i < 4; ++i) {
        std::array<Card*, 13> newSuiteList;
        for (int j = 0; j < 13; ++j) {newSuiteList[j] = nullptr;}
        table.push_back(newSuiteList);
    }
}

Board::Board(bool enableBonus) {
    // initializes the board
    this->enableBonus = enableBonus;
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
        
        std::shared_ptr<Player> newPlayer;

        if (playerType == "h") {
            newPlayer = std::make_shared<HumanPlayer>();
            newPlayer.get()->isHuman = true;
        }
        else if (playerType == "c") {
            if (enableBonus) {
                newPlayer = std::make_shared<SmartComputer>();
            } else {
                newPlayer = std::make_shared<ComputerPlayer>();
            }
            newPlayer.get()->isHuman = false;
        }

        // all players have the same following properties:
        newPlayer->currBoard = this;
        newPlayer->discardRankSum = 0;
        players[i] = newPlayer;
    }
}

void Board::printDeck() {
    for (int i = 1; i <= 52; ++i) {
        std::cout << shuffledDeck[i - 1].getName() << " ";
        // Create a new line every 13 cards printed:
        if ((i != 0) && (i%13 == 0)) {std::cout << std::endl;}
    }
}

void Board::rageQuit(int playerIdx) {
    std::cout << "Player" << playerIdx + 1 << " ragequits. A computer will now take over." << std::endl;

    std::shared_ptr<Player> newPlayer;

    // Depending on bonus, the player will be replaced by the appropriate computer
    if (enableBonus) {
        newPlayer = std::make_shared<SmartComputer>();
    } else {
        newPlayer = std::make_shared<ComputerPlayer>();
    }

    // Transferring the HumanPlayer's fields to the ComputerPlayer:
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
        // Remove the cards from the player's hand
        players[playerIdx]->dealtCards.clear();
        // Give a contigouous set of 13 cards to the player
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
    // Fill Board::shuffledDeck with ordered cards:
    for (int suite = 0; suite < 4; ++suite) {
        for (int rank = 1; rank <= 13; ++rank) {
            Card card{rankToValue(rank), enumToSuite(suite)};
            shuffledDeck.push_back(card);
        }
    }

    while (maxDiscardSum() < 80) {
        // ^^ keep looping while everyone's score is below 80
        shuffleDeck(seed);
        dealCards();

        int currentPlayerIdx = 0;
        // searching for the player which "owns" a 7 of Spades.
        for (int i = 0; i < 4; ++i) {
            bool found = false;
            for (int j = 0; j < 13; ++j) {
                Card card = players[i].get()->dealtCards[j];
                if (card == Card{'7', 'S'}) {
                    currentPlayerIdx = i;
                    found = true;
                    break;
                }
            }
            if (found) {break;}
        }

        std::cout << "A new round begins. It's Player" << currentPlayerIdx + 1 << "'s turn to play." << std::endl;

        int tiredPlayerIdx = -1;
        int tiredPlayers = 0;
        bool tiredEndRound = false;

        // play game until cards run out
        while (players[currentPlayerIdx].get()->dealtCards.size() != 0) {
            // ^^^^^ Not all cards have been played yet by the player. (when this statement
            // evaluates to false, all players have played all cards.)

            // Improve spacing for easier gameplay
            if (enableBonus) {
                for (int i = 0; i < 6; ++i) {std::cout << std::endl;}
                std::cout << "\nIt is Player" << currentPlayerIdx + 1 << "'s turn:\n";
            }

            bool printTable = true;

            if (tiredPlayerIdx != -1) {
                // someone is tired.
                if (tiredPlayerIdx == currentPlayerIdx) {
                    // have come full circle after poll
                    tiredPlayerIdx = -1; // reset poll state
                    if (tiredPlayers == 4) {
                        tiredEndRound = true; // will end game this round
                        std::cout << "Congratulations, your poll has passed! The game will end this round. ";
                        std::cout << "Please let your co-players know.";
                    } else {
                        std::cout << "Unfortunately not all players are tired, so you will have to keep playing or quit";
                        tiredPlayers = 0;
                    }
                    std::cout << std::endl;
                } else {
                    if (players[currentPlayerIdx].get()->isHuman) {

                        std::cout << "Hi! Just a quick message before you start your turn: \n";
                        std::cout << "Player" << tiredPlayerIdx + 1 << " is tired of the game. Would you like to make this ";
                        std::cout << "the last round?\nType \"y\" for yes and \"n\" for no.\n>";
                        std::string response;
                        std::cin >> response;

                        if (response == "y") {
                            std::cout << "Thanks, noted. Onto your turn:" << std::endl;
                            tiredPlayers++;
                        } else if (response == "n") {
                            std::cout << "Thanks, noted. Onto your turn:" << std::endl;
                        } else {
                            std::cout << "You made a typo... sound like you're tired!" << std::endl;
                            tiredPlayers++;
                        }
                    } else {
                        // Computers vote tired
                        tiredPlayers++;
                    }
                    
                }
            }

            while (true) {
                Action act = players[currentPlayerIdx].get()->getAction(table, printTable);

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
                else if (act.isTired) {
                    if (!enableBonus) {
                        std::cout << "Unfortunaely since you have opted to play without bonuses, ";
                        std::cout << "you will have to sit this one through (or quit)." << std::endl;
                    } else if (tiredPlayerIdx != -1) {
                        std::cout << "A tiredness poll is happening this round. Please wait." << std::endl;
                    } else {
                        // Need to make this round the final round if all other players agree
                        std::cout << "All other human players will be asked if they want to end on this round. ";
                        std::cout << "Meanwhile, please play your turn:" << std::endl;
                        tiredPlayerIdx = currentPlayerIdx;
                        ++tiredPlayers;
                    }
                    printTable = false;
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
            // increment current player
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
        if (tiredEndRound) {break;}
    }

    // End of game summary (i.e. state winner(s))
    int minScore = INT32_MAX; // larger than any possible discardRankSum
    // find the minimum score this game
    for (int playerIdx = 0; playerIdx < 4; ++playerIdx) {
        int playerScore = players[playerIdx].get()->discardRankSum;
        if (playerScore < minScore) {
            minScore = playerScore;
        }
    }

    // print player wins for each person with minscore = score.
    for (int playerIdx = 0; playerIdx < 4; ++playerIdx) {
        if (players[playerIdx].get()->discardRankSum == minScore) {
            std::cout << "Player" << playerIdx + 1 << " wins!" << std::endl;
        }
    }
}
