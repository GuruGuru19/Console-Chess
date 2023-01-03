//
// Created by itai on 1/3/23.
//

#include "Rook.h"

Rook::Rook(std::string start, bool white) {
    this->mark = white?'R':'r';
    this->position = start;
    this->white = white;
}

bool Rook::canMoveGeo(std::string next_position) {
    int x_move_size = abs(this->position[0] - next_position[0]);
    int y_move_size = abs(this->position[1] - next_position[1]);

    return (x_move_size > 0 && y_move_size == 0) || (x_move_size == 0 && y_move_size > 0);
}
