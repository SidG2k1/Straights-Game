#ifndef ACTION
#define ACTION

#include "card.h"

// this class can easily be a struct instead, but this setup allows for more consistency
class Action {
    public:
        Action();
        ~Action() {}

        // The card associated with this action
        Card card;
        
        bool isPlay = false;
        bool isDiscard = false;
        bool isQuit = false;
        bool isRageQuit = false;
        bool isDeck = false;
        bool isTired = false;
};

#endif
