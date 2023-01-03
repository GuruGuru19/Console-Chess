//
// Created by itai on 1/3/23.
//

#include "Pawn.h"

bool Pawn::canMoveGeo(std::string next_position) {
    if (isWhite()){
        bool option1 = this->position[1] == '2' && next_position[0] == this->position[0] && next_position[1] == '4'; // two steps
        bool option2 = next_position[0] == this->position[0] && next_position[1] == this->position[1] + 1; // one step
        bool option3 = next_position[0] == this->position[0] - 1 && next_position[1] == this->position[1] + 1;// eat left
        bool option4 = next_position[0] == this->position[0] + 1 && next_position[1] == this->position[1] + 1; // eat right
    }
}
