//
// Created by itai on 1/3/23.
//

#include "ChessGame.h"

ChessGame::ChessGame() {
    FEN * fen = new FEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    this->board = new Board(*fen);
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
    //TODO: players names

}

bool ChessGame::gameLoop() { //returns false when the game ends
    bool white_turn = board->getActiveColor() == 'w';
    std::string kingPos = this->board->getKingPosition(white_turn);

    // position of a piece that is threatening the king
    std::string kingThreatener = this->board->SqrThreatener(kingPos, !white_turn, true);
    if (!kingThreatener.empty()){ // the (active_color)'s king is checked
        bool safeSqrFlag = false;
        //searches 3x3 around the king for empty untethered sqr
        for (int y = kingPos[1] - 1; y <= kingPos[1] + 1 && !safeSqrFlag; ++y) {
            for (int x = kingPos[0] - 1; x <= kingPos[0] + 1; ++x) {
                std::string target = "  ";target[0] = (char)x;target[1] = (char)y;
                //first check: can the king move to the target
                //second check: is the target threatened
                //the first check doesn't consider that a king cant move to a threatened sqr
                //and the second check doesn't consider that a threatener can be pinned
                if (this->board->legalMove(kingPos+target, false, true) && // its ok toEat:true because It's the king, so it's the same check true of false
                    !this->board->SqrThreatener(target, !white_turn, true).empty()){
                    safeSqrFlag = true;
                    break;
                }
            }
        }
        bool canEatThreatener = !this->board->SqrThreatener(kingThreatener, white_turn, false).empty();

        //TODO: last mate check: can you block an attack?
    }

}

void ChessGame::gameEnd() {
    //TODO:print winner
}
