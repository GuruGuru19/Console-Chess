cmake_minimum_required(VERSION 3.20)
project(itai_chess)

set(CMAKE_CXX_STANDARD 14)

set(src_files
        src/Piece.cpp
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
        include/Piece.h
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
set(test_files
        tests/TestFEN.cpp
        tests/TestScreen.cpp tests/TestBoard.cpp tests/Prefixes/BoardPrefix.cpp tests/Prefixes/BoardPrefix.h tests/TestPieces/TestQueen.cpp tests/TestPieces/TestRook.cpp tests/TestPieces/BishopTest.cpp tests/TestChessGame.cpp tests/TestPieces/PawnTest.cpp tests/TestPieces/KnightTest.cpp tests/TestPieces/KingTest.cpp)




# testing
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
#testing
add_executable(itai_chess_tests
        ${test_files}
        ${src_files}
        ${include_files}
        )
add_executable(itai_chess main.cpp
        ${src_files}
        ${include_files})
#testing
target_link_libraries(
        itai_chess_tests
        GTest::gtest_main
)
target_link_libraries(
        itai_chess
        GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(itai_chess_tests)
#testing