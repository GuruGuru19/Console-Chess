//
// Created by itai on 1/3/23.
//

#ifndef ITAI_CHESS_KNIGHT_H
#define ITAI_CHESS_KNIGHT_H


#include "../Piece.h"

class Knight : public Piece{
public:
    Knight(std::string start, bool white);

    bool canMoveGeo(std::string next_position) override;
    std::string getPath(std::string next_position) override{
        return "";  //the knight make jumps so their moves don't have paths
    };
    std::string getGeoPossibleMoves() override;
};


#endif //ITAI_CHESS_KNIGHT_H
