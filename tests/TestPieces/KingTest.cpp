#include <gtest/gtest.h>
#include "../../include/Pieces/King.h"


TEST(KingTest, canMoveGeoTest){
    King * king = new King("e1", false);

    EXPECT_TRUE(king->canMoveGeo("d1"));
    EXPECT_TRUE(king->canMoveGeo("d2"));
    EXPECT_TRUE(king->canMoveGeo("f2"));
    EXPECT_TRUE(king->canMoveGeo("e2"));
    EXPECT_FALSE(king->canMoveGeo("c1"));
    EXPECT_FALSE(king->canMoveGeo("g1"));

    king->setPosition("e8");
    EXPECT_TRUE(king->canMoveGeo("d8"));
    EXPECT_TRUE(king->canMoveGeo("e7"));
    EXPECT_TRUE(king->canMoveGeo("c8"));
    EXPECT_TRUE(king->canMoveGeo("g8"));
    EXPECT_FALSE(king->canMoveGeo("c6"));

    delete king;
}

TEST(KingTest, makePathTest){
    King * king = new King("e1", true);

    EXPECT_STREQ(king->getPath("e1").c_str(), "");
    EXPECT_STREQ(king->getPath("f1").c_str(), "");
    EXPECT_STREQ(king->getPath("d2").c_str(), "");
    EXPECT_STREQ(king->getPath("g1").c_str(), "f1");
    EXPECT_STREQ(king->getPath("c1").c_str(), "d1");

    delete king;
}

TEST(KingTest, getGeoPossibleMovesTest){
    King * king = new King("e1", true);

    EXPECT_STREQ(king->getGeoPossibleMoves().c_str(), "g1c1d0d1d2e2f2f1f0e0");

    delete king;
    king = new King("h1", true);

    EXPECT_STREQ(king->getGeoPossibleMoves().c_str(), "g0g1g2h2i2i1i0h0");

    delete king;
}

TEST(KingTest, isCastlingTest){
    King * king = new King("e1", true);

    EXPECT_TRUE(king->isCastling("g1") == 1);
    EXPECT_TRUE(king->isCastling("c1") == 2);
    EXPECT_TRUE(king->isCastling("g8") == 0);
    EXPECT_TRUE(king->isCastling("c8") == 0);

    delete king;
}