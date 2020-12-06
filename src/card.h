#ifndef CARD
#define CARD

#include <string>

class Card {
    private:
        char suite;
        char value;
    public:
        Card(char value, char suite);
        void setSuite(char suite);
        char getSuite();
        void setValue(char value);
        char getValue();
        int getRank();
};

class InvalidCardData {};

#endif
