//
// Created by itai on 1/3/23.
//

#include "../../include/Pieces/Pawn.h"

Pawn::Pawn(std::string start, bool white) : Piece(start, white) {
    this->mark = white? 'P' : 'p';
}

// CR: long conditions
bool Pawn::canMoveGeo(std::string next_position) {
    if (next_position[0] != this->position[0]){
        return false;
    }

    if (next_position[1] == this->position[1] + (isWhite() ? 1 : -1)){
        return true;
    }
    else if (isWhite()){
        return this->position[1] == '2'  && next_position[1] == '4'; // two steps
    }
    else{
        return this->position[1] == '7' && next_position[1] == '5'; // two steps
    }
}

bool Pawn::canMoveGeoToEat(std::string & next_position) {
    // CR: cna be shortened
    if (isWhite()){
        bool w_option3 = next_position[0] == this->position[0] - 1 && next_position[1] == this->position[1] + 1;// eat left
        bool w_option4 = next_position[0] == this->position[0] + 1 && next_position[1] == this->position[1] + 1; // eat right
        return w_option3 || w_option4;
    }
    else{
        bool b_option3 = next_position[0] == this->position[0] - 1 && next_position[1] == this->position[1] - 1;// eat left
        bool b_option4 = next_position[0] == this->position[0] + 1 && next_position[1] == this->position[1] - 1; // eat right
        return b_option3 || b_option4;
    }
}

std::string Pawn::getPath(std::string next_position) {
    bool two_step = (this->position[1] == '2' && next_position[0] == this->position[0] && next_position[1] == '4') ||
            (this->position[1] == '7' && next_position[0] == this->position[0] && next_position[1] == '5'); // two steps
    std::string middle;
    if (two_step && isWhite()){
        middle+=next_position[0]; middle += '3';
    }
    else if(two_step){
        middle+=next_position[0]; middle += '6';
    }
    return middle;
}

std::string Pawn::getGeoPossibleMoves() {
    if (isWhite()){
        // CR: too long
        std::string positions = "11223344";
        // one step
        positions[0] = this->position[0];
        positions[1] = (char)(this->position[1] + 1);
        // two steps
        positions[2] = this->position[0];
        positions[3] = (char)(this->position[1] + 2);
        // eat right
        positions[4] = (char)(this->position[0] + 1);
        positions[5] = (char)(this->position[1] + 1);
        // eat left
        positions[6] = (char)(this->position[0] - 1);
        positions[7] = (char)(this->position[1] + 1);
        return positions;

    } else{
        std::string positions = "11223344";
        // one step
        positions[0] = this->position[0];
        positions[1] = (char)(this->position[1] - 1);
        // two steps
        positions[2] = this->position[0];
        positions[3] = (char)(this->position[1] - 2);
        // eat left
        positions[4] = (char)(this->position[0] + 1);
        positions[5] = (char)(this->position[1] - 1);
        // eat right
        positions[6] = (char)(this->position[0] - 1);
        positions[7] = (char)(this->position[1] - 1);
        return positions;
    }
}
