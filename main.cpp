#include <iostream>
#include <string>
#include "include/Board.h"
#include "include/FEN.h"
#include "include/Screen.h"

int main() {
    std::string fen_string =  "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w Kkq - 0 1";
    FEN * fen = new FEN(fen_string);
    std::string string = fen->getPositions();
    Screen * screen = new Screen();
    Board * board = new Board(*fen);
    board->printBoard();
    std::cout << screen->printMoveDialog(*fen, false) << std::endl;

}
