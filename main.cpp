// CR: why the un-relevant imports?
#include <iostream>
#include <string>
#include "include/Board.h"
#include "include/FEN.h"
#include "include/Screen.h"
#include "include/ChessGame.h"

int main() {
    std::string starting_fen = "rnb1kbnr/pppppppp/8/8/2BQB3/8/PPPPPPPP/1q2K1NR w KQkq - 0 1";
    ChessGame * game = new ChessGame(starting_fen);
    game->runGame();
}
