//
// Created by itai on 1/3/23.
//

#include "../../include/Pieces/Knight.h"

Knight::Knight(std::string start, bool white) : Piece(start, white) {
    this->mark = white?'N':'n';
}

bool Knight::canMoveGeo(std::string next_position) {
    int x_move_size = abs(this->position[0] - next_position[0]);
    int y_move_size = abs(this->position[1] - next_position[1]);

    return (x_move_size == 1 && y_move_size == 2) || (x_move_size == 2 && y_move_size == 1);
}

std::string Knight::getGeoPossibleMoves() {
    std::string positions = "1122334455667788";
    positions[0] = (char)(this->position[0]+1);
    positions[1] = (char)(this->position[1]+2);

    positions[2] = (char)(this->position[0]-1);
    positions[3] = (char)(this->position[1]+2);

    positions[4] = (char)(this->position[0]+2);
    positions[5] = (char)(this->position[1]+1);

    positions[6] = (char)(this->position[0]-2);
    positions[7] = (char)(this->position[1]+1);


    positions[8] = (char)(this->position[0]+1);
    positions[9] = (char)(this->position[1]-2);

    positions[10] = (char)(this->position[0]-1);
    positions[11] = (char)(this->position[1]-2);

    positions[12] = (char)(this->position[0]+2);
    positions[13] = (char)(this->position[1]-1);

    positions[14] = (char)(this->position[0]-2);
    positions[15] = (char)(this->position[1]-1);

    return positions;
}

