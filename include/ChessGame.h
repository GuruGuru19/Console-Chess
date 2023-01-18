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
    // game board
    Board * board;

    //player names
    std::string whiteName;
    std::string blackName;

    /**
    * gets players names
    */
    void gameStart();

    /**
     * game loop
    * @return if the game can continue to an other move
    */
    bool gameLoop();

    /**
    * end game messages
    */
    void gameEnd();

    /**
    * @return if you currently need to crown a pawn
    */
    std::string Crowning();

    /**
    * @return if you currently the king is mated
    */
    bool kingMate();

    /**
    * @return if you currently the king is stale mated
    */
    bool staleMate();


    FRIEND_TEST(ChessGameTest, kingMate1Test);
    FRIEND_TEST(ChessGameTest, kingMate2Test);
    FRIEND_TEST(ChessGameTest, kingMate3Test);
    FRIEND_TEST(ChessGameTest, kingMate4Test);
    FRIEND_TEST(ChessGameTest, CrowningTest);
public:
    // constructor
    ChessGame(std::string & fenstr);

    //destructor
    ~ChessGame();

    // runs the game
    void runGame();
};


#endif //ITAI_CHESS_CHESSGAME_H
