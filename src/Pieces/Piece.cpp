//
// Created by itai on 1/3/23.
//

#include "Piece.h"

bool Piece::move(std::string next_position) {
    if (this->position == next_position){
        return false;
    }
    this->position = next_position;
    return true;
}
