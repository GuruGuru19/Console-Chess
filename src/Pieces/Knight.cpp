//
// Created by itai on 1/3/23.
//

#include "Knight.h"

Knight::Knight(std::string start, bool white) {
    this->mark = white?'N':'n';
    this->position = start;
    this->white = white;
}

bool Knight::canMoveGeo(std::string next_position) {
    int x_move_size = abs(this->position[0] - next_position[0]);
    int y_move_size = abs(this->position[1] - next_position[1]);

    return (x_move_size == 1 && y_move_size == 2) || (x_move_size == 2 && y_move_size == 1);
}
