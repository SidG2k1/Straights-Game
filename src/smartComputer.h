#ifndef SMART_PLAYER
#define SMART_PLAYER

#include "player.h"

class SmartComputer: public Player {
    private:
    public:
        // Note: Since this is a computer, it will only return Actions which
        //   are plays or discards
        // This computer uses a more advanced and strategic algorithm for detemining the action
        Action getAction(std::vector<std::array<Card*, 13>> table, bool printTable = true) override;
};

#endif
