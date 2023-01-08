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
    bool white_turn = board->getActiveColor() == 'w';
    std::string kingPos = this->board->getKingPosition(white_turn);

    // position of a piece that is threatening the king
    std::string kingThreateners = this->board->sqrThreatener(kingPos, !white_turn, true);
    if (!kingThreateners.empty()){
        if (kingMate(white_turn)){
            return false;
        }
    }

    return true;
}

void ChessGame::gameEnd() {
    //TODO:print winner
}

bool ChessGame::kingMate(bool white_turn) {
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

        bool canEatThreatener = !this->board->sqrThreatener(kingThreateners, white_turn, false).empty();
        if (canEatThreatener){
            return false;
        }

        Piece * kingThreatenerPiece = this->board->getPiece(kingThreateners);
        std::string path = kingThreatenerPiece->getPath(kingPos);
        // if the move is to block the Threatener
        for (int i = 0; i < path.size()/2; ++i) {
            std::string pos = path.substr(i*2, 2);
            if (!this->board->sqrThreatener(pos, white_turn, false).empty()){
                return false;
            }
        }
        return true;
    }
    return false;
}
