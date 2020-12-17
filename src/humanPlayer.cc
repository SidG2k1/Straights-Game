#include "humanPlayer.h"

bool HumanPlayer::existsLegalPlay(Board* board, std::vector<Card> cards, std::vector<std::array<Card*, 13>> table) {
    for (Card card: cards) {
        if (isLegal(table, card)) {return true;}
    }
    return false;
}

bool inDeck(Card card, std::vector<Card> deck) {
    for (Card deckElem : deck) {
        if (deckElem == card) {
            return true;
        }
    }
    return false;
}

Action HumanPlayer::getAction(std::vector<std::array<Card*, 13>> table, bool printTable) {
    Action act;
    if (printTable) {printState(table);}

    while (true) {
        std::cout << ">"; // awaiting user input
        std::string command;
        std::cin >> command;

        std::string cardName;
        Card ccard;
        if (command == "play") {
            try {
                std::cin >> cardName;
                if (cardName.length() > 2) {throw InvalidCardData{};}
                ccard.setValue(cardName[0]);
                ccard.setSuite(cardName[1]);
            } catch (...) {
                std::cout << "This is not a legal play." << std::endl;
                continue;
            }

            if (!isLegal(table, ccard)) {
                std::cout << "This is not a legal play." << std::endl;
                continue;
            }
            else if (!inDeck(ccard, dealtCards)) {
                std::cout << "This is not a legal play." << std::endl;
                continue;
            }

            act.card = ccard;
            act.isPlay = true;
            break;
        }
        else if (command == "discard") {
            try {
                std::cin >> cardName;
                if (cardName.length() > 2) {throw InvalidCardData{};}
                ccard.setValue(cardName[0]);
                ccard.setSuite(cardName[1]);
            } catch (...) {
                std::cout << "Couldn't read selected card." << std::endl;
                continue;
            }

            if (existsLegalPlay(currBoard, dealtCards, table)) {
                std::cout << "You have a legal play. You may not discard." << std::endl;
                continue;
            }
            else if (!inDeck(ccard, dealtCards)) {
                std::cout << "You don't have this card." << std::endl;
                continue;
            }

            act.card = ccard;
            act.isDiscard = true;
            break;
        }
        else if (command == "deck") {
            act.isDeck = true;
            break;
        }
        else if (command == "imtired") {
            act.isTired = true;
            break;
        }
        else if (command == "quit" || command == "") {
            act.isQuit = true;
            break;
        }
        else if (command == "ragequit") {
            act.isRageQuit = true;
            break;
        }
        else {
            std::cout << "Invalid command: " << command << ". Please make your selection again" << std::endl;
        }
    }
    return act;
}

void printDeck(Board* board, int suite, std::vector<std::array<Card*, 13>> table) {
    for (int i = 0; i < 13; ++i) {
        Card* ccard = table.at(suite)[i];
        if (ccard != nullptr) {
            std::cout << ccard->getValue() << " ";
        }
    }
    std::cout << std::endl;
}

void HumanPlayer::printState(std::vector<std::array<Card*, 13>> table) {
    std::cout << "Cards on the table:" << std::endl;
    std::cout << "Clubs: ";
    printDeck(currBoard, 0, table);
    std::cout << "Diamonds: ";
    printDeck(currBoard, 1, table);
    std::cout << "Hearts: ";
    printDeck(currBoard, 2, table);
    std::cout << "Spades: ";
    printDeck(currBoard, 3, table);

    std::cout << "Your hand: ";
    for (Card ccard : dealtCards) {
        std::cout << ccard.getName() << " ";
    }
    std::cout << std::endl;

    std::cout << "Legal plays: ";
    for (Card card: dealtCards) {
        if (isLegal(table, card)) {
            std::cout << card.getName() << " ";
        }
    }
    std::cout << std::endl;
}
