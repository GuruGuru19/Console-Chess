#include <gtest/gtest.h>
#include "../include/FEN.h"
#include "../include/Board.h"

// CR: missing tests for update_fen & fen from other fen
TEST(Test_FEN, correctBuildFEN1Test){
    std::string fen_string = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    FEN * fen = new FEN(fen_string);
    EXPECT_STREQ(fen->getPositions().c_str(), "rnbqkbnrpppppppp                                PPPPPPPPRNBQKBNR");
    EXPECT_TRUE(fen->isWhiteTurn());
    EXPECT_TRUE(fen->canWooCastle());
    EXPECT_TRUE(fen->canWoooCastle());
    EXPECT_TRUE(fen->canBooCastle());
    EXPECT_TRUE(fen->canBoooCastle());
    EXPECT_STREQ(fen->getEnPassant().c_str(), "-");
    delete fen;
}

TEST(Test_FEN, correctBuildFEN2Test){
    std::string fen_string = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2";
    FEN * fen = new FEN(fen_string);
    EXPECT_STREQ(fen->getPositions().c_str(), "rnbqkbnrpp ppppp          p         P        N  PPPP PPPRNBQKB R");
    EXPECT_FALSE(fen->isWhiteTurn());
    EXPECT_TRUE(fen->canWooCastle());
    EXPECT_TRUE(fen->canWoooCastle());
    EXPECT_TRUE(fen->canBooCastle());
    EXPECT_TRUE(fen->canBoooCastle());
    EXPECT_STREQ(fen->getEnPassant().c_str(), "-");
    delete fen;
}

TEST(Test_FEN, correctBuildFEN3Test){
    std::string fen_string = "r1b3nr/pppk2qp/1bnp4/4p1BQ/2BPP3/2P5/PP3PPP/RN3RK1 w - - 1 12";
    FEN * fen = new FEN(fen_string);
    EXPECT_STREQ(fen->getPositions().c_str(), "r b   nrpppk  qp bnp        p BQ  BPP     P     PP   PPPRN   RK ");
    EXPECT_TRUE(fen->isWhiteTurn());
    EXPECT_FALSE(fen->canWooCastle());
    EXPECT_FALSE(fen->canWoooCastle());
    EXPECT_FALSE(fen->canBooCastle());
    EXPECT_FALSE(fen->canBoooCastle());
    EXPECT_STREQ(fen->getEnPassant().c_str(), "-");
    delete fen;
}

TEST(Test_FEN, correctBuildFEN4Test){
    std::string fen_string = "r3k2r/pppq1p1p/2np1bpB/4p3/2PNP2P/1PN3P1/P1P1BP2/1R2K2R b K - 0 14";
    FEN * fen = new FEN(fen_string);
    EXPECT_STREQ(fen->getPositions().c_str(), "r   k  rpppq p p  np bpB    p     PNP  P PN   P P P BP   R  K  R");
    EXPECT_FALSE(fen->isWhiteTurn());
    EXPECT_TRUE(fen->canWooCastle());
    EXPECT_FALSE(fen->canWoooCastle());
    EXPECT_FALSE(fen->canBooCastle());
    EXPECT_FALSE(fen->canBoooCastle());
    EXPECT_STREQ(fen->getEnPassant().c_str(), "-");
    delete fen;
}

TEST(FENTest, updateTest){
    // Board::board is private
}