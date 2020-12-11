#include "computerPlayer.h"

Action ComputerPlayer::getAction(std::vector<Card*[13]> table) {
    // currently plays the first availabe action (tries all plays first then dicards)
    Action act;
    for (Card card : dealtCards) {
        if (isLegal(table, card)) {
            act.card = card;
            act.isPlay = true;
            return act;
        }
    }
    // now needs to discard
    // FIXME: In case of len(dealtCards) = 0; the game should finish
    act.isDiscard = true;
    act.card = dealtCards[0];
    // dealtCards.erase(dealtCards.begin());   //// Should do this in Action handler
    return act;
}
