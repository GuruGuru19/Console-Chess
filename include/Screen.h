//
// Created by itai on 1/3/23.
//

#ifndef ITAI_CHESS_SCREEN_H
#define ITAI_CHESS_SCREEN_H


#include <string>
#include "FEN.h"

class Screen {
public:
    static const std::string COLOR_CLEAR;
    static const std::string WHITE_TEXT;
    static const std::string BLACK_TEXT;
    static const std::string GREEN_BACK;
    static const std::string BLUE_BACK;
    static const std::string RED_BACK;

    static const std::string DARK_BACK;
    static const std::string LIGHT_BACK;

    // CR: docs
    /**
    * @param fen a fen object
    * @return a string representing the fen board
    */
    static std::string buildBoardString(FEN & fen);

    /**
    * @param c the piece mark
    * @param dark piece is on a dark color sqr
    * @return the string representing the sqr
    */
    static std::string pieceCode(char c, bool dark);

    /**
     * prints the move dialog
    * @param fen
    * @param check is the king checked
    * @return the user imputed move string
    */
    static std::string printMoveDialog(FEN & fen, bool check);

    /**
     * prints the crowning dialog
    * @param white is the piece white
    * @return the user imputed new piece mark
    */
    static char printCrowningDialog(bool white);
};


#endif //ITAI_CHESS_SCREEN_H
