//
// Created by itai on 1/12/23.
//

#ifndef ITAI_CHESS_BOARDPREFIX_H
#define ITAI_CHESS_BOARDPREFIX_H

#include <gtest/gtest.h>
#include "../../include/Board.h"

class BoardPrefix : public ::testing::Test{
protected:
    void SetUp() override;
    void TearDown() override;

    Board * startBoard;
};


#endif //ITAI_CHESS_BOARDPREFIX_H
