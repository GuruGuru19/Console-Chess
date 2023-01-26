//
// Created by itai on 1/3/23.
//

#include "../include/Board.h"
#include "../include/Pieces/Pawn.h"
#include "../include/Pieces/Rook.h"
#include "../include/Pieces/Knight.h"
#include "../include/Pieces/Bishop.h"
#include "../include/Pieces/Queen.h"
#include "../include/Pieces/King.h"


Board::Board(FEN &fen) {
    this->boardFEN = new FEN(fen);
    int i = 0;
    for (char c: this->boardFEN->getPositions()) { // for every char in the FEN's positions make a new Piece
        if (c == ' '){
            board[i] = nullptr;
        }
        std::string pos = sqrToPosition(i);
        switch (toupper(c)) {
            case 'P':
                board[i] = new Pawn(pos, c == 'P');
                break;
            case 'R':
                board[i] = new Rook(pos, c == 'R');
                break;
            case 'N':
                board[i] = new Knight(pos, c == 'N');
                break;
            case 'B':
                board[i] = new Bishop(pos, c == 'B');
                break;
            case 'Q':
                board[i] = new Queen(pos, c == 'Q');
                break;
            case 'K':
                board[i] = new King(pos, c == 'K');
                break;
        }
        i++;
    }
}

Board::~Board() {
    delete this->boardFEN; // deletes the fen
    for (auto & i : this->board) { // deletes the pieces
        delete i;
    }
    //free(this->board);
}

//TODO: better name for threateningCheck
bool Board::legalMove(const std::string & move, bool pinnedPieceCantMove, bool toEat, bool threateningCheck) {
    std::string fromPos = move.substr(0,2); // position of the piece
    std::string toPos = move.substr(2); // position to move the piece

    if (!isPositionOnBoard(fromPos) || !isPositionOnBoard(toPos)){ // the move is outside the board
        return false;
    }

    if (fromPos == toPos){ // trying to move to the same place
        return false;
    }

    Piece * piece = this->board[positionToSqr(fromPos)];

    if (piece == nullptr){
        return false;// trying to move an empty sqr
    }

    if (!piece->canMoveGeo(toPos) && !piece->canMoveGeoToEat(toPos)){
        return false;
    }

    Piece * pieceAtTarget = this->board[positionToSqr(toPos)];

    if (!threateningCheck && toEat && pieceAtTarget != nullptr && (pieceAtTarget->isWhite() == piece->isWhite())){
        return false; //trying to eat the same color
    }
    if (!toEat && pieceAtTarget != nullptr){
        return false; //trying to move to an occupied sqr
    }

    if (pinnedPieceCantMove){
        //trying to move a king
        if (piece->getMark() == 'K' || piece->getMark() == 'k'){
            std::string kingThreatener = sqrThreatener(fromPos, !piece->isWhite(), true);
            std::string kingPath = piece->getPath(toPos); // if the king has a path is a castling move
            // trying to move a king to Threatened sqr
            if (!sqrThreatener(toPos, !piece->isWhite(), true).empty()||
                !sqrThreatener(kingPath, !piece->isWhite(), true).empty()){
                return false;
            }
            if (!kingThreatener.empty() && toPos != kingThreatener && movePathClear(kingThreatener+toPos, fromPos)){ // assumes that there is only one threatener
                return false;
            }

            King * king = dynamic_cast<King *>(piece);
            int casling = king->isCastling(toPos); // return what type of castling we are trying to do 1=woo, 2=wooo, 3=boo, 4=booo, 0= not a castling
            if (casling == 1 && (!this->boardFEN->canWooCastle() || !movePathClear("h1e1"))){
                return false;// the rook can preform this move
            }
            if (casling == 2 && (!this->boardFEN->canWoooCastle() || !movePathClear("a1e1"))){
                return false;// the rook can preform this move
            }
            if (casling == 3 && (!this->boardFEN->canBooCastle() || !movePathClear("h8e8"))){
                return false;// the rook can preform this move
            }
            if (casling == 4 && (!this->boardFEN->canBoooCastle() || !movePathClear("a8e8"))){
                return false;// the rook can preform this move
            }
        }
            // tests if your trying to move while the king is checked
        else {
            std::string kingPos = getKingPosition(piece->isWhite());
            std::string kingThreatenerPos = this->sqrThreatener(kingPos, !piece->isWhite(), true);
            //if the king is checked and this move doesn't fix it +
            // assumes that there is only one threatener cause else this code isn't reachable
            //the only way to be saved from a 2 threateners check is by moving the king and that code is above
            if (!kingThreatenerPos.empty()){
                Piece * kingThreatener = this->board[positionToSqr(kingThreatenerPos)];
                std::string threatener_path = kingThreatener->getPath(kingPos);
                bool tryingToEatThreat = toPos == kingThreatenerPos;
                bool tryingToBlockThreat = threatener_path.find(toPos) < threatener_path.size();
                if (not (tryingToEatThreat || tryingToBlockThreat)){
                    return false;
                }
            }

        }
    }
    if (!threateningCheck && toEat && pieceAtTarget == nullptr){// trying to eat an empty sqr

        bool toPosIsEnPassantPos = toPos == this->boardFEN->getEnPassant();
        bool pieceIsCorrectPawn = this->boardFEN->isWhiteTurn()? piece->getMark() == 'P' : piece->getMark() == 'p';
        bool enPassant = toPosIsEnPassantPos && pieceIsCorrectPawn;

        if (not enPassant){// trying to eat an empty sqr & not En passant!
            return false;
        }
    }

    bool pinned = pinnedPieceCantMove && toupper(piece->getMark()) != 'K' && piecePinned(fromPos);// a king cant be pinned
    bool geometrically_legal = toEat ? piece->canMoveGeoToEat(toPos) : piece->canMoveGeo(toPos);
    bool move_path_clear = movePathClear(move);
    return !pinned && geometrically_legal && move_path_clear;
}

// CR: ordering
Piece * Board::getPiece(std::string & position) {
    if (!isPositionOnBoard(position)){ // the position is outside the board
        return nullptr;
    }
    return this->board[positionToSqr(position)]; // the position is inside the board
}

std::string Board::getKingPosition(bool white) {
    char target = white ? 'K' : 'k'; // what would the king's mark be
    for (int i = 0; i < 64; ++i) {
        if (this->board[i] != nullptr && this->board[i]->getMark() == target){ // checks every sqr for the king
            return sqrToPosition(i);
        }
    }
    return "";
}

bool Board::piecePinned(const std::string & position) {
    if (not isPositionOnBoard(position)){
        return false; // the position is outside the board (only gets here in tests)
    }

    Piece * piece = this->board[positionToSqr(position)];
    if (piece == nullptr){
        return false; // there is no piece at the position
    }
    std::string kingPos = getKingPosition(piece->isWhite());

    for (Piece * pinner : this->board) {
        // sets every sqr in a loop as a potential pinner
        if (pinner != nullptr && (pinner->isWhite() != piece->isWhite())){ // is an enemy piece
            std::string path = pinner->getPath(kingPos); //gets the pinner path to the king
            bool flag = false;
            for (int j = 0; j < path.size()/2; ++j) {
                if (this->board[positionToSqr(path.substr(j*2, 2))] != nullptr){ // there is a piece in its way
                    if (path.substr(j*2, 2) == position){ // it's the piece we look for
                        flag = true;
                    } else{
                        return false; // if it's not the piece we search for then it's not pinned
                    }
                }
            }
            if (flag){
                // if the only piece that in the pinner's path -> is pinned
                return true;
            }
        }
    }
    return false;
}

bool Board::movePathClear(const std::string & move, const std::string & ignorePos) {
    std::string fromPos = move.substr(0,2); // position of the piece
    std::string toPos = move.substr(2); // position to move the piece

    Piece * piece = this->board[positionToSqr(fromPos)];
    if (piece == nullptr){
        return false;// trying to move an empty sqr
    }

    if (!piece->canMoveGeo(toPos) && !piece->canMoveGeoToEat(toPos)){ // doesn't check the eatGeo cause its only relevant to the pawn
        return false;// the piece can't move that way geometrically
    }
    // CR: don't you repeat this check few times?
    std::string path = piece->getPath(toPos);
    for (int i = 0; i < path.size()/2; ++i) {
        std::string pos = path.substr(i*2, 2);
        if (pos != ignorePos && this->board[positionToSqr(pos)] != nullptr){
            return false;// found a piece in the way
        }
    }
    return true; // no problem
}

std::string Board::sqrThreatener(const std::string& position, bool threatenedByWhite, bool ignorePinned, bool moveToEat) { // always ignores pins
    if (position.empty() || positionToSqr(position) < 0 || positionToSqr(position) >= 64){ // the position is invalid
        return "";
    }
    std::string threateners; // empty string
    for (int i = 0; i < 64; ++i) {
        Piece * p = this->board[i]; // every piece as a potential threatener

        bool correct_color_piece = p != nullptr && p->isWhite() == threatenedByWhite;
        if (correct_color_piece && legalMove(sqrToPosition(i)+position,!ignorePinned, moveToEat, true)){ // & the move is legal
            threateners.append(sqrToPosition(i)); // adds its position to the list
        }
    }
    return threateners;
}

int Board::positionToSqr(std::string position) {
    int x = position[0] - 'a'; // 'a' is the first column
    int y = '8' - position[1]; // '8' is the first column
    return x + y * 8;
}

std::string Board::sqrToPosition(int sqr) {
    char x = (char)('a' + (sqr%8));
    char y = (char)('8' - (sqr/8));
    std::string p;
    p += x;
    p += y;
    return p;
}

// only for testing!!!!!!
std::string Board::printBoard() {
    std::string print;
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            Piece * piece = this->board[x + y * 8];
            if (piece == nullptr){
                print += " ";
            }
            else{
                print += this->board[x + y * 8]->getMark();
            }
        }
        print += "\n";
    }
    return print;
}

bool Board::move(const std::string & move) {
    bool legal_move = legalMove(move); // is the move legal
    bool legal_eat_move = legalEatMove(move); // is the move a legal eat move

    if (!(legal_move || legal_eat_move)){ // remember for later ! they cant both be true
        return false;
    }

    std::string fromPos = move.substr(0,2); // position of the piece
    std::string toPos = move.substr(2); // position to move the piece
    Piece * piece = this->board[positionToSqr(fromPos)]; // piece to move

    std::string enPassant; // reset
    bool woo = this->boardFEN->canWooCastle();
    bool wooo = this->boardFEN->canWoooCastle();
    bool boo = this->boardFEN->canBooCastle();
    bool booo = this->boardFEN->canBoooCastle();

    if (piece->getMark() == 'p' || piece->getMark() == 'P'){ //if it's a pawn
        enPassant = piece->getPath(toPos);// save the path as the en passant
    }
    else if(piece->getMark() == 'K'){ // if the white king moves
        this->boardFEN->setWooCastling(false);
        this->boardFEN->setWoooCastling(false);
    }
    else if(piece->getMark() == 'k'){ // if the black King moves
        this->boardFEN->setBooCastling(false);
        this->boardFEN->setBoooCastling(false);
    }
    else if (!woo && fromPos == "h1"){ // is the rook moves
        this->boardFEN->setWooCastling(false);
    }
    else if (!wooo && fromPos == "a1"){
        this->boardFEN->setWoooCastling(false);
    }
    else if (!boo && fromPos == "h8"){
        this->boardFEN->setBooCastling(false);
    }
    else if (!booo && fromPos == "a8"){
        this->boardFEN->setBoooCastling(false);
    }

    this->board[positionToSqr(fromPos)] = nullptr; // puts a null where the piece is moved from
    if (legal_move){
        if (move == "e1g1"){ // if it's a white o-o castling
            // move the rook h1f1
            Piece * rook =  this->board[positionToSqr("h1")];
            this->board[positionToSqr("h1")] = nullptr;
            this->board[positionToSqr("f1")] = rook;
            rook->setPosition("f1");
        }
        else if (move == "e1c1"){ // if it's a white o-o-o castling
            // move the rook a1d1
            Piece * rook =  this->board[positionToSqr("a1")];
            this->board[positionToSqr("a1")] = nullptr;
            this->board[positionToSqr("d1")] = rook;
            rook->setPosition("d1");
        }
        else if (move == "e8g8"){ // if it's a black o-o castling
            // move the rook h8f8
            Piece * rook =  this->board[positionToSqr("h8")];
            this->board[positionToSqr("h8")] = nullptr;
            this->board[positionToSqr("f8")] = rook;
            rook->setPosition("f8");
        }
        else if (move == "e8c8"){ // if it's a black o-o-o castling
            // move the rook a8d8
            Piece * rook =  this->board[positionToSqr("a8")];
            this->board[positionToSqr("a8")] = nullptr;
            this->board[positionToSqr("d8")] = rook;
            rook->setPosition("d8");
        }
    }
    else{ // eating
        std::string removePos;
        if (this->board[positionToSqr(toPos)] == nullptr){ //it's a legal eat so if the target sqr is empty it means it's an En Passant
            std::string targetPos = this->boardFEN->getEnPassant();
            targetPos[1] += piece->isWhite() ? -1 : 1; // the pawn position to eat

            removePos = targetPos;
        }
        else{ // not En Passant
            removePos = toPos;
        }

        delete this->board[positionToSqr(removePos)]; // delete the eaten piece
        this->board[positionToSqr(removePos)] = nullptr;

    }
    this->board[positionToSqr(toPos)] = piece; // puts the piece in its target position

    piece->setPosition(toPos); // updates the piece's internal position

    this->boardFEN->update(this->board, enPassant, legal_eat_move); // updates the FEN's internal data
    return true; // the move is complete
}

// CR: what other more useful func can you make in this style?
std::string Board::getLegalMoves(const std::string & position) {
    Piece * piece = this->board[positionToSqr(position)];
    if (piece == nullptr){ // there is no piece at (position)
        return "";
    }
    std::string geoMoves = piece->getGeoPossibleMoves(); // gets the piece's geometrical legal moves
    std::string moves;
    for (int i = 0; i < geoMoves.size()/2; ++i) {
        std::string toPos = geoMoves.substr(i * 2, 2);
        // if the move is legal in any way
        if (legalMove(position+toPos, true, false) || legalMove(position+toPos, true, true)){
            moves.append(toPos); // adds the end position
        }
    }
    return moves;
}

void Board::setPiece(Piece * new_piece) {
    int sqr = positionToSqr(new_piece->getPosition()); // new piece's sqr on the board
    delete this->board[sqr]; // delete what ever was in the sqr before (usually a pawn)
    this->board[sqr] = new_piece; // sets the new piece in the board
    this->boardFEN->update(this->board,
                           "", false, true); // updates the FEN
}
