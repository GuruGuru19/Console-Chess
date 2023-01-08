//
// Created by itai on 1/3/23.
//

#ifndef ITAI_CHESS_KING_H
#define ITAI_CHESS_KING_H

#include <string>
#include "Piece.h"

class King : public Piece{
public:
    King(std::string start, bool white);

    bool canMoveGeo(std::string next_position) override;
    // doesn't need canMoveGeoToEat()
    // doesn't need getPath()
    std::string getGeoPossibleMoves() override;
};


#endif //ITAI_CHESS_KING_H
