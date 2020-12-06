#ifndef ACTION
#define ACTION

#include "card.h"

// this class can easily be a struct instead, but this setup allows for more consistency
class Action {
    public:
        Card card;
        bool isPlay;
        bool isDiscard;
        bool isQuit;
};

#endif
