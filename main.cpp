#include <iostream>
#include <string>
#include "include/Board.h"
#include "include/FEN.h"
#include "include/Screen.h"
#include "include/ChessGame.h"

int main() {
    std::string starting_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    ChessGame * game = new ChessGame(starting_fen);
    game->runGame();
}
