#include "humanPlayer.h"

bool HumanPlayer::existsLegalPlay(Board* board, std::vector<Card> cards, std::vector<Card*[13]> table) {
    for (Card card: cards) {
        if (isLegal(table, card)) {return true;}
    }
    return false;
}

Action HumanPlayer::getAction(std::vector<Card*[13]> table) {
    // FIXME: In case of len(dealtCards) = 0; the round should be ending
    Action act;
    if (toPrintState) { printState(table);}
    std::cout << ">"; // awaiting user input
    std::string command;
    std::cin >> command;

    if (command == "play") {
        std::string card;
        std::cin >> card;
        Card ccard{card[0], card[1]};
        if (isLegal(table, ccard)) {
            act.card = ccard;
            act.isPlay = true;
        } else {
            toPrintState = false;
            std::cout << "This is not a legal play.\n";
            act = getAction(table);
        }
    } else if (command == "ragequit") {
        act.isRageQuit = true;
    } else if (command == "discard") {
        std::string card;
        std::cin >> card;
        Card ccard{card[0], card[1]};
        if (!existsLegalPlay(currBoard, dealtCards, table)) {
            act.card = ccard;
            act.isDiscard = true;
        } else {
            toPrintState = false;
            std::cout << "You have a legal play. You may not discard.\n";
            act = getAction(table);
        }
    } else if (command == "deck") {
        act.isDeck = true;
    } else if (command == "quit") {
        act.isQuit = true;
    } else {
        // no valid command given
        std::cout << "Please make your selection again\n";
        toPrintState = false;
        act = getAction(table);
    }
    toPrintState = true;
    return act;
}

void HumanPlayer::printState(std::vector<Card*[13]> table) {
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

void printDeck(Board* board, int suite, std::vector<Card*[13]> table) {
    for (int i = 0; i < 13; ++i) {
        Card* ccard = table.at(suite)[i];
        if (ccard != nullptr) {
            std::cout << ccard->getName() << " ";
        }
    }
    std::cout << std::endl;
}
