//
// Created by itai on 1/3/23.
//

#ifndef ITAI_CHESS_PIECE_H
#define ITAI_CHESS_PIECE_H


#include <string>

// CR: this class should appear outside the pieces directory
class Piece {
protected:
    char mark;
    std::string position;
    bool white;
public:
    // CR: docs
    // constructor
    Piece(std::string start, bool white);

    // returns if the piece can move to (next_position) geometrically
    virtual bool canMoveGeo(std::string next_position) = 0;

    // returns if the piece can move to (next_position) geometrically to eat... relevant for the Pawn
    virtual bool canMoveGeoToEat(std::string & next_position) {
        return canMoveGeo(next_position);
    };

    // CR: not sure if I would make a default implementation in this case
    // returns the positions on the path the piece need to take to (next_position)
    virtual std::string getPath(std::string next_position) {
        return "";  //the knight and king make jumps so their moves don't have paths
    };

    // returns the positions a piece can move geometrically
    virtual std::string getGeoPossibleMoves() = 0;


    bool isWhite() {
        return this->white;
    };

    char getMark(){
        return this->mark;
    };

    void setPosition(std::string new_position){
        this->position = new_position;
    };
    std::string getPosition(){
        return this->position;
    };
};


#endif //ITAI_CHESS_PIECE_H
