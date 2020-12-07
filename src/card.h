#ifndef CARD
#define CARD

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
        char* getName();
};

class InvalidCardData {};

#endif
