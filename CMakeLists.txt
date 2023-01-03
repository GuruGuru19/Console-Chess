cmake_minimum_required(VERSION 3.24)
project(itai_chess)

set(CMAKE_CXX_STANDARD 14)

set(src_files
        src/Pieces/Piece.cpp
        src/Pieces/Piece.h
        src/Pieces/King.cpp
        src/Pieces/King.h
        src/Pieces/Queen.cpp
        src/Pieces/Queen.h
        src/Pieces/Rook.cpp
        src/Pieces/Rook.h
        src/Pieces/Bishop.cpp
        src/Pieces/Bishop.h
        src/Pieces/Knight.cpp
        src/Pieces/Knight.h
        src/Pieces/Pawn.cpp
        src/Pieces/Pawn.h
        src/Board.cpp
        src/Board.h
        src/Screen.cpp
        src/Screen.h
        src/ChessGame.cpp
        src/ChessGame.h
        src/FEN.cpp
        src/FEN.h
        )

add_executable(itai_chess main.cpp ${src_files})
