//
// Created by itai on 1/3/23.
//

#include <iostream>
#include "../include/Board.h"
#include "../include/Pieces/Pawn.h"
#include "../include/Pieces/Rook.h"
#include "../include/Pieces/Knight.h"
#include "../include/Pieces/Bishop.h"
#include "../include/Pieces/Queen.h"
#include "../include/Pieces/King.h"


Board::Board(FEN &fen) {
    this->boardFEN = new FEN(fen);
    this->board = (Piece **)malloc(sizeof(Piece *) * 64);
    int i = 0;
    for (char c: this->boardFEN->getPositions()) {
        if (c == 'p' || c == 'P'){
            board[i] = new Pawn(sqrToPosition(i), c == 'P');
        }
        else if (c == 'r' || c == 'R'){
            board[i] = new Rook(sqrToPosition(i), c == 'R');
        }
        else if (c == 'n' || c == 'N'){
            board[i] = new Knight(sqrToPosition(i), c == 'N');
        }
        else if (c == 'b' || c == 'B'){
            board[i] = new Bishop(sqrToPosition(i), c == 'B');
        }
        else if (c == 'q' || c == 'Q'){
            board[i] = new Queen(sqrToPosition(i), c == 'Q');
        }
        else if (c == 'k' || c == 'K'){
            board[i] = new King(sqrToPosition(i), c == 'K');
        } else{
            board[i] = nullptr;
        }
        i++;
    }
}

Board::~Board() {
    delete this->boardFEN;
    for (int i = 0; i < 64; ++i) {
        delete this->board[i];
    }
}

bool Board::legalMove(std::string move, bool considerPinned, bool toEat) {
    std::string fromPos = move.substr(0,2);
    std::string toPos = move.substr(2);

    if (not (fromPos[0] >= 'a' && fromPos[0] <='h' && fromPos[1] >= '1' && fromPos[1] <='8'&&
            toPos[0] >= 'a' && toPos[0] <='h' && toPos[1] >= '1' && toPos[1] <='8')){
        return false;// the move is outside the board
    }

    Piece * piece = this->board[positionToSqr(fromPos)];

    if (piece == nullptr){
        return false;// trying to move an empty sqr
    }

    //trying to move a king
    if (piece->getMark() == 'K' || piece->getMark() == 'k'){
        // trying to move a king to Threatened sqr
        if (!sqrThreatener(move.substr(2), piece->getMark() == 'k', true).empty()){
            return false;
        }
        // a king cant be pinned
        considerPinned = false;
    }
    // tests if your trying to move while the king is checked
    else{
        std::string kingPos = getKingPosition(piece->getMark() >= 'A' && piece->getMark() >= 'Z');
        std::string kingThreatenerPos = this->sqrThreatener(kingPos, !(piece->getMark() >= 'A' && piece->getMark() >= 'Z'), true);
        //if the king is checked and this move doesn't fix it +
        // assumes that there is only one threatener cause else this code isn't reachable
        if (!kingThreatenerPos.empty()){
            // if the move is to eat the Threatener
            bool flag = move.substr(2) == kingThreatenerPos;
            Piece * kingThreatener = this->board[positionToSqr(kingThreatenerPos)];
            std::string path = kingThreatener->getPath(kingPos);
            // if the move is to block the Threatener
            for (int i = 0; i < path.size()/2 && !flag; ++i) {
                if (move.substr(2) == path.substr(i*2, 2)){
                    flag = true;
                }
            }
            if (!flag){
                return false;
            }
        }

    }

    bool pinned = considerPinned && piecePinned(fromPos);
    bool geometrically_legal = toEat ? piece->canMoveGeoToEat(toPos) : piece->canMoveGeo(toPos);
    bool move_path_clear = movePathClear(move);
    return !pinned && geometrically_legal && move_path_clear;
}

std::string Board::getKingPosition(bool white) {
    char target = white?'W':'w';
    for (int i = 0; i < 64; ++i) {
        if (this->board[i] != nullptr && this->board[i]->getMark() == target){
            return sqrToPosition(i);
        }
    }
    return "";
}

bool Board::piecePinned(std::string position) {//TODO
    return false;
}

bool Board::movePathClear(std::string move) {
    std::string fromPos = move.substr(0,2);
    std::string toPos = move.substr(2);
    Piece * piece = this->board[positionToSqr(fromPos)];
    if (piece == nullptr){
        return false;// trying to move an empty sqr
    }
    if (piece->canMoveGeo(toPos)){ // doesn't check the eatGeo cause its only relevant to the pawn
        return false;// the piece cant move that way geometrically
    }
    std::string path = piece->getPath(toPos);
    for (int i = 0; i < path.size()/2; ++i) {
        if (this->board[positionToSqr(path.substr(i*2, 2))] != nullptr){
            return false;// found a piece in the way
        }
    }
    return true; // no problem
}

std::string Board::sqrThreatener(std::string position, bool threatenedByWhite, bool ignorePinned) {
    std::string threateners;
    char targetMarkSet = threatenedByWhite?'A':'a';
    for (int i = 0; i < 64; ++i) {
        Piece * p = this->board[i];
        if (p != nullptr && // the sqr in not empty
        p->getMark() >=targetMarkSet && p->getMark() < targetMarkSet + 26 && // & the threatener is the opposite color
                legalEatMove(sqrToPosition(i)+position), !ignorePinned){ // & the move is legal
            threateners.append(sqrToPosition(i));
        }
    }
    return threateners;
}

int Board::positionToSqr(std::string position) {
    int x = 'a' - position[0];
    int y = '1' - position[1];
    return x + y * 8;
}

std::string Board::sqrToPosition(int sqr) {
    char x = (char)('a' + (sqr%8));
    char y = (char)('a' + (sqr/8));
    std::string p = "  ";
    p[0] = x;
    p[1] = y;
    return p;
}

void Board::printBoard() {
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            Piece * piece = this->board[x + y * 8];
            if (piece == nullptr){
                std::cout << " ";
                continue;
            }
            std::cout << this->board[x + y * 8]->getMark();
        }
        std::cout << "\n";
    }
}

bool Board::move(std::string move) {
    return false; //TODO
}

std::string Board::getLegalMoves(std::string position) {
    Piece * piece = this->board[positionToSqr(position)];
    if (piece == nullptr){
        return "";
    }
    std::string geoMoves = piece->getGeoPossibleMoves();
    std::string moves;
    for (int i = 0; i < geoMoves.size()/2; ++i) {
        std::string toPos = geoMoves.substr(i * 2, 2);
        if (legalMove(position+toPos, true, false) || legalMove(position+toPos, true, true)){
            moves.append(toPos);
        }
    }
    return moves;
}
