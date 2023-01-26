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


    /**
    * @param fen a fen object
    * @return a string representing the the fen's board in the format needed by the exercise
    */
    static std::string buildBoardString(FEN & fen);

    /**
    * @param c the piece mark (from the FEN representation)
    * @param dark piece is on a dark color sqr
    * @return the string representing the sqr
    */
    static std::string pieceCode(char c, bool dark);

    /**
     * prints the move dialog: printing the state of the gae and asking for a move
    * @param fen
    * @param check is the king checked
    * @return the user imputed move string
    */
    static std::string printMoveDialog(FEN & fen, bool check, const std::string& whiteName, const std::string& blackName);

    /**
     * prints the crowning dialog: prints the crowning options
    * @param white is the piece white
    * @return the user imputed new piece mark
    */
    static char printCrowningDialog(bool white);

    static std::string warningMsg(const std::string& msg);
};


#endif //ITAI_CHESS_SCREEN_H
