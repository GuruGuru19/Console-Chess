//
// Created by itai on 1/3/23.
//

#ifndef ITAI_CHESS_CHESSGAME_H
#define ITAI_CHESS_CHESSGAME_H


#include "Screen.h"
#include "Board.h"

class ChessGame {
private:
    Board * board;
    Screen * screen;

    std::string whiteName;
    std::string blackName;

    void gameStart();
    bool gameLoop();
    void gameEnd();

    bool kingMate(bool white_turn);
public:
    ChessGame(std::string & fenstr);
    ~ChessGame();

    void runGame();
};


#endif //ITAI_CHESS_CHESSGAME_H
