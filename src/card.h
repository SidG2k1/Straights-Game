#ifndef CARD
#define CARD

// array is included here because Card is eventually included in all files, making array 
//  universally accessible by all classes
#include <array>
#include <string>

class Card {
    private:
        char suite;
        char value;
    public:
        Card(); // Avoid using if possible

        // Creates a card with the specified value and suite
        Card(char value, char suite);
        ~Card() {}

        void setSuite(char suite);
        char getSuite();
        void setValue(char value);
        char getValue();

        int getRank();

        // represents the colloquial name of the card. (e.g. "7S" for seven of spades)
        std::string getName();

        bool operator==(const Card &other) const;
        
        // Converts from a suite to an enumerated int for ease in vector/array ordering
        static int suiteToEnum(char suite);
};

// thrown whenever there is an invalid data call to the Card.
class InvalidCardData {};

#endif
