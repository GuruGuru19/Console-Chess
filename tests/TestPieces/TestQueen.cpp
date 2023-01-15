#include <gtest/gtest.h>
#include "../../include/Pieces/Queen.h"

TEST(QueenTest, makePathTest){
    Queen * queen = new Queen("e5", true);
    EXPECT_STREQ(queen->getPath("e8").c_str(), "e6e7");
    EXPECT_STREQ(queen->getPath("c7").c_str(), "d6");
    EXPECT_STREQ(queen->getPath("c4").c_str(), "");
    EXPECT_STREQ(queen->getPath("d4").c_str(), "");
}

TEST(QueenTest, makePathTest){
    Queen * queen = new Queen("e5", true);
    EXPECT_STREQ(queen->getPath("e8").c_str(), "e6e7");
    EXPECT_STREQ(queen->getPath("c7").c_str(), "d6");
    EXPECT_STREQ(queen->getPath("c4").c_str(), "");
    EXPECT_STREQ(queen->getPath("d4").c_str(), "");
}