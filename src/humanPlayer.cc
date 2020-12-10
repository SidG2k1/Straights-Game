#include "humanPlayer.h"

bool existsLegalPlay(Board* board, std::vector<Card> cards) {
    for (Card card: cards) {
        if (board->isLegal(card)) {return true;}
    }
    return false;
}

Action HumanPlayer::getAction() {
    // FIXME: Consider case of len(dealtCards) = 0
    Action act;
    printState();
    std::cout << "> "; // awaiting user input
    std::string command;
    std::cin >> command;

    if (command == "play") {
        std::string card;
        std::cin >> card;
        Card ccard{card[0], card[1]};
        if (currBoard->isLegal(ccard)) {
            act.card = ccard;
            act.isPlay = true;
        } else {
            std::cout << "Please make your selection again\n";
            act = getAction();
        }
    } else if (command == "ragequit") {
        currBoard->rageQuit(this);
    } else if (command == "discard") {
        std::string card;
        std::cin >> card;
        Card ccard{card[0], card[1]};
        if (!existsLegalPlay(currBoard, dealtCards)) {
            act.card = ccard;
            act.isDiscard = true;
        } else {
            std::cout << "Please make your selection again\n";
            act = getAction();
        }
    } else if (command == "deck") {
        // FIXME: in act handling (up the call stack), 
        //  consider this case where everything is false
        currBoard->printDeck();
    } else if (command == "quit") {
        act.isQuit = true;
    } else {
        // no valid command given
        std::cout << "Please make your selection again\n";
        act = getAction();
    }
    return act;
}

void HumanPlayer::printState() {
    std::cout << "Cards on the table:" << std::endl;
    std::cout << "Clubs: ";
    printDeck(currBoard, 0);
    std::cout << "Diamonds: ";
    printDeck(currBoard, 1);
    std::cout << "Hearts: ";
    printDeck(currBoard, 2);
    std::cout << "Spades: ";
    printDeck(currBoard, 3);

    std::cout << "Your hand: ";
    for (Card ccard : dealtCards) {
        std::cout << ccard.getName() << " ";
    }
    std::cout << std::endl;

    std::cout << "Legal plays: ";
    for (Card card: dealtCards) {
        if (currBoard->isLegal(card)) {
            std::cout << card.getName() << " ";
        }
    }
    std::cout << std::endl;
}

void printDeck(Board* board, int suite) {
    for (int i = 0; i < 13; ++i) {
        Card* ccard = board->table.at(suite)[i];
        if (ccard != nullptr) {
            std::cout << ccard->getName() << " ";
        }
    }
    std::cout << std::endl;
}
