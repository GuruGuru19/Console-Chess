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
    std::string getPath(std::string next_position) override;
    std::string getGeoPossibleMoves() override;

    /**
    * @param next_position position to move to
    * @return what type of castling (1-4 woo-booo) returns 0 if its not a castling
    */
    int isCastling(std::string next_position);
};


#endif //ITAI_CHESS_KING_H
