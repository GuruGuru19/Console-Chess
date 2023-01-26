#include <gtest/gtest.h>
#include "../../include/Pieces/Pawn.h"


TEST(PawnTest, canMoveGeoTest){
    Pawn * pawn = new Pawn("f2", true);

    EXPECT_TRUE(pawn->canMoveGeo("f3"));
    EXPECT_TRUE(pawn->canMoveGeo("f4"));
    EXPECT_FALSE(pawn->canMoveGeo("f5"));
    EXPECT_FALSE(pawn->canMoveGeo("g3"));

    delete pawn;
}

TEST(PawnTest, canMoveGeoToEatTest){
    Pawn * pawn = new Pawn("f2", true);

    EXPECT_FALSE(pawn->canMoveGeoToEat("f3"));
    EXPECT_FALSE(pawn->canMoveGeoToEat("f4"));
    EXPECT_FALSE(pawn->canMoveGeoToEat("f5"));
    EXPECT_TRUE(pawn->canMoveGeoToEat("g3"));
    EXPECT_TRUE(pawn->canMoveGeoToEat("e3"));

    delete pawn;
}

TEST(PawnTest, makePathTest){
    Pawn * pawn = new Pawn("f2", true);

    EXPECT_STREQ(pawn->getPath("g3").c_str(), "");
    EXPECT_STREQ(pawn->getPath("e3").c_str(), "");
    EXPECT_STREQ(pawn->getPath("f3").c_str(), "");
    EXPECT_STREQ(pawn->getPath("f4").c_str(), "f3");
    EXPECT_STREQ(pawn->getPath("g1").c_str(), "");

    delete pawn;
}

TEST(PawnTest, getGeoPossibleMovesTest){
    Pawn * pawn = new Pawn("f2", true);

    EXPECT_STREQ(pawn->getGeoPossibleMoves().c_str(), "f3f4g3e3");

    delete pawn;
}