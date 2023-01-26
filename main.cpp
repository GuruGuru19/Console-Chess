#include <string>
#include "include/ChessGame.h"

#define BOARD_FEN ("r1b3nr/pppk2qp/1bnp4/4p1BQ/2BPP3/2P5/PP3PPP/RN3RK1 w - - 1 12")

int main() {
    std::string starting_fen = BOARD_FEN;
    ChessGame * game = new ChessGame(starting_fen);
    game->runGame();
}
