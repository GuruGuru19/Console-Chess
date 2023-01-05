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

std::string Bishop::getPath(std::string next_position) {
    std::string moves;
    if (!canMoveGeo(next_position)){
        return moves;
    }

    int x_move = this->position[0] - next_position[0];
    int y_move = this->position[1] - next_position[1];

    int x_dir = x_move/abs(x_move);
    int y_dir = y_move/abs(y_move);

    for (int n = 1; n < abs(x_move); ++n) {
        char x = (char)(this->position[0] + n * x_dir);
        char y = (char)(this->position[1] + n * y_dir);
        std::string newPos; newPos+=x; newPos+=y;
        moves.append(newPos);
    }

    return moves;
}
