//
// Created by itai on 1/3/23.
//

#include "../../include/Pieces/Bishop.h"
#include "../../include/Board.h"

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

    std::string moves;

    int x_move = next_position[0] - this->position[0];
    int y_move = next_position[1] - this->position[1];

    int x_dir = x_move/abs(x_move);
    int y_dir = y_move/abs(y_move);

    for (int n = 1; n < abs(x_move); ++n) {
        char x = (char)(this->position[0] + n * x_dir);
        char y = (char)(this->position[1] + n * y_dir);
        std::string newPos;
        newPos+=x;
        newPos+=y;
        moves.append(newPos);
    }

    return moves;
}

std::string Bishop::getGeoPossibleMoves() {
    std::string positions;

    for (int i = 1; i <= 8; ++i) {
        std::string dir1;
        dir1 += (char)(this->position[0] + i);
        dir1 += (char)(this->position[1] + i);
        std::string dir2;
        dir2 += (char)(this->position[0] - i);
        dir2 += (char)(this->position[1] + i);
        std::string dir3;
        dir3 += (char)(this->position[0] - i);
        dir3 += (char)(this->position[1] - i);
        std::string dir4;
        dir4 += (char)(this->position[0] + i);
        dir4 += (char)(this->position[1] - i);
        if (Board::isPositionOnBoard(dir1)){
            positions.append(dir1);
        }
        if (Board::isPositionOnBoard(dir2)){
            positions.append(dir2);
        }
        if (Board::isPositionOnBoard(dir3)){
            positions.append(dir3);
        }
        if (Board::isPositionOnBoard(dir4)){
            positions.append(dir4);
        }
    }

//    std::string diagonal_1_start = this->position;
//    std::string diagonal_2_start = this->position;
//
//    while (diagonal_1_start[0] > 'a' && diagonal_1_start[1] > '1'){ // takes the position as back and down as it can
//        diagonal_1_start[0]-=1;
//        diagonal_1_start[1]+=1;
//    }
//    while (diagonal_2_start[0] > 'a' && diagonal_2_start[1] > '1'){ // takes the position as back and up as it can
//        diagonal_2_start[0]-=1;
//        diagonal_2_start[1]-=1;
//    }
//
//    while (diagonal_1_start[0] <= 'h' && diagonal_1_start[1] <= '8'){ // takes the position as front and up as it can
//        positions.append(diagonal_1_start != this->position ? diagonal_1_start : ""); // adds the positions on the way and ignores this.position
//        diagonal_1_start[0]+=1;
//        diagonal_1_start[1]-=1;
//    }
//    while (diagonal_2_start[0] <= 'h' && diagonal_2_start[1] <= '8'){// takes the position as front and down as it can
//        positions.append(diagonal_2_start != this->position ? diagonal_2_start : ""); // adds the positions on the way and ignores this.position
//        diagonal_2_start[0]+=1;
//        diagonal_2_start[1]+=1;
//    }
    return positions;
}
