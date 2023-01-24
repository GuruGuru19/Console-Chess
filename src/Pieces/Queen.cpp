//
// Created by itai on 1/3/23.
//

#include "../../include/Pieces/Queen.h"
#include "../../include/Pieces/Bishop.h"
#include "../../include/Pieces/Rook.h"

Queen::Queen(std::string start, bool white) : Piece(start, white) {
    this->mark = white? 'Q' : 'q';
}

bool Queen::canMoveGeo(std::string next_position) {
    int x_move_size = abs(this->position[0] - next_position[0]);
    int y_move_size = abs(this->position[1] - next_position[1]);

    bool bishop_logic = x_move_size == y_move_size && x_move_size != 0;
    bool rook_logic = (x_move_size > 0 && y_move_size == 0) || (x_move_size == 0 && y_move_size > 0);

    return bishop_logic || rook_logic;
}

std::string Queen::getPath(std::string next_position) {
    if (!this->canMoveGeo(next_position)){
        return "";
    }

    int x_move = next_position[0] - this->position[0];
    int y_move = next_position[1] - this->position[1];
    int x_dir;
    int y_dir;

    bool bishop_logic = abs(x_move) == abs(y_move) && abs(x_move) != 0;
    if (bishop_logic){
        x_dir = x_move/abs(x_move);
        y_dir = y_move/abs(y_move);
    }
    else{
        x_dir = x_move == 0 ? 0 : x_move/abs(x_move);
        y_dir = y_move == 0 ? 0 : y_move/abs(y_move);
    }
    std::string moves;
    for (int n = 1; n < std::max(abs(x_move), abs(y_move)); ++n) {
        char x = (char)(this->position[0] + n * x_dir);
        char y = (char)(this->position[1] + n * y_dir);
        std::string newPos; newPos+=x; newPos+=y;
        moves.append(newPos);
    }
    return moves;
}

std::string Queen::getGeoPossibleMoves() {
    // CR: this is not optimal in my opinion
    Bishop * bishop = new Bishop(this->position, true);
    Rook * rook = new Rook(this->position, true);
    std::string positions;
    positions.append(bishop->getGeoPossibleMoves());
    positions.append(rook->getGeoPossibleMoves());
    delete bishop; delete rook;
    return positions;
}
