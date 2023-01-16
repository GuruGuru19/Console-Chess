#include <gtest/gtest.h>
#include "../../include/Pieces/Rook.h"

TEST(RookTest, makePathTest){
    Rook * rook = new Rook("e5", true);
    EXPECT_STREQ(rook->getPath("e8").c_str(), "e6e7");
    EXPECT_STREQ(rook->getPath("c7").c_str(), "");
    EXPECT_STREQ(rook->getPath("c5").c_str(), "d5");
    EXPECT_STREQ(rook->getPath("e1").c_str(), "e4e3e2");
    EXPECT_STREQ(rook->getPath("h5").c_str(), "f5g5");
    delete rook;
}
