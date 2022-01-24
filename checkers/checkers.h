#include <iostream>
#include <vector>
#include <array>
#include "colorcode.h"

class checkers
{
    private:

    public:
        // checkers();
        char pieces[2] = {'X', 'O'};
        bool winnerOfGame = false;
        std::array<std::array<int,8>,8> board;
        void intializePiecesOnBoard();
        bool isKing();
        void printBoard();
        bool playerMovement();
        bool capturePieces();

};

void checkers::intializePiecesOnBoard()
{
    for(int row = 0; row < board.size(); row++)
    {
        for(int column = 0; column < board.size(); column++)
        {
            board[row][column] = '-';
            board[0][1] = 'X';
            board[0][3] = 'X';
            board[0][5] = 'X';
            board[0][7] = 'X';
            board[1][0] = 'X';
            board[1][2] = 'X';
            board[1][4] = 'X';
            board[1][6] = 'X';
            board[2][1] = 'X';
            board[2][3] = 'X';
            board[2][5] = 'X';
            board[2][7] = 'X';

            board[7][0] = 'O';
            board[7][2] = 'O';
            board[7][4] = 'O';
            board[7][6] = 'O';
            board[6][1] = 'O';
            board[6][3] = 'O';
            board[6][5] = 'O';
            board[6][7] = 'O';
            board[5][0] = 'O';
            board[5][2] = 'O';
            board[5][4] = 'O';
            board[5][6] = 'O';
        }
    }    
}


void checkers::printBoard()
{
    // char header[] = "  1   2   3   4   5   6   7   8";
    //std::cout << header << "\n";
    std::cout << ColorRed("+---+---+---+---+---+---+---+---+");
    std::cout << "\n";

    // Row
    for (int row = 0; row < board.size(); row++)
    {
        std::cout << ColorRed("|");
        // Column
        for (int column = 0; column < board.size(); column++)
        {
            std::cout << " " << colorElement(board[row][column]) << " ";
            std::cout << ColorRed("|");
        }
        // Printing newline of rows (0 - 2) or (1 - SIZE)
        std::cout << "\n";
        std::cout << ColorRed("+---+---+---+---+---+---+---+---+");
        std::cout << "\n";
    }

    std::cout << "\n";

    if (winnerOfGame == false)
    {
        std::cout << "It's player " << pieces << " turn"
                  << "\n";
    }
}

