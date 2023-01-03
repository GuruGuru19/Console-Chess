//
// Created by itai on 1/3/23.
//

#ifndef ITAI_CHESS_PIECE_H
#define ITAI_CHESS_PIECE_H


#include <string>

class Piece {
protected:
    char mark;
    std::string position;
public:
    virtual bool canMoveGeo(std::string next_position) = 0;
    bool move(std::string next_position);
    bool isWhite();
};


#endif //ITAI_CHESS_PIECE_H
