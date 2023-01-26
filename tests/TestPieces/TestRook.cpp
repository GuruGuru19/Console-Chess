#include <gtest/gtest.h>
#include "../../include/Pieces/Rook.h"

TEST(RookTest, canMoveGeoTest){
    Rook * rook = new Rook("e5", true);

    EXPECT_TRUE(rook->canMoveGeo("e7"));
    EXPECT_TRUE(rook->canMoveGeo("a5"));
    EXPECT_TRUE(rook->canMoveGeo("e8"));
    EXPECT_TRUE(rook->canMoveGeo("e1"));
    EXPECT_TRUE(rook->canMoveGeo("e1"));

    delete rook;
}

TEST(RookTest, makePathTest){
    Rook * rook = new Rook("e5", true);

    EXPECT_STREQ(rook->getPath("e8").c_str(), "e6e7");
    EXPECT_STREQ(rook->getPath("c7").c_str(), "");
    EXPECT_STREQ(rook->getPath("c5").c_str(), "d5");
    EXPECT_STREQ(rook->getPath("e1").c_str(), "e4e3e2");
    EXPECT_STREQ(rook->getPath("h5").c_str(), "f5g5");

    delete rook;
}

TEST(RookTest, getGeoPossibleMovesTest){
    Rook * rook = new Rook("c6", true);

    EXPECT_STREQ(rook->getGeoPossibleMoves().c_str(), "c1c2c3c4c5c7c8a6b6d6e6f6g6h6");

    delete rook;
}