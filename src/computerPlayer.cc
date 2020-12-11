#include "computerPlayer.h"

Action ComputerPlayer::getAction(std::vector<std::array<Card*, 13>> table) {
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
    act.isDiscard = true;
    act.card = dealtCards[0];
    return act;
}
