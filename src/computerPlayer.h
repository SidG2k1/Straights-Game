#ifndef COMPUTER_PLAYER
#define COMPUTER_PLAYER

#include "player.h"

class ComputerPlayer: public Player {
    private:
    public:
        // Since this is a computer, it will only return Actions which
        //   are plays or discards
        Action getAction(std::vector<std::array<Card*, 13>> table) override;
};

#endif
