#ifndef COMPUTER_PLAYER
#define COMPUTER_PLAYER

#include "player.h"

class ComputerPlayer: public Player {
    private:
    public:
        Action getAction() override;
};

#endif
