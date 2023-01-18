#include <iostream>
#include <string>
#include "include/Board.h"
#include "include/FEN.h"
#include "include/Screen.h"
#include "include/ChessGame.h"

int main() {
    std::string starting_fen = "4k3/R7/8/8/8/8/8/K1R2R2 w - - 0 1";
    ChessGame * game = new ChessGame(starting_fen);
    game->runGame();
}
