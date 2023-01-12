#include <gtest/gtest.h>
#include "../include/FEN.h"

TEST(Test_FEN, correctBuildFEN1Test){
    std::string fen_string = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    FEN * fen = new FEN(fen_string);
    EXPECT_STREQ(fen->getPositions().c_str(), "rnbqkbnrpppppppp                                PPPPPPPPRNBQKBNR");
    EXPECT_EQ(fen->getActiveColor(), 'w');
    EXPECT_TRUE(fen->getWooCastling());
    EXPECT_TRUE(fen->getWoooCastling());
    EXPECT_TRUE(fen->getBooCastling());
    EXPECT_TRUE(fen->getBoooCastling());
    EXPECT_STREQ(fen->getEnPassant().c_str(), "-");
}

TEST(Test_FEN, correctBuildFEN2Test){
    std::string fen_string = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2";
    FEN * fen = new FEN(fen_string);
    EXPECT_STREQ(fen->getPositions().c_str(), "rnbqkbnrpp ppppp          p         P        N  PPPP PPPRNBQKB R");
    EXPECT_EQ(fen->getActiveColor(), 'b');
    EXPECT_TRUE(fen->getWooCastling());
    EXPECT_TRUE(fen->getWoooCastling());
    EXPECT_TRUE(fen->getBooCastling());
    EXPECT_TRUE(fen->getBoooCastling());
    EXPECT_STREQ(fen->getEnPassant().c_str(), "-");
}

TEST(Test_FEN, correctBuildFEN3Test){
    std::string fen_string = "r1b3nr/pppk2qp/1bnp4/4p1BQ/2BPP3/2P5/PP3PPP/RN3RK1 w - - 1 12";
    FEN * fen = new FEN(fen_string);
    EXPECT_STREQ(fen->getPositions().c_str(), "r b   nrpppk  qp bnp        p BQ  BPP     P     PP   PPPRN   RK ");
    EXPECT_EQ(fen->getActiveColor(), 'w');
    EXPECT_FALSE(fen->getWooCastling());
    EXPECT_FALSE(fen->getWoooCastling());
    EXPECT_FALSE(fen->getBooCastling());
    EXPECT_FALSE(fen->getBoooCastling());
    EXPECT_STREQ(fen->getEnPassant().c_str(), "-");
}