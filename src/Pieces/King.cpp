//
// Created by itai on 1/3/23.
//

#include "../../include/Pieces/King.h"

King::King(std::string start, bool white) {
    this->mark = white?'K':'k';
    this->position = start;
    this->white = white;
}

bool King::canMoveGeo(std::string next_position) {
    int x_move_size = abs(this->position[0] - next_position[0]);
    int y_move_size = abs(this->position[1] - next_position[1]);

    return x_move_size < 2 && y_move_size < 2 && !(x_move_size == 0 && y_move_size == 0);
}

std::string King::getGeoPossibleMoves() {
    std::string positions;
    if (isWhite() && this->position == "e1"){
        positions.append("g1");
        positions.append("c1");
    } else if (!isWhite() && this->position == "e8"){
        positions.append("g8");
        positions.append("c8");
    }
    std::string empty;
    positions.append(empty + (char)(this->position[0] - 1) + (char)(this->position[1] - 1)); // - -
    positions.append(empty + (char)(this->position[0] - 1) + (char)(this->position[1])); // - 0
    positions.append(empty + (char)(this->position[0] - 1) + (char)(this->position[1] + 1)); // - +
    positions.append(empty + (char)(this->position[0]) + (char)(this->position[1] + 1)); // 0 +
    positions.append(empty + (char)(this->position[0] + 1) + (char)(this->position[1] + 1)); // + +
    positions.append(empty + (char)(this->position[0] + 1) + (char)(this->position[1])); // + 0
    positions.append(empty + (char)(this->position[0] + 1) + (char)(this->position[1] - 1)); // + -
    positions.append(empty + (char)(this->position[0]) + (char)(this->position[1] - 1)); // 0 -

    return positions;
}
