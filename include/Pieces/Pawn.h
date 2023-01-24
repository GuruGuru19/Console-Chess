//
// Created by itai on 1/3/23.
//

#ifndef ITAI_CHESS_PAWN_H
#define ITAI_CHESS_PAWN_H


#include <string>
#include "../Piece.h"

class Pawn : public Piece{
public:
    Pawn(std::string start, bool white);
    bool canMoveGeo(std::string next_position) override;
    bool canMoveGeoToEat(std::string & next_position) override;
    std::string getPath(std::string next_position) override;
    std::string getGeoPossibleMoves() override;
};


#endif //ITAI_CHESS_PAWN_H
