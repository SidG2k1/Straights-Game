#include "player.h"

Player::~Player() {
    // Since following RAII principle, nothing to destroy.
}

bool Player::isLegal(std::vector<std::array<Card*, 13>> table, Card card) {
    if (card.getRank() == 7) {return true;}
    else {
        std::array<Card *, 13> deck = table[card.suiteToEnum(card.getSuite())];
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

Action Player::getAction(std::vector<std::array<Card*, 13>> table) {
    return Action{};
}
