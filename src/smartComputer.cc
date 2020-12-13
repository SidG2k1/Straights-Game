#include "smartComputer.h"

Action SmartComputer::getAction(std::vector<std::array<Card*, 13>> table, bool printTable) {
    /*
    The Strategy:
    - If there exists a legal play, play the card with the highest rank as to dispose of 
        the high risk of having to discard it
    - If there does not exist a legal play, discard the card with the lowest ranks as to
        add the lowest value to the discard sum, and "live to fight another day" and
        potentially play the high-rank cards later in the round
    */
    Action act;

    bool existsPlay = false;
    int highestRank = -100; // lower than any rank of existing card
    int lowestRank = 100;  // higher than any rank of existing card
    int cardCount = dealtCards.size();
 
    for (int i = 0; i < cardCount; ++i) {
        int cardRank = dealtCards[i].getRank();
        if (isLegal(table, dealtCards[i])) {
            existsPlay = true;
        }
        if (cardRank > highestRank && isLegal(table, dealtCards[i])) {
            // highest card only is valid when legal
            highestRank = cardRank;
        }
        if (cardRank < lowestRank) {
            lowestRank = cardRank;
        }
    }

    for (int i = 0; i < cardCount; ++i) {
        if (existsPlay) {
            if (dealtCards[i].getRank() == highestRank && isLegal(table, dealtCards[i])) {
                act.card = dealtCards[i];
                act.isPlay = true;
                break;
            }
        } else {
            if (dealtCards[i].getRank() == lowestRank) {
                act.card = dealtCards[i];
                act.isDiscard = true;
                break;
            }
        }
    }
 
    return act;
}
