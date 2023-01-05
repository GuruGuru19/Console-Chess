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
    bool white;
public:
    virtual bool canMoveGeo(std::string next_position) = 0;

    virtual bool canMoveGeoToEat(std::string & next_position) {
        return canMoveGeo(next_position);
    };

    virtual std::string getPath(std::string next_position) {
        return "";//the pawn, knight and king make jumps so their moves don't have paths
    };

    bool move(std::string next_position);


    bool isWhite() {
        return this->white;
    };

    char getMark(){
        return this->mark;
    };
};


#endif //ITAI_CHESS_PIECE_H
