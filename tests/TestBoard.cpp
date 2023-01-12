#include <gtest/gtest.h>
#include "../include/Board.h"

TEST(BoardTest, BuildBoard1){
    std::string fen_string = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    FEN * fen = new FEN(fen_string);
    Board * board = new Board(*fen);
}

TEST(BoardTest, legalMove1Test){
    std::string fen_string = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    FEN * fen = new FEN(fen_string);
    Board * board = new Board(*fen);
    //EXPECT_TRUE(board->legalMove("e2e4"));
}

TEST(BoardTest, getKingPositionTest){
    std::string fen_string = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    FEN * fen = new FEN(fen_string);
    Board * board = new Board(*fen);
    ASSERT_STREQ(board->getKingPosition(true).c_str(), "e1");
    ASSERT_STREQ(board->getKingPosition(false).c_str(), "e8");
}

TEST(BoardTest, sqrThreatenerTest){
    std::string fen_string = "rnbqkb1r/pppp1ppp/5n2/4Q3/4P3/8/PPPP1PPP/RNB1KBNR b KQkq - 0 3";
    FEN * fen = new FEN(fen_string);
    Board * board = new Board(*fen);
    std::string c7_threatener = board->sqrThreatener("c7", true);
    //EXPECT_STREQ("e5", c7_threatener.c_str());
}

TEST(BoardTest, SqrToPosTest){
    EXPECT_STREQ(Board::sqrToPosition(1).c_str(), "b8");
    EXPECT_STREQ(Board::sqrToPosition(2).c_str(), "c8");
    EXPECT_STREQ(Board::sqrToPosition(4).c_str(), "e8");
    EXPECT_STREQ(Board::sqrToPosition(8).c_str(), "a7");
    EXPECT_STREQ(Board::sqrToPosition(16).c_str(), "a6");
    EXPECT_STREQ(Board::sqrToPosition(32).c_str(), "a4");
    EXPECT_STREQ(Board::sqrToPosition(63).c_str(), "h1");
    EXPECT_STREQ(Board::sqrToPosition(31).c_str(), "h5");
    EXPECT_STREQ(Board::sqrToPosition(15).c_str(), "h7");
    EXPECT_STREQ(Board::sqrToPosition(7).c_str(), "h8");
    EXPECT_STREQ(Board::sqrToPosition(3).c_str(), "d8");
    EXPECT_STREQ(Board::sqrToPosition(0).c_str(), "a8");
}

TEST(BoardTest, PosToAqrTest){
    EXPECT_EQ(Board::positionToSqr("b8"), 1);
    EXPECT_EQ(Board::positionToSqr("c7"), 10);
    EXPECT_EQ(Board::positionToSqr("d6"), 19);
    EXPECT_EQ(Board::positionToSqr("e5"), 28);
    EXPECT_EQ(Board::positionToSqr("f4"), 37);
    EXPECT_EQ(Board::positionToSqr("g3"), 46);
    EXPECT_EQ(Board::positionToSqr("h2"), 55);
}