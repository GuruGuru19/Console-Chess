//
// Created by itai on 1/3/23.
//

#ifndef ITAI_CHESS_ROOK_H
#define ITAI_CHESS_ROOK_H

#include <string>
#include "../Piece.h"

class Rook : public Piece{
public:
    Rook(std::string start, bool white);

    bool canMoveGeo(std::string next_position) override;
    // doesn't need canMoveGeoToEat()
    std::string getPath(std::string next_position) override;
    std::string getGeoPossibleMoves() override;
};


#endif //ITAI_CHESS_ROOK_H
