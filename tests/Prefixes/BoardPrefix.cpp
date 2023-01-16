//
// Created by itai on 1/12/23.
//

#include "BoardPrefix.h"

void BoardPrefix::SetUp() {
    std::string fen_string1 = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    FEN * fen1 = new FEN(fen_string1);
    std::string fen_string2 = "rnbqkb1r/pppp1ppp/5n2/4Q3/4P3/8/PPPP1PPP/RNB1KBNR b KQkq - 0 3";
    FEN * fen2 = new FEN(fen_string2);
    std::string fen_string3 = "r1b3nr/pppk2qp/1bnp4/4p1BQ/2BPP3/2P5/PP3PPP/RN3RK1 w - - 1 12";
    FEN * fen3 = new FEN(fen_string3);
    board1 = new Board(*fen1);
    board2 = new Board(*fen2);
    board3 = new Board(*fen3);
    delete fen1; delete fen2; delete fen3;
}

void BoardPrefix::TearDown() {
    delete board1;
    delete board2;
    delete board3;
}
