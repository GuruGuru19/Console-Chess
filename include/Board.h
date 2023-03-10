//
// Created by itai on 1/3/23.
//

#ifndef ITAI_CHESS_BOARD_H
#define ITAI_CHESS_BOARD_H


#include <list>
#include "FEN.h"
#include "Piece.h"

class Board {
private:
    // board current FEN
    FEN * boardFEN;
    // array of piece pointers representing the board
    Piece *board [64];

public:
    //constructor
    Board(FEN & fen);
    //destructor
    ~Board();

    /**
    * @param move a 4 char string (2 positions) that represent a move on the board
    * @param pinnedPieceCantMove (default = true) is the calculation needs to consider is the piece is pinned -
     * relevant when we check if a piece can eat the King
    * @param toEat (default = false) the move aims to eat another piece
    * @param threateningCheck (default = false) when you check if a piece can eat an empty sqr -
     * relevant when we check if a king can move to a sqr
    * @return is the move is legal
    */
    bool legalMove(const std::string& move, bool pinnedPieceCantMove = true, bool toEat = false, bool threateningCheck = false);
    bool legalEatMove(std::string move, bool pinnedPieceCantMove = true,  bool threateningCheck = false){
        return legalMove(move, pinnedPieceCantMove, true, threateningCheck);
    };

    /**
    * @param position position on the board
    * @return Piece pointer - piece in the (position)
    */
    Piece * getPiece(std::string & position);

    /**
    * @param white is the king white
    * @return the king's position on the board
    */
    std::string getKingPosition(bool white);

    /**
    * @param position position on the board
    * @return is the piece on (position) pinned
    */
    bool piecePinned(const std::string& position);

    /**
    * @param move a 4 char string (2 positions) that represent a move on the board
     * - **assumes the move is on the board**
    * @param ignorePos (default = "") a position to ignore on the way
    * @return is the move path is clear of pieces
    */
    bool movePathClear(const std::string& move, const std::string& ignorePos = "");

    /**
    * @param position position on the board
    * @param threatenedByWhite is the Threatener a white piece
    * @param ignorePinned (default = false) a Threatener can be pinned and still be a threat -
     * relevant when threatening a king
    * @param moveToEat (default = true) is the move to the sqr considered an "eat move"
    * @return is the piece on (position) pinned
    */
    std::string sqrThreatener(const std::string& position, bool threatenedByWhite, bool ignorePinned = false, bool moveToEat = true);

    /**
    * @param position position on the board
    * @return index on the board array (from 0 to 63)
    */
    static int positionToSqr(std::string position);

    /**
    * @param sqr index on the board array (from 0 to 63)
    * @return position on the board
    */
    static std::string sqrToPosition(int sqr);

    /**
    * @return makes a board string
     * used for debugs
    */
    std::string printBoard();

    /**
     * preforms moves on the board
    * @param move a 4 char string (2 positions) that represent a move on the board
    * @return if the move was made
    */
    bool move(const std::string& move);

    /**
    * @param position position on the board
    * @return all the legal positions the piece at (position) can go to legally
    */
    std::string getLegalMoves(const std::string& position);

    /**
     * puts a new piece on the board -
     * used in crowning
    * @param new_piece piece pointer
    */
    void setPiece(Piece * new_piece);

    bool isWhiteTurn(){
        return this->boardFEN->isWhiteTurn();
    }

    FEN * getFEN(){
        return this->boardFEN;
    }

    /**
    * @param pos a 2 char long string representing a position
    */
    static bool isPositionOnBoard(const std::string& pos){
        return pos[0] >= 'a' && pos[0] <='h' && pos[1] >= '1' && pos[1] <='8';
    }
};


#endif //ITAI_CHESS_BOARD_H
