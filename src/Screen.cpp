//
// Created by itai on 1/3/23.
//

#include <algorithm>
#include <iostream>
#include "../include/Screen.h"

// CR: it seems you don't use the COLOR_CLEAR var anywhere
// CR: the convention is to initialize the consts in the header file
// CR: why not make the colors the full code?
const std::string Screen::COLOR_CLEAR = "0";
const std::string Screen::WHITE_TEXT = "97";
const std::string Screen::BLACK_TEXT = "30";
const std::string Screen::GREEN_BACK = "42";
const std::string Screen::BLUE_BACK = "46";
const std::string Screen::RED_BACK = "41";

const std::string Screen::DARK_BACK = GREEN_BACK;
const std::string Screen::LIGHT_BACK = BLUE_BACK;


// CR: spacing
std::string Screen::buildBoardString(FEN & fen) {
    std::string str = "";
    std::string positions = fen.getPositions();

    str.append("   A  B  C  D  E  F  G  H\n");

    int sqr = 0;
    for (int x = 8; x >= 1; --x) {
        str.append(std::to_string(x) + " ");

        for (char y = 'A'; y <= 'H'; ++y) {
            // CR: complex command
            str.append(pieceCode(positions[sqr + (-x+8)], sqr%2==1));
            sqr++;
        }

        str.append(" " + std::to_string(x));
        str.append("\n");
        // CR: why?
        sqr--;
    }

    str.append("   A  B  C  D  E  F  G  H");

    return str;
}

std::string Screen::pieceCode(char c, bool dark) {
    std::string piece;
    // CR: switch-case
    if (c == 'p' || c == 'P'){
        piece = "\u265F";
    }
    else if (c == 'r' || c == 'R'){
        piece = "\u265C";
    }
    else if (c == 'n' || c == 'N'){
        piece = "\u265E";
    }
    else if (c == 'b' || c == 'B'){
        piece = "\u265D";
    }
    else if (c == 'q' || c == 'Q'){
        piece = "\u265B";
    }
    else if (c == 'k' || c == 'K'){
        piece = "\u265A";
    } else{
        piece =" ";
    }
    std::string sqr = dark ? DARK_BACK : LIGHT_BACK;
    if (c>='A' && c<= 'Z'){
        return "\33[" + WHITE_TEXT + ";" + sqr + "m " + piece + " \33[0m";
    }
    else {
        return "\33[" + BLACK_TEXT + ";" + sqr + "m " + piece + " \33[0m";
    }
}

std::string Screen::printMoveDialog(FEN & fen, bool check) {
    std::string turn = fen.isWhiteTurn()? "White" : "Black";
    std::string msg = "=================================\n";
    msg.append(buildBoardString(fen)+ "\n");
    if (check){
        // CR: maybe add a warning theme
        msg.append("\33["+WHITE_TEXT+";"+RED_BACK+"m"+turn+" is checked!!!\33[0m\n");
    }
    msg.append("its " + turn + "'s turn\n");

    // CR: why not use the names you got at the start?
    msg += fen.isWhiteTurn()? 'w' : 'b';
    msg.append(" move: ");
    std::cout << msg;
    std::string move;
    std::cin >> move;
    return move;
}

char Screen::printCrowningDialog(bool white) {
    while (true){
        std::string msg = "=================================\n";
        msg.append("1-Bishop, 2-Knight, 3-Rook, 4-Queen\n");
        msg.append("Crown your Pawn: ");
        std::cout << msg;

        std::string piece_code;
        std::cin >> piece_code;

        // CR: switch-case
        if (piece_code == "1"){
            return white?'B':'b';
        }
        if (piece_code == "2"){
            return white?'N':'n';
        }
        if (piece_code == "3"){
            return white?'R':'r';
        }
        if (piece_code == "4"){
            return white?'Q':'q';
        }
        std::cout << "invalid!\n";
    }
}
