#include <string>
#include "include/ChessGame.h"

int main() {
    std::string starting_fen = "rnb2bnr/ppppk2p/8/1BN2pP1/4B3/1Q6/PPPPPP1P/Rq2K1NR w KQ - 0 1";
    ChessGame * game = new ChessGame(starting_fen);
    game->runGame();
}
