#include <gtest/gtest.h>
#include "../../include/Pieces/Bishop.h"

TEST(BishopTest, canMoveGeoTest){
    Bishop * bishop = new Bishop("c6", true);

    EXPECT_TRUE(bishop->canMoveGeo("b5"));
    EXPECT_TRUE(bishop->canMoveGeo("a4"));
    EXPECT_TRUE(bishop->canMoveGeo("f3"));
    EXPECT_TRUE(bishop->canMoveGeo("e8"));
    EXPECT_FALSE(bishop->canMoveGeo("d6"));
    EXPECT_FALSE(bishop->canMoveGeo("d4"));

    delete bishop;
}

TEST(BishopTest, makePathTest){
    Bishop * bishop = new Bishop("e5", true);

    EXPECT_STREQ(bishop->getPath("e8").c_str(), "");// invalid geometrically
    EXPECT_STREQ(bishop->getPath("c7").c_str(), "d6");
    EXPECT_STREQ(bishop->getPath("a1").c_str(), "d4c3b2");
    EXPECT_STREQ(bishop->getPath("g4").c_str(), "");

    delete bishop;
}

TEST(BishopTest, getGeoPossibleMovesTest){
    Bishop * bishop = new Bishop("c6", true);

    EXPECT_STREQ(bishop->getGeoPossibleMoves().c_str(), "d7b7b5d5e8a8a4e4f3g2h1");

    delete bishop;
}
