cmake_minimum_required(VERSION 3.24)
project(itai_chess)

set(CMAKE_CXX_STANDARD 14)

set(src_files
        src/Pieces/Piece.cpp
        src/Pieces/King.cpp
        src/Pieces/Queen.cpp
        src/Pieces/Rook.cpp
        src/Pieces/Bishop.cpp
        src/Pieces/Knight.cpp
        src/Pieces/Pawn.cpp
        src/Board.cpp
        src/Screen.cpp
        src/ChessGame.cpp
        src/FEN.cpp
        )
set(include_files
        include/Pieces/Piece.h
        include/Pieces/King.h
        include/Pieces/Queen.h
        include/Pieces/Rook.h
        include/Pieces/Bishop.h
        include/Pieces/Knight.h
        include/Pieces/Pawn.h
        include/Board.h
        include/Screen.h
        include/ChessGame.h
        include/FEN.h
        )

add_executable(itai_chess main.cpp ${src_files} ${include_files})
