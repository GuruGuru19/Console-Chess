//
// Created by itai on 1/3/23.
//

#include <iostream>
#include "../include/ChessGame.h"
#include "../include/Pieces/Queen.h"
#include "../include/Pieces/Bishop.h"
#include "../include/Pieces/Knight.h"
#include "../include/Pieces/Rook.h"

ChessGame::ChessGame(std::string & fenstr) {
    FEN * fen = new FEN(fenstr);
    this->board = new Board(*fen);
    this->whiteName = "";
    this->blackName = "";
    delete fen;
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
    // CR: sectioning and commenting
    bool white_turn = this->board->isWhiteTurn();
    FEN * fen = this->board->getFEN();
    std::string kingPos = this->board->getKingPosition(white_turn);


    if (kingMate() || staleMate()){ // if the game needs to end
        std::cout << Screen::buildBoardString(*fen) << std::endl;
        return false;
    }

    std::string move;
    // CR: change the true & break
    while (true){  // until the move is legal
        // position of a piece that is threatening the king
        std::string kingThreateners = this->board->sqrThreatener(kingPos, !white_turn);
        bool king_checked = !kingThreateners.empty();
        move = Screen::printMoveDialog(*fen, king_checked);
        if (this->board->legalMove(move) || this->board->legalEatMove(move)){
            break;
        }
        std::cout << "=================================" << std::endl;
        // CR: should print white on red
        std::cout << "Illegal move! try again" << std::endl;
    }

    this->board->move(move); // make the move

    std::string crowning_pos = Crowning();
    // CR: encapsulate
    if (!crowning_pos.empty()){ // the move result in a crowning
        char new_mark = Screen::printCrowningDialog(white_turn); // gets the new piece mark
        Piece * piece;
        // puts it on the board
        if (new_mark == 'r' || new_mark == 'R'){
            piece = new Rook(crowning_pos, new_mark == 'R');
            this->board->setPiece(piece);
        }
        else if (new_mark == 'n' || new_mark == 'N'){
            piece = new Knight(crowning_pos, new_mark == 'N');
            this->board->setPiece(piece);
        }
        else if (new_mark == 'b' || new_mark == 'B'){
            piece = new Bishop(crowning_pos, new_mark == 'B');
            this->board->setPiece(piece);
        }
        else if (new_mark == 'q' || new_mark == 'Q'){
            piece = new Queen(crowning_pos, new_mark == 'Q');
            this->board->setPiece(piece);
        }
        else{
            std::cout << "\nERROR\n\n"; // isn't supposed to get here
        }
    }

    return true;
}

// CR: ordering
void ChessGame::gameEnd() {
    bool white_turn = board->isWhiteTurn();
    // print the game result
    if (kingMate()){
        std::string msg = "\33["+Screen::WHITE_TEXT+";"+Screen::RED_BACK+"mCheck mate!\33[0m\n";
        std::cout << msg << (white_turn? "Black (": "White (") << (white_turn? this->blackName: this->whiteName) << ") wins!";
    }
    else if (staleMate()){
        std::string msg = "\33["+Screen::WHITE_TEXT+";"+Screen::RED_BACK+"mStale mate!\33[0m\n";
        std::cout << msg << "Draw!";
    }
    // CR: why the else without anything?
    else{

    }
}

// CR: would have gotten the white_turn
// CR: not good naming
std::string ChessGame::Crowning() {
    // this code is run after the move
    bool white_turn = !this->board->isWhiteTurn();

    // CR: could be shortened
    if (white_turn){
        for (int i = 0; i < 8; ++i) { // search for a pawn on the '8' line
            std::string pos = Board::sqrToPosition(i);
            Piece * piece = this->board->getPiece(pos);
            if (piece != nullptr && piece->getMark() == 'P'){
                return pos;
            }
        }
    }
    else{
        for (int i = 56; i < 64; ++i) { // search for a pawn on the '1' line
            std::string pos = Board::sqrToPosition(i);
            Piece * piece = this->board->getPiece(pos);
            if (piece != nullptr && piece->getMark() == 'p'){
                return pos;
            }
        }
    }
    return "";
}

bool ChessGame::kingMate() {
    bool white_turn = this->board->isWhiteTurn();
    std::string kingPos = this->board->getKingPosition(white_turn); // king's position

    // position of a piece that is threatening the king
    std::string kingThreateners = this->board->sqrThreatener(kingPos, !white_turn, true);
    if (kingThreateners.empty()){
        return false;
    }

    if (!this->board->getLegalMoves(kingPos).empty()){
        return false; //if the king can run away
    } else if (kingThreateners.size()/2 > 1){ // if there are more than 1 Threatener the king can only run away
        return true;
    }

    // CR: change logic
    bool kingCanEatThreatener = this->board->sqrThreatener(kingThreateners, !white_turn, true).empty() &&
                                board->legalEatMove(kingPos+kingThreateners);
    if (kingCanEatThreatener){ // if someone can eat the threatener
        return false;
    }

    Piece * kingThreatenerPiece = this->board->getPiece(kingThreateners);
    std::string path = kingThreatenerPiece->getPath(kingPos); // the path the threatener needs to take
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
    return true; // if none of the color's pieces have legal moves -> stale mate
}
