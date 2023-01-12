#include <gtest/gtest.h>
#include "../include/Screen.h"

TEST(ScreenTest, buildBoardString1Test){
    std::string fen_string = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    FEN * fen = new FEN(fen_string);
    std::string str = Screen::buildBoardString(*fen);
    ASSERT_STREQ(str.c_str(), "   A  B  C  D  E  F  G  H\n8 \x1B[30;46m \xE2\x99\x9C \x1B[0m\x1B[30;42m \xE2\x99\x9E \x1B[0m\x1B[30;46m \xE2\x99\x9D \x1B[0m\x1B[30;42m \xE2\x99\x9B \x1B[0m\x1B[30;46m \xE2\x99\x9A \x1B[0m\x1B[30;42m \xE2\x99\x9D \x1B[0m\x1B[30;46m \xE2\x99\x9E \x1B[0m\x1B[30;42m \xE2\x99\x9C \x1B[0m 8\n7 \x1B[30;42m \xE2\x99\x9F \x1B[0m\x1B[30;46m \xE2\x99\x9F \x1B[0m\x1B[30;42m \xE2\x99\x9F \x1B[0m\x1B[30;46m \xE2\x99\x9F \x1B[0m\x1B[30;42m \xE2\x99\x9F \x1B[0m\x1B[30;46m \xE2\x99\x9F \x1B[0m\x1B[30;42m \xE2\x99\x9F \x1B[0m\x1B[30;46m \xE2\x99\x9F \x1B[0m 7\n6 \x1B[30;46m   \x1B[0m\x1B[30;42m   \x1B[0m\x1B[30;46m   \x1B[0m\x1B[30;42m   \x1B[0m\x1B[30;46m   \x1B[0m\x1B[30;42m   \x1B[0m\x1B[30;46m   \x1B[0m\x1B[30;42m   \x1B[0m 6\n5 \x1B[30;42m   \x1B[0m\x1B[30;46m   \x1B[0m\x1B[30;42m   \x1B[0m\x1B[30;46m   \x1B[0m\x1B[30;42m   \x1B[0m\x1B[30;46m   \x1B[0m\x1B[30;42m   \x1B[0m\x1B[30;46m   \x1B[0m 5\n4 \x1B[30;46m   \x1B[0m\x1B[30;42m   \x1B[0m\x1B[30;46m   \x1B[0m\x1B[30;42m   \x1B[0m\x1B[30;46m   \x1B[0m\x1B[30;42m   \x1B[0m\x1B[30;46m   \x1B[0m\x1B[30;42m   \x1B[0m 4\n3 \x1B[30;42m   \x1B[0m\x1B[30;46m   \x1B[0m\x1B[30;42m   \x1B[0m\x1B[30;46m   \x1B[0m\x1B[30;42m   \x1B[0m\x1B[30;46m   \x1B[0m\x1B[30;42m   \x1B[0m\x1B[30;46m   \x1B[0m 3\n2 \x1B[97;46m \xE2\x99\x9F \x1B[0m\x1B[97;42m \xE2\x99\x9F \x1B[0m\x1B[97;46m \xE2\x99\x9F \x1B[0m\x1B[97;42m \xE2\x99\x9F \x1B[0m\x1B[97;46m \xE2\x99\x9F \x1B[0m\x1B[97;42m \xE2\x99\x9F \x1B[0m\x1B[97;46m \xE2\x99\x9F \x1B[0m\x1B[97;42m \xE2\x99\x9F \x1B[0m 2\n1 \x1B[97;42m \xE2\x99\x9C \x1B[0m\x1B[97;46m \xE2\x99\x9E \x1B[0m\x1B[97;42m \xE2\x99\x9D \x1B[0m\x1B[97;46m \xE2\x99\x9B \x1B[0m\x1B[97;42m \xE2\x99\x9A \x1B[0m\x1B[97;46m \xE2\x99\x9D \x1B[0m\x1B[97;42m \xE2\x99\x9E \x1B[0m\x1B[97;46m \xE2\x99\x9C \x1B[0m 1\n   A  B  C  D  E  F  G  H");
}

TEST(ScreenTest, buildBoardString2Test){
    std::string fen_string = "r1b3nr/pppk2qp/1bnp4/4p1BQ/2BPP3/2P5/PP3PPP/RN3RK1 w - - 1 12";
    FEN * fen = new FEN(fen_string);
    std::string str = Screen::buildBoardString(*fen);
    ASSERT_STREQ(str.c_str(), "   A  B  C  D  E  F  G  H\n8 \x1B[30;46m \xE2\x99\x9C \x1B[0m\x1B[30;42m   \x1B[0m\x1B[30;46m \xE2\x99\x9D \x1B[0m\x1B[30;42m   \x1B[0m\x1B[30;46m   \x1B[0m\x1B[30;42m   \x1B[0m\x1B[30;46m \xE2\x99\x9E \x1B[0m\x1B[30;42m \xE2\x99\x9C \x1B[0m 8\n7 \x1B[30;42m \xE2\x99\x9F \x1B[0m\x1B[30;46m \xE2\x99\x9F \x1B[0m\x1B[30;42m \xE2\x99\x9F \x1B[0m\x1B[30;46m \xE2\x99\x9A \x1B[0m\x1B[30;42m   \x1B[0m\x1B[30;46m   \x1B[0m\x1B[30;42m \xE2\x99\x9B \x1B[0m\x1B[30;46m \xE2\x99\x9F \x1B[0m 7\n6 \x1B[30;46m   \x1B[0m\x1B[30;42m \xE2\x99\x9D \x1B[0m\x1B[30;46m \xE2\x99\x9E \x1B[0m\x1B[30;42m \xE2\x99\x9F \x1B[0m\x1B[30;46m   \x1B[0m\x1B[30;42m   \x1B[0m\x1B[30;46m   \x1B[0m\x1B[30;42m   \x1B[0m 6\n5 \x1B[30;42m   \x1B[0m\x1B[30;46m   \x1B[0m\x1B[30;42m   \x1B[0m\x1B[30;46m   \x1B[0m\x1B[30;42m \xE2\x99\x9F \x1B[0m\x1B[30;46m   \x1B[0m\x1B[97;42m \xE2\x99\x9D \x1B[0m\x1B[97;46m \xE2\x99\x9B \x1B[0m 5\n4 \x1B[30;46m   \x1B[0m\x1B[30;42m   \x1B[0m\x1B[97;46m \xE2\x99\x9D \x1B[0m\x1B[97;42m \xE2\x99\x9F \x1B[0m\x1B[97;46m \xE2\x99\x9F \x1B[0m\x1B[30;42m   \x1B[0m\x1B[30;46m   \x1B[0m\x1B[30;42m   \x1B[0m 4\n3 \x1B[30;42m   \x1B[0m\x1B[30;46m   \x1B[0m\x1B[97;42m \xE2\x99\x9F \x1B[0m\x1B[30;46m   \x1B[0m\x1B[30;42m   \x1B[0m\x1B[30;46m   \x1B[0m\x1B[30;42m   \x1B[0m\x1B[30;46m   \x1B[0m 3\n2 \x1B[97;46m \xE2\x99\x9F \x1B[0m\x1B[97;42m \xE2\x99\x9F \x1B[0m\x1B[30;46m   \x1B[0m\x1B[30;42m   \x1B[0m\x1B[30;46m   \x1B[0m\x1B[97;42m \xE2\x99\x9F \x1B[0m\x1B[97;46m \xE2\x99\x9F \x1B[0m\x1B[97;42m \xE2\x99\x9F \x1B[0m 2\n1 \x1B[97;42m \xE2\x99\x9C \x1B[0m\x1B[97;46m \xE2\x99\x9E \x1B[0m\x1B[30;42m   \x1B[0m\x1B[30;46m   \x1B[0m\x1B[30;42m   \x1B[0m\x1B[97;46m \xE2\x99\x9C \x1B[0m\x1B[97;42m \xE2\x99\x9A \x1B[0m\x1B[30;46m   \x1B[0m 1\n   A  B  C  D  E  F  G  H");
}

TEST(ScreenTest, pieceCodeTest){
    EXPECT_STREQ(Screen::pieceCode('k', false).c_str(), "\x1B[30;46m \xE2\x99\x9A \x1B[0m");
    EXPECT_STREQ(Screen::pieceCode('K', false).c_str(), "\x1B[97;46m \xE2\x99\x9A \x1B[0m");

    EXPECT_STREQ(Screen::pieceCode('q', false).c_str(), "\x1B[30;46m \xE2\x99\x9B \x1B[0m");
    EXPECT_STREQ(Screen::pieceCode('Q', false).c_str(), "\x1B[97;46m \xE2\x99\x9B \x1B[0m");

    EXPECT_STREQ(Screen::pieceCode('r', false).c_str(), "\x1B[30;46m \xE2\x99\x9C \x1B[0m");
    EXPECT_STREQ(Screen::pieceCode('R', false).c_str(), "\x1B[97;46m \xE2\x99\x9C \x1B[0m");

    EXPECT_STREQ(Screen::pieceCode('b', true).c_str(), "\x1B[30;42m \xE2\x99\x9D \x1B[0m");
    EXPECT_STREQ(Screen::pieceCode('B', true).c_str(), "\x1B[97;42m \xE2\x99\x9D \x1B[0m");

    EXPECT_STREQ(Screen::pieceCode('n', true).c_str(), "\x1B[30;42m \xE2\x99\x9E \x1B[0m");
    EXPECT_STREQ(Screen::pieceCode('N', true).c_str(), "\x1B[97;42m \xE2\x99\x9E \x1B[0m");

    EXPECT_STREQ(Screen::pieceCode('p', true).c_str(), "\x1B[30;42m \xE2\x99\x9F \x1B[0m");
    EXPECT_STREQ(Screen::pieceCode('P', true).c_str(), "\x1B[97;42m \xE2\x99\x9F \x1B[0m");
}
