//
// Created by itai on 1/3/23.
//

#include <iostream>
#include "../include/ChessGame.h"

ChessGame::ChessGame(std::string & fenstr) {
    FEN * fen = new FEN(fenstr);
    this->board = new Board(*fen);
    this->whiteName = "";
    this->blackName = "";
}

ChessGame::~ChessGame() {
    delete this->board;
}

void ChessGame::runGame() {
    gameStart();
    while (gameLoop());
    gameEnd();
}

void ChessGame::gameStart() {
    std::cout << "Enter player's one (White) name: ";
    std::cin >> this->whiteName;
    std::cout << "Enter player's one (Black) name: ";
    std::cin >> this->blackName;

}

bool ChessGame::gameLoop() {
    bool white_turn = this->board->isWhiteTurn();
    std::string kingPos = this->board->getKingPosition(white_turn);

    // position of a piece that is threatening the king
    std::string kingThreateners = this->board->sqrThreatener(kingPos, !white_turn);
    bool king_checked = !kingThreateners.empty();
    if ((king_checked && kingMate()) || staleMate()){
        return false;
    }

    //TODO: play

    return true;
}

void ChessGame::gameEnd() {
    bool white_turn = board->isWhiteTurn();
    if (kingMate()){

    }
    else if (staleMate()){

    }
    else{

    }
}

bool ChessGame::kingMate() {
    bool white_turn = this->board->isWhiteTurn();
    std::string kingPos = this->board->getKingPosition(white_turn);

    // position of a piece that is threatening the king
    std::string kingThreateners = this->board->sqrThreatener(kingPos, !white_turn, true);
    if (!kingThreateners.empty()){ // the (active_color)'s king is checked
        //if the king can run away
        if (!this->board->getLegalMoves(kingPos).empty()){
            return false;
        } else if (kingThreateners.size() > 2){
            return true; // if there are more than 1 Threatener the king can only run away
        }

        bool canEatThreatener = this->board->sqrThreatener(kingThreateners, !white_turn, true).empty() &&
                board->legalEatMove(kingPos+kingThreateners);
        if (canEatThreatener){
            return false;
        }

        Piece * kingThreatenerPiece = this->board->getPiece(kingThreateners);
        std::string path = kingThreatenerPiece->getPath(kingPos);
        // if the move is to block the Threatener
        for (int i = 0; i < path.size()/2; ++i) {
            std::string pos = path.substr(i*2, 2);
            std::string path_blocker_pos = this->board->sqrThreatener(pos, white_turn, false, false).substr(0,2);
            if (!path_blocker_pos.empty() &&
            (this->board->getPiece(path_blocker_pos)->getMark()!='K' && this->board->getPiece(path_blocker_pos)->getMark()!='k')){
                return false;
            }
        }
        return true;
    }
    return false;
}

bool ChessGame::staleMate() {
    if (kingMate()){
        return false;
    }
    bool white_turn = this->board->isWhiteTurn();
    for (int i = 0; i < 64; ++i) {
        std::string pos = Board::sqrToPosition(i);
        Piece * piece = this->board->getPiece(pos);
        if (piece != nullptr && (piece->isWhite() == white_turn) && !this->board->getLegalMoves(pos).empty()){
            return false; // for every (same color) piece -> do you have possible moves?
        }
    }
    return true; // if none of the color's pieces have moves
}
