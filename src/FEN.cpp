//
// Created by itai on 1/3/23.
//

#include "../include/FEN.h"

FEN::FEN(std::string str) { // assumes the str is valid
    int i = 0;
    char c;
    while(this->positions.size() < 64){
        c = str[i];
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
    i++; //for the space
    // CR: as you know where the sectioning will happen each time in the FEN (in the space), would have tried to section
    // in start to different parts and give them meaningful names
    str = str.substr(i);
    i = 0;

    c = str[i];
    i++;

    this->whiteTurn = c == 'w';// c can be 'w' or 'b'
    i++;//for the space
    str = str.substr(i);
    i = 0;

    white_oo_castling = false;
    white_ooo_castling = false;
    black_oo_castling = false;
    black_ooo_castling = false;
    std::string castling = str.substr(0,str.find(' '));
    // CR: can you think of better way to implement this?
    if (castling[0] != '-'){
        while (!castling.empty()){
            // CR: why use erase and not iterate over the string?
            c = castling[0];
            castling.erase(0,1);
            // CR: could be done in switch-case
            if (c == 'K'){
                this->white_oo_castling = true;
            }
            else if (c == 'Q'){
                this->white_ooo_castling = true;
            }
            else if (c == 'k'){
                this->black_oo_castling = true;
            }
            else if (c == 'q'){
                this->black_ooo_castling = true;
            }
        }
    }
//    if (castling[0] != '-'){
//        this->white_oo_castling = castling.find('K') < castling.size();
//        this->white_ooo_castling = castling.find('Q') < castling.size();
//        this->black_oo_castling = castling.find('k') < castling.size();
//        this->black_ooo_castling = castling.find('q') < castling.size();
//    }
    i += str.find(' ') + 1;//for the space
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

