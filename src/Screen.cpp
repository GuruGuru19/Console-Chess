//
// Created by itai on 1/3/23.
//

#include <algorithm>
#include <iostream>
#include "Screen.h"

const std::string Screen::COLOR_CLEAR = "0";
const std::string Screen::WHITE_TEXT = "97";
const std::string Screen::BLACK_TEXT = "30";
const std::string Screen::GREEN_BACK = "42";
const std::string Screen::BLUE_BACK = "46";
const std::string Screen::RED_BACK = "41";

const std::string Screen::DARK_BACK = GREEN_BACK;
const std::string Screen::LIGHT_BACK = BLUE_BACK;

Screen::Screen() {

}

std::string Screen::buildBoardString(FEN & fen) {
    std::string str = "";
    std::string positions = fen.getPositions();
    str.append("   A  B  C  D  E  F  G  H\n");
    int sqr = 0;
    for (int x = 8; x >= 1; --x) {
        str.append(std::to_string(x) + " ");
        for (char y = 'A'; y <= 'H'; ++y) {
            str.append(pieceCode(positions[sqr + (-x+8)], sqr%2==1));
            sqr++;
        }
        str.append(" " + std::to_string(x));
        str.append("\n");
        sqr--;
    }
    str.append("   A  B  C  D  E  F  G  H");
    return str;
}

std::string Screen::pieceCode(char c, bool dark) {
    std::string piece;
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
    std::string turn = fen.getActiveColor() == 'w'?"White":"Black";
    std::string msg = "=================================\n";
    msg.append(buildBoardString(fen)+ "\n");
    if (check){
        msg.append("\33["+WHITE_TEXT+";"+RED_BACK+"m"+turn+" is checked!!!\33[0m\n");
    }
    msg.append("its " + turn + "'s turn\n");

    msg += fen.getActiveColor();
    msg.append(" move: ");
    std::cout << msg;
    std::string move;
    std::cin >> move;
    return move;
}
