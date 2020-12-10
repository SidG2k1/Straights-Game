#include "computerPlayer.h"

Action ComputerPlayer::getAction() {
    // currently plays the first availabe action (tries all plays first then dicards)
    Action act;
    for (Card card : dealtCards) {
        if (currBoard->isLegal(card)) {
            act.card = card;
            act.isPlay = true;
            return act;
        }
    }
    // now needs to discard
    // FIXME: Consider case of len(dealtCards) = 0
    act.isDiscard = true;
    act.card = dealtCards[0]; // As mentiond in above FIXME, might throw segfault
    dealtCards.erase(dealtCards.begin());
    return act;
}
