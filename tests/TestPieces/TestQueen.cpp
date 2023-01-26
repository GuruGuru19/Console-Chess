#include <gtest/gtest.h>
#include "../../include/Pieces/Queen.h"

TEST(QueenTest, canMoveGeoTest){
    Queen * queen = new Queen("e5", true);

    EXPECT_TRUE(queen->canMoveGeo("e7"));
    EXPECT_TRUE(queen->canMoveGeo("b2"));
    EXPECT_TRUE(queen->canMoveGeo("c3"));
    EXPECT_TRUE(queen->canMoveGeo("h2"));
    EXPECT_FALSE(queen->canMoveGeo("c6"));

    delete queen;
}

TEST(QueenTest, makePathTest){
    Queen * queen = new Queen("e5", true);

    EXPECT_STREQ(queen->getPath("e8").c_str(), "e6e7");
    EXPECT_STREQ(queen->getPath("c7").c_str(), "d6");
    EXPECT_STREQ(queen->getPath("c4").c_str(), "");
    EXPECT_STREQ(queen->getPath("d4").c_str(), "");

    delete queen;
}

TEST(QueenTest, getGeoPossibleMovesTest){
    Queen * queen = new Queen("c6", true);

    EXPECT_STREQ(queen->getGeoPossibleMoves().c_str(), "d7b7b5d5e8a8a4e4f3g2h1c1c2c3c4c5c7c8a6b6d6e6f6g6h6");

    delete queen;
}

