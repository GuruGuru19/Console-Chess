//
// Created by itai on 1/3/23.
//

#include "../../include/Pieces/Bishop.h"

Bishop::Bishop(std::string start, bool white) : Piece(start, white) {
    this->mark = white? 'B' : 'b';
}

bool Bishop::canMoveGeo(std::string next_position) {
    int x_move_size = abs(this->position[0] - next_position[0]);
    int y_move_size = abs(this->position[1] - next_position[1]);

    return x_move_size == y_move_size && x_move_size != 0;
}

std::string Bishop::getPath(std::string next_position) {
    if (!canMoveGeo(next_position)){
        return "";
    }
    // CR: spacing
    std::string moves;

    int x_move = next_position[0] - this->position[0];
    int y_move = next_position[1] - this->position[1];

    int x_dir = x_move/abs(x_move);
    int y_dir = y_move/abs(y_move);

    // CR: why the ++n?
    for (int n = 1; n < abs(x_move); ++n) {
        char x = (char)(this->position[0] + n * x_dir);
        char y = (char)(this->position[1] + n * y_dir);
        // CR: multiple actions in one line
        std::string newPos; newPos+=x; newPos+=y;
        moves.append(newPos);
    }

    return moves;
}

std::string Bishop::getGeoPossibleMoves() {
    // CR: didn't like that, let's think about other solutions.
    std::string diagonal_1_start = this->position;
    std::string diagonal_2_start = this->position;
    while (diagonal_1_start[0] > 'a' && diagonal_1_start[1] > '1'){ // takes the position as back and down as it can
        diagonal_1_start[0]-=1;
        diagonal_1_start[1]+=1;
    }
    while (diagonal_2_start[0] > 'a' && diagonal_2_start[1] > '1'){ // takes the position as back and up as it can
        diagonal_2_start[0]-=1;
        diagonal_2_start[1]-=1;
    }

    std::string positions;
    while (diagonal_1_start[0] <= 'h' && diagonal_1_start[1] <= '8'){ // takes the position as front and up as it can
        positions.append(diagonal_1_start != this->position ? diagonal_1_start : ""); // adds the positions on the way and ignores this.position
        diagonal_1_start[0]+=1;
        diagonal_1_start[1]-=1;
    }
    while (diagonal_2_start[0] <= 'h' && diagonal_2_start[1] <= '8'){// takes the position as front and down as it can
        positions.append(diagonal_2_start != this->position ? diagonal_2_start : ""); // adds the positions on the way and ignores this.position
        diagonal_2_start[0]+=1;
        diagonal_2_start[1]+=1;
    }
    return positions;
}
