//
// Created by itai on 1/3/23.
//

#include "Bishop.h"

Bishop::Bishop(std::string start, bool white) {
    this->mark = white?'B':'b';
    this->position = start;
    this->white = white;
}

bool Bishop::canMoveGeo(std::string next_position) {
    int x_move_size = abs(this->position[0] - next_position[0]);
    int y_move_size = abs(this->position[1] - next_position[1]);

    return x_move_size == y_move_size && x_move_size != 0;
}
