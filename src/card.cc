#include "card.h"

Card::Card() {
    // defaut, not intended for significant use
    suite = '\0';
    value = '\0';
}

Card::Card(char value, char suite) {
    setValue(value);
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
            throw InvalidCardData{};
            break;
        }
    }
}

std::string Card::getName() {
    std::string name = "";
    name += value;
    name += suite;
    return name;
}

bool Card::operator==(const Card &other) const {
    if (this->suite != other.suite) {
        return false;
    } else if (this->value != other.value) {
        return false;
    }
    return true;
}

int Card::suiteToEnum(char suite) {
    switch (suite)
    {
    case 'C':
        return 0;
        break;
    case 'D':
        return 1;
        break;
    case 'H':
        return 2;
        break;
    case 'S':
        return 3;
        break;
    default:
        throw InvalidCardData{};
        break;
    }
}
