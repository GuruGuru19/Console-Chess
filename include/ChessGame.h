//
// Created by itai on 1/3/23.
//

#ifndef ITAI_CHESS_CHESSGAME_H
#define ITAI_CHESS_CHESSGAME_H


#include "Screen.h"
#include "Board.h"
#include <gtest/gtest.h>

class ChessGame {
private:
    Board * board;
    Screen * screen;

    std::string whiteName;
    std::string blackName;

    void gameStart();
    bool gameLoop();
    void gameEnd();

    bool kingMate();
    bool staleMate();

    FRIEND_TEST(ChessGameTest, kingMate1Test);
    FRIEND_TEST(ChessGameTest, kingMate2Test);
    FRIEND_TEST(ChessGameTest, kingMate3Test);
    FRIEND_TEST(ChessGameTest, kingMate4Test);
public:
    ChessGame(std::string & fenstr);
    ~ChessGame();

    void runGame();
};


#endif //ITAI_CHESS_CHESSGAME_H
