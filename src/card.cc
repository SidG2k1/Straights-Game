#include "card.h"

Card::Card(char value, char suite) {
    setSuite(suite);
}

void Card::setSuite(char suite) {
    if (suite == 'C' || suite == 'D' || suite == 'H' || suite == 'S') {
        this->suite = suite;
    } else {
        throw InvalidCardData{};
    }
}

void Card::setValue(char value) {
    if (value >= '2' && value <= '9') {
        this->value = value;
    } else if (value == 'A' || value == 'T' || value == 'J' || value == 'Q' || value == 'K') {
        this->value = value;
    } else {
        throw InvalidCardData{};
    }
}

char Card::getSuite() {return suite;}

char Card::getValue() {return value;}

int Card::getRank() {
    if (value >= '2' && value <= '9') {
        return (value - '0'); // casts to int
    } else {
        switch (value)
        {
        case 'A':
            return 1;
            break;
        case 'T':
            return 10;
            break;
        case 'J':
            return 11;
            break;
        case 'Q':
            return 12;
            break;
        case 'K':
            return 13;
            break;
        default:
            break;
        }
    }
}
