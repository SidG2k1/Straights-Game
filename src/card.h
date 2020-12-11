#ifndef CARD
#define CARD

// array is included here because Card is eventually included in all files, making array 
//  effectively universally accessible
#include <array>

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
