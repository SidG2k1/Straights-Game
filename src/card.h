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

        bool operator==(const Card &other) const;

        // FIXME: better implementation exist for the following
        //  method
        static int suiteToEnum(char suite);
};

class InvalidCardData {};

#endif
