//
// Created by itai on 1/3/23.
//

#include "Queen.h"

Queen::Queen(std::string start, bool white) {
    this->mark = white?'Q':'q';
    this->position = start;
    this->white = white;
}

bool Queen::canMoveGeo(std::string next_position) {
    int x_move_size = abs(this->position[0] - next_position[0]);
    int y_move_size = abs(this->position[1] - next_position[1]);

    bool bishop_logic = x_move_size == y_move_size && x_move_size != 0;
    bool rook_logic = (x_move_size > 0 && y_move_size == 0) || (x_move_size == 0 && y_move_size > 0);

    return bishop_logic && rook_logic;
}

std::string Queen::getPath(std::string next_position) {
    //TODO
}
