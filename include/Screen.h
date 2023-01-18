//
// Created by itai on 1/3/23.
//

#ifndef ITAI_CHESS_SCREEN_H
#define ITAI_CHESS_SCREEN_H


#include <string>
#include "FEN.h"

class Screen {
private:

public:
    static const std::string COLOR_CLEAR;
    static const std::string WHITE_TEXT;
    static const std::string BLACK_TEXT;
    static const std::string GREEN_BACK;
    static const std::string BLUE_BACK;
    static const std::string RED_BACK;

    static const std::string DARK_BACK;
    static const std::string LIGHT_BACK;

    static std::string buildBoardString(FEN & fen);
    static std::string pieceCode(char c, bool dark);
    static std::string printMoveDialog(FEN & fen, bool check);
    static char printCrowningDialog(bool white);
};


#endif //ITAI_CHESS_SCREEN_H
