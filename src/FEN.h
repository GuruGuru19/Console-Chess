//
// Created by itai on 1/3/23.
//

#ifndef ITAI_CHESS_FEN_H
#define ITAI_CHESS_FEN_H


#include <string>

class FEN {
private:
    std::string positions;

    char activeColor;

    bool white_oo_castling;
    bool white_ooo_castling;
    bool black_oo_castling;
    bool black_ooo_castling;

    std::string enPassant;

    int halfmoveClock;
    int fullmoveNumber;
public:
    FEN(std::string str);

    std::string getPositions(){
        return this->positions;
    };
    char getActiveColor() const{
        return this->activeColor;
    };
    bool getWooCastling() const{
        return this->white_oo_castling;
    }
    bool getWoooCastling() const{
        return this->white_ooo_castling;
    }
    bool getBooCastling() const{
        return this->black_oo_castling;
    }
    bool getBoooCastling() const{
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
};


#endif //ITAI_CHESS_FEN_H
