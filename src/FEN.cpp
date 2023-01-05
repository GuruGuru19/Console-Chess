//
// Created by itai on 1/3/23.
//

#include "FEN.h"

FEN::FEN(std::string str) { // assumes the str is valid
    this->positions = "";
    int i = 0;
    char c;
    while(this->positions.size() < 64){
        c = str[i];
        if ((c <= 'z' && c >= 'a')||(c <= 'Z' && c >= 'A')){
            positions += c;
            i++;
            continue;
        }
        if (c == '/'){
            i++;
            continue;
        }
        if (c <= '8' && c >= '1'){
            int n = ((int)(c-'0'));
            for (int j = 0; j < n; ++j) {
                positions += ' ';
            }
            i ++;
            continue;
        }
    }
    i++;//for the space
    str = str.substr(i);
    i = 0;

    c = str[i++];
    this->activeColor = c;// 'w' or 'b'
    i++;//for the space
    str = str.substr(i);
    i = 0;

    c = str[i++];
    this->white_oo_castling = c == 'K';
    c = str[i++];
    this->white_ooo_castling = c == 'Q';
    c = str[i++];
    this->black_oo_castling = c == 'k';
    c = str[i++];
    this->black_ooo_castling = c == 'q';
    i++;//for the space
    str = str.substr(i);
    i = 0;

    c = str[i];
    if (c == '-'){
        this->enPassant = "-";
        i++;
    } else{
        this->enPassant = str.substr(i, 2);
        i+=2;
    }

    i++;//for the space
    str = str.substr(i);
    i = 0;

    int space = str.find(' ');
    std::string halfmove_clock = str.substr(0,space);
    this->halfmoveClock = std::stoi(halfmove_clock);
    std::string fullmove_number = str.substr(space+1);
    this->fullmoveNumber = std::stoi(fullmove_number);
}

FEN::FEN(FEN &other) {
    this->positions = other.positions;

    this->activeColor = other.activeColor;

    this->white_oo_castling = other.white_oo_castling;
    this->white_ooo_castling = other.white_ooo_castling;
    this->black_oo_castling = other.black_oo_castling;
    this->black_ooo_castling = other.black_ooo_castling;

    this->enPassant = other.enPassant;

    this->halfmoveClock = other.halfmoveClock;
    this->fullmoveNumber = other.fullmoveNumber;
}

