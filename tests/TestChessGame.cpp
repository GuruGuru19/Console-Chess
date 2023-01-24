#include <gtest/gtest.h>
#include "../include/ChessGame.h"

// CR: missing tests of chase game
TEST(ChessGameTest, kingMate1Test){
    std::string fen_string = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    ChessGame * chessGame = new ChessGame(fen_string);
    EXPECT_FALSE(chessGame->kingMate());
    EXPECT_FALSE(chessGame->staleMate());
    delete chessGame;
}

TEST(ChessGameTest, kingMate2Test){
    std::string fen_string = "rnb1kbnr/pppp1ppp/8/4p3/6Pq/5P2/PPPPP2P/RNBQKBNR w KQkq - 1 3";
    ChessGame * chessGame = new ChessGame(fen_string);
    EXPECT_TRUE(chessGame->kingMate());
    EXPECT_FALSE(chessGame->staleMate());
    delete chessGame;
}

TEST(ChessGameTest, kingMate3Test){
    std::string fen_string = "r1bqkbnr/p1pp1Qpp/2n5/1p2p3/2B1P3/8/PPPP1PPP/RNB1K1NR b KQkq - 0 4";
    ChessGame * chessGame = new ChessGame(fen_string);
    EXPECT_TRUE(chessGame->kingMate());
    EXPECT_FALSE(chessGame->staleMate());
    delete chessGame;
}

TEST(ChessGameTest, kingMate4Test){
    std::string fen_string = "7k/Q7/3p1p1p/3P1P1P/8/8/8/K5R1 b - - 0 1";
    ChessGame * chessGame = new ChessGame(fen_string);
    EXPECT_FALSE(chessGame->kingMate());
    EXPECT_TRUE(chessGame->staleMate());
    delete chessGame;
}

TEST(ChessGameTest, CrowningTest){
    std::string fen_string = "2k4P/8/8/8/8/8/8/2K5 b - - 0 1";
    ChessGame * chessGame = new ChessGame(fen_string);
    EXPECT_TRUE(!chessGame->Crowning().empty());
    delete chessGame;
}
