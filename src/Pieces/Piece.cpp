//
// Created by itai on 1/3/23.
//

#include "Piece.h"

bool Piece::move(std::string next_position) {
    this->position = next_position;
    return this->position == next_position;
}

bool Piece::isWhite() {
    switch (this->mark) {
        case 'P':
            return true;
        case 'N':
            return true;
        case 'B':
            return true;
        case 'R':
            return true;
        case 'Q':
            return true;
        case 'K':
            return true;
        case 'p':
            return false;
        case 'n':
            return false;
        case 'b':
            return false;
        case 'r':
            return false;
        case 'q':
            return false;
        case 'k':
            return false;
        default:
            throw "NON VALID MARK";
    }
}
