#include <iostream>
#include <string>
#include "src/Board.h"
#include "src/FEN.h"
#include "src/Screen.h"

int main() {
    std::string fen_string =  "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    FEN * fen = new FEN(fen_string);
    std::string string = fen->getPositions();
    Screen * screen = new Screen();
    //std::string str = screen -> buildBoardString(*fen);

    std::cout << screen->printMoveDialog(*fen, true) << std::endl;
}
