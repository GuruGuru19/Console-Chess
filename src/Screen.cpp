//
// Created by itai on 1/3/23.
//

#include <algorithm>
#include <iostream>
#include "../include/Screen.h"

// CR: the convention is to initialize the consts in the header file
const std::string Screen::COLOR_CLEAR = "[0m";
const std::string Screen::WHITE_TEXT = "97";
const std::string Screen::BLACK_TEXT = "30";
const std::string Screen::GREEN_BACK = "42";
const std::string Screen::BLUE_BACK = "46";
const std::string Screen::RED_BACK = "41";

const std::string Screen::DARK_BACK = GREEN_BACK;
const std::string Screen::LIGHT_BACK = BLUE_BACK;

std::string Screen::buildBoardString(FEN & fen) {
    std::string str;
    std::string positions = fen.getPositions();

    str.append("   A  B  C  D  E  F  G  H\n");

    int sqr = 0;
    bool darkSqr = false;
    for (int x = 8; x >= 1; --x) {
        str.append(std::to_string(x) + " ");

        for (char y = 'A'; y <= 'H'; ++y) {
            str.append(pieceCode(positions[sqr], darkSqr));
            darkSqr = !darkSqr;
            sqr++;
        }

        str.append(" " + std::to_string(x));
        str.append("\n");
        darkSqr = !darkSqr; // when going down a row we need to flip again
    }

    str.append("   A  B  C  D  E  F  G  H");

    return str;
}

std::string Screen::pieceCode(char c, bool dark) {
    std::string piece;
    switch (toupper(c)) {
        case 'P':
            piece = "\u265F";
            break;
        case 'R':
            piece = "\u265C";
            break;
        case 'N':
            piece = "\u265E";
            break;
        case 'B':
            piece = "\u265D";
            break;
        case 'Q':
            piece = "\u265B";
            break;
        case 'K':
            piece = "\u265A";
            break;
        default:
            piece =" ";
            break;
    }

    std::string sqr = dark ? DARK_BACK : LIGHT_BACK;
    if (c>='A' && c<= 'Z'){
        return "\33[" + WHITE_TEXT + ";" + sqr + "m " + piece + " \33" + COLOR_CLEAR;
    }
    else {
        return "\33[" + BLACK_TEXT + ";" + sqr + "m " + piece + " \33" + COLOR_CLEAR;
    }
}

std::string Screen::printMoveDialog(FEN & fen, bool check, const std::string& whiteName, const std::string& blackName) {
    std::string turn = fen.isWhiteTurn()? "White" : "Black";
    std::string msg = "=================================\n";
    msg.append(buildBoardString(fen)+ "\n");
    if (check){
        msg.append(warningMsg(turn+" is checked!!!"));
    }
    msg.append("its " + turn + "'s turn\n");

    msg.append(fen.isWhiteTurn() ? whiteName : blackName);
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

std::string Screen::warningMsg(const std::string& msg) {
    std::string print = "\33["+WHITE_TEXT+";"+RED_BACK+"m"+msg+"\33" + COLOR_CLEAR;
    return print;
}
