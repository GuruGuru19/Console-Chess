//
// Created by itai on 1/3/23.
//

#ifndef ITAI_CHESS_BOARD_H
#define ITAI_CHESS_BOARD_H


#include <list>
#include "FEN.h"
#include "Pieces/Piece.h"

class Board {
private:
    FEN * boardFEN;
    Piece ** board;

public:
    Board(FEN & fen);
    ~Board();
    bool legalMove(std::string move, bool considerPinned = true, bool toEat = false, bool threateningCheck = false);
    bool legalEatMove(std::string move, bool considerPinned = true,  bool threateningCheck = false){
        return legalMove(move, considerPinned, true, threateningCheck);
    };
    Piece * getPiece(std::string & position){
        return this->board[positionToSqr(position)];
    };
    std::string getKingPosition(bool white);
    bool piecePinned(std::string position);
    bool movePathClear(std::string move);
    std::string sqrThreatener(std::string position, bool threatenedByWhite, bool ignorePinned = false);

    static int positionToSqr(std::string position);
    static std::string sqrToPosition(int sqr);

    std::string printBoard();

    bool move(std::string move);

    std::string getLegalMoves(std::string position);

    bool isWhiteTurn(){
        return this->boardFEN->isWhiteTurn();
    }
};


#endif //ITAI_CHESS_BOARD_H
