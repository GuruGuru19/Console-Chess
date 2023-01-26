#include <gtest/gtest.h>
#include "../../include/Pieces/Knight.h"

TEST(KnightTest, canMoveGeoTest){
    Knight * knight = new Knight("e5", true);

    EXPECT_TRUE(knight->canMoveGeo("f7"));
    EXPECT_TRUE(knight->canMoveGeo("d7"));
    EXPECT_TRUE(knight->canMoveGeo("c6"));
    EXPECT_TRUE(knight->canMoveGeo("c4"));
    EXPECT_TRUE(knight->canMoveGeo("d3"));
    EXPECT_TRUE(knight->canMoveGeo("f3"));
    EXPECT_TRUE(knight->canMoveGeo("g4"));
    EXPECT_TRUE(knight->canMoveGeo("g6"));

    EXPECT_FALSE(knight->canMoveGeo("f6"));
    EXPECT_FALSE(knight->canMoveGeo("f5"));
    EXPECT_FALSE(knight->canMoveGeo("e3"));

    delete knight;
}

TEST(KnightTest, makePathTest){
    Knight * knight = new Knight("e5", true);

    EXPECT_STREQ(knight->getPath("f7").c_str(), "");
    EXPECT_STREQ(knight->getPath("d7").c_str(), "");
    EXPECT_STREQ(knight->getPath("c6").c_str(), "");
    EXPECT_STREQ(knight->getPath("c4").c_str(), "");
    EXPECT_STREQ(knight->getPath("d3").c_str(), "");
    EXPECT_STREQ(knight->getPath("f3").c_str(), "");
    EXPECT_STREQ(knight->getPath("g4").c_str(), "");
    EXPECT_STREQ(knight->getPath("g6").c_str(), "");

    delete knight;
}

TEST(KnightTest, getGeoPossibleMovesTest){
    Knight * knight = new Knight("e5", true);

    EXPECT_STREQ(knight->getGeoPossibleMoves().c_str(), "f7d7g6c6f3d3g4c4");

    delete knight;
}