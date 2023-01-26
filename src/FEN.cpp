//
// Created by itai on 1/3/23.
//

#include "../include/FEN.h"

FEN::FEN(const std::string& fen_string) { // assumes the str is valid
    std::string str = fen_string;
    std::string in_positions = str.substr(0, str.find_first_of(' '));
    int i = 0;
    char c;
    while(this->positions.size() < 64){
        c = in_positions[i];
        if ((c <= 'z' && c >= 'a')||(c <= 'Z' && c >= 'A')){
            positions += c;
            i++;
        }
        else if (c == '/'){
            i++;
        }
        else if (c <= '8' && c >= '1'){
            int n = ((int)(c - '0'));
            positions += std::string(n, ' ');
            i ++;
            continue;
        }
    }

    str = str.substr(str.find_first_of(' ') + 1); // next section

    c = str[0];
    this->whiteTurn = c == 'w';// c can be 'w' or 'b'

    str = str.substr(str.find_first_of(' ') + 1); // next section

    std::string castling_rights = str.substr(0, str.find_first_of(' '));

    white_oo_castling = castling_rights.find('K') < castling_rights.size();
    white_ooo_castling = castling_rights.find('Q') < castling_rights.size();
    black_oo_castling = castling_rights.find('k') < castling_rights.size();
    black_ooo_castling = castling_rights.find('q') < castling_rights.size();

    str = str.substr(str.find_first_of(' ') + 1); // next section

    c = str[0];
    if (c == '-'){
        this->enPassant = "-";
    } else{
        this->enPassant = str.substr(0, 2);
    }

    str = str.substr(str.find_first_of(' ') + 1); // next section

    int space = str.find(' ');
    std::string halfmove_clock = str.substr(0,space);
    this->halfmoveClock = std::stoi(halfmove_clock);
    std::string fullmove_number = str.substr(space+1);
    this->fullmoveNumber = std::stoi(fullmove_number);
}

FEN::FEN(FEN &other) {
    this->positions = other.positions;

    this->whiteTurn = other.whiteTurn;

    this->white_oo_castling = other.white_oo_castling;
    this->white_ooo_castling = other.white_ooo_castling;
    this->black_oo_castling = other.black_oo_castling;
    this->black_ooo_castling = other.black_ooo_castling;

    this->enPassant = other.enPassant;

    this->halfmoveClock = other.halfmoveClock;
    this->fullmoveNumber = other.fullmoveNumber;
}

void FEN::update(Piece ** board, std::string enPassant, bool eat, bool stopTime) {
    std::string new_positions;
    for (int i = 0; i < 64; ++i) {
        if (board[i] == nullptr){
            new_positions += " ";
        } else{
            new_positions += board[i]->getMark();
        }
    }
    this->positions = new_positions;

    this->whiteTurn = stopTime? this->whiteTurn : !this->whiteTurn;

    this->enPassant = enPassant.size() != 2 ? "-" : enPassant;

    this->halfmoveClock = !stopTime && eat ? 0 : this->halfmoveClock + 1;
    this->fullmoveNumber += !stopTime && this->whiteTurn ? 1 : 0; // if its white now (after it was changed)

}

