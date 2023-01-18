//
// Created by itai on 1/3/23.
//

#include "../../include/Pieces/King.h"

King::King(std::string start, bool white) : Piece(start, white) {
    this->mark = white?'K':'k';
}

bool King::canMoveGeo(std::string next_position) {
    if (isWhite() && this->position == "e1" && (next_position == "g1" || next_position == "c1")){
        return true;
    } else if (!isWhite() && this->position == "e8" && (next_position == "g8" || next_position == "c8")){
        return true;
    }

    int x_move_size = abs(this->position[0] - next_position[0]);
    int y_move_size = abs(this->position[1] - next_position[1]);

    return x_move_size < 2 && y_move_size < 2 && !(x_move_size == 0 && y_move_size == 0);
}

std::string King::getPath(std::string next_position) {
    if (isWhite() && this->position == "e1"){
        if (next_position == "g1"){
            return "f1";
        }
        if (next_position == "c1") {
            return "d1";
        }
    }
    else if (!isWhite() && this->position == "e8"){
        if (next_position == "g8"){
            return "f8";
        }
        if (next_position == "c8"){
            return "d8";
        }
    }
    return "";
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

int King::isCastling(std::string next_position) {
    if (isWhite() && this->position == "e1" && next_position == "g1"){
        return 1;//w o-o
    }
    else if (isWhite() && this->position == "e1" && next_position == "c1"){
        return 2;//w o-o-o
    }
    else if (!isWhite() && this->position == "e8" && next_position == "g8"){
        return 3;//b o-o
    }
    else if (!isWhite() && this->position == "e8" && next_position == "c8"){
        return 4;//b o-o-o
    }
    return 0;
}
