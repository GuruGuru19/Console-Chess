//
// Created by itai on 1/3/23.
//

#include "../../include/Pieces/Rook.h"

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

std::string Rook::getPath(std::string next_position) {
    if (!canMoveGeo(next_position)){
        return "";
    }
    std::string moves;
    int x_move = next_position[0] - this->position[0];
    int y_move = next_position[1] - this->position[1];

    int x_dir = x_move == 0 ? 0 : x_move/abs(x_move);
    int y_dir = y_move == 0 ? 0 : y_move/abs(y_move);

    for (int n = 1; n < std::max(abs(x_move), abs(y_move)); ++n) {
        char x = (char)(this->position[0] + n * x_dir);
        char y = (char)(this->position[1] + n * y_dir);
        std::string newPos; newPos+=x; newPos+=y;
        moves.append(newPos);
    }

    return moves;
}

std::string Rook::getGeoPossibleMoves() {
    std::string positions;
    for (char c = '1'; c <= '8'; ++c) {
        std::string pos; pos+=this->position[0]; pos+=c;
        positions.append(pos);
    }
    for (char c = 'a'; c <= 'h'; ++c) {
        std::string pos; pos+=c; pos+=this->position[1];
        positions.append(pos);
    }
    return positions;
}
