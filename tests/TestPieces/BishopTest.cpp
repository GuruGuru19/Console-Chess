#include <gtest/gtest.h>
#include "../../include/Pieces/Bishop.h"

TEST(BishopTest, makePathTest){
    Bishop * bishop = new Bishop("e5", true);
    EXPECT_STREQ(bishop->getPath("e8").c_str(), "");// invalid geometrically
    EXPECT_STREQ(bishop->getPath("c7").c_str(), "d6");
    EXPECT_STREQ(bishop->getPath("a1").c_str(), "d4c3b2");
    EXPECT_STREQ(bishop->getPath("g4").c_str(), "");
    delete bishop;
}
