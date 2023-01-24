//
// Created by itai on 1/3/23.
//

#ifndef ITAI_CHESS_FEN_H
#define ITAI_CHESS_FEN_H


#include <string>
#include "Piece.h"

class FEN {
private:
    // CR: explanation
    //all the positions in a 64 long string, ' ' is an empty sqr and every other piece is represented by its mark from the fen
    std::string positions;

    // read about Forsyth–Edwards Notation https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
    bool whiteTurn;

    bool white_oo_castling;
    bool white_ooo_castling;
    bool black_oo_castling;
    bool black_ooo_castling;

    std::string enPassant;

    int halfmoveClock;
    int fullmoveNumber;
public:
    // CR: better to receive a const string.
    //constructor
    FEN(std::string str);
    //copy constructor
    FEN(FEN & other);

    std::string getPositions(){
        return this->positions;
    };
    bool isWhiteTurn() const{
        return this->whiteTurn;
    };

    bool canWooCastle() const{
        return this->white_oo_castling;
    }
    bool canWoooCastle() const{
        return this->white_ooo_castling;
    }
    bool canBooCastle() const{
        return this->black_oo_castling;
    }
    bool canBoooCastle() const{
        return this->black_ooo_castling;
    }
    std::string getEnPassant(){
        return this->enPassant;
    }
    int getHalfMoveClock() const{
        return this->halfmoveClock;
    }
    int getFullMoveNumber() const{
        return this->fullmoveNumber;
    }

    void setWooCastling(bool value){
        this->white_oo_castling = value;
    }
    void setWoooCastling(bool value){
        this->white_ooo_castling = value;
    }
    void setBooCastling(bool value){
        this->black_oo_castling = value;
    }
    void setBoooCastling(bool value){
        this->black_ooo_castling = value;
    }


    /**
    * updates the FEN
     * @param board array of piece pointers representing the board
     * @param enPassant En passant target square
     * @param eat update triggered by a eat move
     * @param stopTime (default = false) dont advance move counts - relevant when you update the FEN twice in one move (crowning)
    */
    void update(Piece ** board, std::string enPassant, bool eat, bool stopTime = false);
};


#endif //ITAI_CHESS_FEN_H
