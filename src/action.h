#ifndef ACTION
#define ACTION

#include "card.h"

// this class can easily be a struct instead, but this setup allows for more consistency
class Action {
    public:
        Action();
        Card card;
        bool isPlay = false;
        bool isDiscard = false;
        bool isQuit = false;
        bool isRageQuit = false;
        bool isDeck = true;
};

#endif
