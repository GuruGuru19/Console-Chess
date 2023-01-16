#include <gtest/gtest.h>
#include "../include/Board.h"
#include "Prefixes/BoardPrefix.h"

TEST(BoardTest, BuildBoard1){
    std::string fen_string = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    FEN * fen = new FEN(fen_string);
    Board * board = new Board(*fen);
    delete board; delete fen;
}

TEST_F(BoardPrefix, legalMove1Test){
    EXPECT_TRUE(board1->legalMove("e2e4"));
    EXPECT_TRUE(board1->legalMove("f2f4"));
    EXPECT_TRUE(board1->legalMove("a2a3"));
    EXPECT_FALSE(board1->legalMove("a2a2"));//cant move to the same place
    EXPECT_FALSE(board1->legalMove("a2c3"));//pawn cant move that way geometrically
    EXPECT_FALSE(board1->legalEatMove("a2c3"));//trying to eat an empty sqr
}

TEST_F(BoardPrefix, legalMove2Test){
    EXPECT_TRUE(board2->legalMove("f8e7"));
    EXPECT_TRUE(board2->legalMove("d8e7"));
    EXPECT_FALSE(board2->legalMove("f8d6"));// illegal because black is checked
    EXPECT_FALSE(board2->legalMove("g7g5"));// illegal because black is checked
    EXPECT_FALSE(board2->legalMove("e8e7"));// illegal because black is checked

}

TEST_F(BoardPrefix, legalMove3Test){
    EXPECT_TRUE(board3->legalMove("c4e6"));
    EXPECT_TRUE(board3->legalEatMove("h5h7"));
    EXPECT_FALSE(board3->legalMove("d7e6"));
    EXPECT_FALSE(board3->legalMove("h5h7"));// needs legalEatMove()
    EXPECT_FALSE(board3->legalMove("e5e5"));
}

TEST(BoardTest, legalMoveCastling1Test){
    std::string fen_string = "r3k2r/pppq1p1p/2np1bpB/4p3/2PNP2P/1PN3P1/P1P1BP2/1R2K2R b K - 0 14";
    FEN * fen = new FEN(fen_string);
    Board * board = new Board(*fen);
    EXPECT_TRUE(board->legalMove("e1g1"));//w o-o
    EXPECT_FALSE(board->legalMove("e1c1"));//w o-o-o
    EXPECT_FALSE(board->legalMove("e8g8"));//b o-o
    EXPECT_FALSE(board->legalMove("e88"));//b o-o-o
    delete board; delete fen;
}

TEST(BoardTest, legalMoveCastling2Test){
    std::string fen_string = "r3k2r/6b1/2nqb2n/pppppppp/PPPPPPPP/2NQB2N/6B1/R3K2R w KQkq - 10 14"; // all
    FEN * fen = new FEN(fen_string);
    Board * board = new Board(*fen);
    EXPECT_TRUE(board->legalMove("e1g1"));//w o-o
    EXPECT_TRUE(board->legalMove("e1c1"));//w o-o-o
    EXPECT_TRUE(board->legalMove("e8g8"));//b o-o
    EXPECT_TRUE(board->legalMove("e8c8"));//b o-o-o
    delete board; delete fen;
}

TEST(BoardTest, legalMoveCastling3Test){
    std::string fen_string = "r3k2r/2q3b1/2n1b2n/pppppppp/PPPPPPPP/4B2N/6B1/RQ1NK2R b KQkq - 13 15"; // checking that you cant castle if the path isn't clear
    FEN * fen = new FEN(fen_string);
    Board * board = new Board(*fen);
    EXPECT_TRUE(board->legalMove("e1g1"));//w o-o
    EXPECT_FALSE(board->legalMove("e1c1"));//w o-o-o
    EXPECT_TRUE(board->legalMove("e8g8"));//b o-o
    EXPECT_TRUE(board->legalMove("e8c8"));//b o-o-o
    delete board; delete fen;
}

TEST(BoardTest, legalMoveEnPassantTest){
    std::string fen_string = "rnbqkbnr/ppp5/Q3p1pp/3pPp2/8/2P5/PP1P1PPP/RNB1KBNR w KQkq d6 0 6";
    FEN * fen = new FEN(fen_string);
    Board * board = new Board(*fen);
    EXPECT_TRUE(board->legalEatMove("e5d6"));
    EXPECT_FALSE(board->legalEatMove("e5f6"));
    // not that its relevant :)
    EXPECT_FALSE(board->legalEatMove("a6d6"));
    EXPECT_TRUE(board->legalMove("a6d6"));
    delete board; delete fen;
}

TEST_F(BoardPrefix, getPieceTest){
    std::string a8 = "a8";
    ASSERT_TRUE(board3->getPiece(a8) != nullptr);
    EXPECT_TRUE(board3->getPiece(a8)->getMark() == 'r');

    std::string d7 = "d7";
    ASSERT_TRUE(board3->getPiece(d7) != nullptr);
    EXPECT_TRUE(board3->getPiece(d7)->getMark() == 'k');

    std::string h5 = "h5";
    ASSERT_TRUE(board3->getPiece(h5) != nullptr);
    EXPECT_TRUE(board3->getPiece(h5)->getMark() == 'Q');

    std::string c3 = "c3";
    ASSERT_TRUE(board3->getPiece(c3) != nullptr);
    EXPECT_TRUE(board3->getPiece(c3)->getMark() == 'P');

    std::string d1 = "d1";
    EXPECT_TRUE(board3->getPiece(d1) == nullptr); // empty sqr
    std::string e7 = "e7";
    EXPECT_TRUE(board3->getPiece(e7) == nullptr); // empty sqr
    std::string n11 = "11";
    EXPECT_TRUE(board3->getPiece(n11) == nullptr); // invalid sqr
    std::string ff = "ff";
    EXPECT_TRUE(board3->getPiece(ff) == nullptr); // invalid sqr

}

TEST_F(BoardPrefix, getKingPositionTest){
    EXPECT_STREQ(board1->getKingPosition(true).c_str(), "e1");
    EXPECT_STREQ(board1->getKingPosition(false).c_str(), "e8");
    EXPECT_STREQ(board2->getKingPosition(true).c_str(), "e1");
    EXPECT_STREQ(board2->getKingPosition(false).c_str(), "e8");
    EXPECT_STREQ(board3->getKingPosition(true).c_str(), "g1");
    EXPECT_STREQ(board3->getKingPosition(false).c_str(), "d7");
}

TEST(BoardTest, piecePinnedTest){
    std::string fen_string = "rnbqkbnr/pp1ppppp/8/2p4Q/4P3/8/PPPP1PPP/RNB1KBNR b KQkq - 1 2";
    FEN * fen = new FEN(fen_string);
    Board * board = new Board(*fen);
    EXPECT_TRUE(board->piecePinned("f7"));
    delete board; delete fen;

    std::string fen_string_2 = "rnbqkbnr/pp1ppp1p/6p1/2p4Q/4P3/8/PPPP1PPP/RNB1KBNR w KQkq - 0 3";
    FEN * fen_2 = new FEN(fen_string_2);
    Board * board_2 = new Board(*fen_2);
    EXPECT_FALSE(board_2->piecePinned("f7"));
    delete board_2; delete fen_2;
}

TEST_F(BoardPrefix, movePathClearTest){
    EXPECT_TRUE(board1->movePathClear("e2e4"));
    EXPECT_TRUE(board1->movePathClear("h7h6"));
    EXPECT_FALSE(board1->movePathClear("d1f3"));

    EXPECT_TRUE(board2->movePathClear("e5c7"));
    EXPECT_TRUE(board2->movePathClear("f6e4"));
    EXPECT_TRUE(board2->movePathClear("h8g8"));
    EXPECT_FALSE(board2->movePathClear("d8e1"));//invalid geometrically
    EXPECT_FALSE(board2->movePathClear("e5d8"));
    EXPECT_FALSE(board2->movePathClear("h8e8"));

    EXPECT_TRUE(board3->movePathClear("c4e6"));
    EXPECT_TRUE(board3->movePathClear("f1c1"));
    EXPECT_FALSE(board3->movePathClear("f1f4"));
    EXPECT_FALSE(board3->movePathClear("b6d8"));
}

TEST_F(BoardPrefix, sqrThreatenerTest){
    std::string c7_threatener = board2->sqrThreatener("c7", true);
    std::string e8_threatener = board2->sqrThreatener("e8", true);
    EXPECT_STREQ("e5", c7_threatener.c_str());
    EXPECT_STREQ("e5", e8_threatener.c_str());
}

TEST_F(BoardPrefix, move1Test){
    std::string fen_string = "r1b3nr/pppk2qp/1bnp4/4p1BQ/2BPP3/2P5/PP3PPP/RN3RK1 w - - 1 12";
    FEN * fen = new FEN(fen_string);
    Board * board = new Board(*fen);

    EXPECT_STREQ(board->printBoard().c_str(), "r b   nr\npppk  qp\n bnp    \n    p BQ\n  BPP   \n  P     \nPP   PPP\nRN   RK \n");
    ASSERT_TRUE(board->move("c4e6"));
    EXPECT_STREQ(board->printBoard().c_str(), "r b   nr\npppk  qp\n bnpB   \n    p BQ\n   PP   \n  P     \nPP   PPP\nRN   RK \n");
    ASSERT_TRUE(board->move("d7e6"));
    EXPECT_STREQ(board->printBoard().c_str(), "r b   nr\nppp   qp\n bnpk   \n    p BQ\n   PP   \n  P     \nPP   PPP\nRN   RK \n");

    delete board; delete fen;
}

TEST_F(BoardPrefix, moveToEatTest){
    //TODO: write test (remember En passant)
}

TEST(BoardTest, SqrToPosTest){
    EXPECT_STREQ(Board::sqrToPosition(1).c_str(), "b8");
    EXPECT_STREQ(Board::sqrToPosition(2).c_str(), "c8");
    EXPECT_STREQ(Board::sqrToPosition(4).c_str(), "e8");
    EXPECT_STREQ(Board::sqrToPosition(8).c_str(), "a7");
    EXPECT_STREQ(Board::sqrToPosition(16).c_str(), "a6");
    EXPECT_STREQ(Board::sqrToPosition(32).c_str(), "a4");
    EXPECT_STREQ(Board::sqrToPosition(63).c_str(), "h1");
    EXPECT_STREQ(Board::sqrToPosition(31).c_str(), "h5");
    EXPECT_STREQ(Board::sqrToPosition(15).c_str(), "h7");
    EXPECT_STREQ(Board::sqrToPosition(7).c_str(), "h8");
    EXPECT_STREQ(Board::sqrToPosition(3).c_str(), "d8");
    EXPECT_STREQ(Board::sqrToPosition(0).c_str(), "a8");
}

TEST(BoardTest, PosToAqrTest){
    EXPECT_EQ(Board::positionToSqr("b8"), 1);
    EXPECT_EQ(Board::positionToSqr("c7"), 10);
    EXPECT_EQ(Board::positionToSqr("d6"), 19);
    EXPECT_EQ(Board::positionToSqr("e5"), 28);
    EXPECT_EQ(Board::positionToSqr("f4"), 37);
    EXPECT_EQ(Board::positionToSqr("g3"), 46);
    EXPECT_EQ(Board::positionToSqr("h2"), 55);
}

TEST_F(BoardPrefix, getLegalMovesTest){
    EXPECT_STREQ(board1->getLegalMoves("f2").c_str(), "f3f4");
    EXPECT_STREQ(board1->getLegalMoves("e7").c_str(), "e6e5");
    EXPECT_STREQ(board1->getLegalMoves("a2").c_str(), "a3a4");
    EXPECT_STREQ(board1->getLegalMoves("e1").c_str(), ""); // closed in
    EXPECT_STREQ(board1->getLegalMoves("d4").c_str(), ""); // empty sqr

    EXPECT_STREQ(board2->getLegalMoves("f8").c_str(), "e7");// the king is checked and the piece can help !
    EXPECT_STREQ(board2->getLegalMoves("f6").c_str(), "");// the king is checked and the piece can't help  :(

    EXPECT_STREQ(board3->getLegalMoves("h5").c_str(), "d1e2f3g4h3h4h6h7");
}

TEST(BoardTest, getLegalMovesEnPassantTest){
    std::string fen_string = "rnbqkbnr/ppp5/Q3p1pp/3pPp2/8/2P5/PP1P1PPP/RNB1KBNR w KQkq d6 0 6";
    FEN * fen = new FEN(fen_string);
    Board * board = new Board(*fen);
    EXPECT_STREQ(board->getLegalMoves("e5").c_str(), "d6"); // En passant
    EXPECT_STREQ(board->getLegalMoves("a6").c_str(), "b5c4d3e2b7a3a4a5a7b6c6d6e6");
    delete board; delete fen;
}

TEST(BoardTest, getLegalMovesCastling1Test){
    std::string fen_string = "r3k2r/pppq1p1p/2np1bpB/4p3/2PNP2P/1PN3P1/P1P1BP2/1R2K2R b K - 0 14";
    FEN * fen = new FEN(fen_string);
    Board * board = new Board(*fen);
    EXPECT_STREQ(board->getLegalMoves("e1").c_str(), "g1d1d2f1");
    EXPECT_STREQ(board->getLegalMoves("e8").c_str(), "d8e7");
    delete board; delete fen;
}

TEST(BoardTest, getLegalMovesCastling2Test){
    std::string fen_string = "r3k2r/6b1/2nqb2n/pppppppp/PPPPPPPP/2NQB2N/6B1/R3K2R w KQkq - 10 14";
    FEN * fen = new FEN(fen_string);
    Board * board = new Board(*fen);
    EXPECT_STREQ(board->getLegalMoves("e1").c_str(), "g1c1d1d2e2f2f1");
    EXPECT_STREQ(board->getLegalMoves("e8").c_str(), "g8c8d7d8f8f7e7");
    delete board; delete fen;
}