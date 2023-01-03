//
// Created by itai on 1/3/23.
//

#ifndef ITAI_CHESS_PAWN_H
#define ITAI_CHESS_PAWN_H


#include <string>
#include "Piece.h"

class Pawn : public Piece{
public:
    virtual bool canMoveGeo(std::string next_position) override;
};


#endif //ITAI_CHESS_PAWN_H
