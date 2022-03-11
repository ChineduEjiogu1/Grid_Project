#include <iostream>
#include <vector>
#include <array>
#include "colorcode.h"

class checkers
{
    private:

    public:
        // checkers();
        const int ROW = 8;
        const int COL = 8;
        const char emptySpace = '-';
        char playerPiece[2] = {'X', 'O'};
        bool currentPlayer = false;
        bool winnerOfGame = false;
        std::array<std::array<int,8>,8> board;
        void intializePiecesOnBoard();
        bool isKing(int, char);
        void printBoard();
        void playerInput(int & row , int & col);
        bool playerMovement(int, int, int, int);
        bool capturePieces();
        bool isEmpty(int, int);
        bool isMoveValid(int, int, int, int);
        void move();
};

void checkers::intializePiecesOnBoard()
{
    for(int row = 0; row < board.size(); row++)
    {
        for(int column = 0; column < board.size(); column++)
        {
            board[row][column] = emptySpace;
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
    char header[] = "   A   B   C   D   E   F   G   H  ";
    std::cout << header << "\n";
    std::cout << " ";
    std::cout << ColorRed("+---+---+---+---+---+---+---+---+");
    std::cout << "\n";

    // Row
    for (int row = 0; row < board.size(); row++)
    {
        std::cout << (row + 1);
        std::cout << ColorRed("|");
        // Column
        for (int column = 0; column < board.size(); column++)
        {
            std::cout << " " << colorElement(board[row][column]) << " ";
            std::cout << ColorRed("|");

            if(column == board.size() - 1)
            {
                std::cout << (row + 1);
            }
        }
        // Printing newline of rows (0 - 2) or (1 - SIZE)
        std::cout << "\n";
        std::cout << " ";
        std::cout << ColorRed("+---+---+---+---+---+---+---+---+");
        std::cout << "\n";
    }

    std::cout << header << "\n";

    std::cout << "\n";

    if (winnerOfGame == false)
    {
        std::cout << "It's player " << playerPiece[currentPlayer] << " turn"
                  << "\n";
    }
}

bool checkers::isEmpty(int row, int column)
{
    return board[row][column] == emptySpace;  
}

bool checkers::isKing(int row, char playerPiece)
{
    for(int row = 0; row < board.size(); row++)
    {
        if(playerPiece == (row == 7) || playerPiece == (row == 0))
        {
            return true;
        }
    }
    return false;
}

/*
    [0,0][0,1][0,2][0,3][0,4][0,5][0,6][0,7]
    [1,0][1,1][1,2][1,3][1,4][1,5][1,6][1,7]
    [2,0][2,1][2,2][2,3][2,4][2,5][2,6][2,7]
    [3,0][3,1][3,2][3,3][3,4][3,5][3,6][3,7]
    [4,0][4,1][4,2][4,3][4,4][4,5][4,6][4,7]
    [5,0][5,1][5,2][5,3][5,4][5,5][5,6][5,7]
    [6,0][6,1][6,2][6,3][6,4][6,5][6,6][6,7]
    [7,0][7,1][7,2][7,3][7,4][7,5][7,6][7,7]
*/

void checkers::playerInput(int & row , int & col)
{
    std::cout << "\n";
    std::cout << "Please enter your desired row and column [" << row << "] [SPACE] [" << col << "]: \n";
    std::cin >> row;
    std::cin >> col;
    std::cout << "\n";

    // https://stackoverflow.com/questions/18728754/checking-cin-input-stream-produces-an-integer
    while (std::cin.fail() || !(row < ROW && col < COL && row >= 0 && col >= 0))
    {
        std::cout << "Invalid input (Integer not found): Enter your desired row and column this way please [" << row << "] [SPACE] [" << col << "]: \n";
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cin >> row;
        std::cin >> col;
    }

    // if (row < ROW && col < COL && row >= 0 && col >= 0)
    // {

    // }
}

 bool checkers::isMoveValid(int startRow, int startCol, int endRow, int endCol)
 {
    if(playerPiece[currentPlayer] == 'O')
    {
        if(startRow - 1 == endRow && (startCol + 1 == endCol) || (startCol - 1 == endCol))
        {
            return true;
        }
    }
    
    std::cout << "in isMoveValid function" << "\n";
    if(playerPiece[currentPlayer] == 'X')
    {
        // startRow = 2, endRow = 3
        // startCol = 3, endCol = 3
        if(startRow + 1 == endRow && (startCol + 1 == endCol) || (startCol - 1 == endCol))
        {
            std::cout << "X move is valid" << "\n";
            return true;
        }
    }

    return false;
 }

void checkers::move()
{
    int startRow, startCol, endRow, endCol = -1;
    do
    {
        std::cout << "Please enter current position of the checker piece" << "\n";
        playerInput(startRow, startCol);
    }while(board[startRow][startCol] != playerPiece[currentPlayer]);

    do
    {
        std::cout << "Please enter destination location of the checker piece" << "\n";
        playerInput(endRow, endCol);
    }while(board[endRow][endCol] != emptySpace);

    // need addition checks for the movement
    if(!isMoveValid(startRow, startCol, endRow, endCol))
    {
        move();
    }

    playerMovement(startRow, startCol, endRow, endCol);
}

bool checkers::playerMovement(int startRow, int startCol, int endRow, int endCol)
{
    // check if the startColumn has the current player piece 
    board[endRow][endCol] = playerPiece[currentPlayer]; 
    board[startRow][startCol] = emptySpace; 

    
    // check if the endpoint is positioned diagonially from startingPoint
    // if it's a regular move by a regular piece it:
        // for the piece which is 'O' the row and will be decreasing by one and column will increase by one
        // for the piece which is 'X' the row and will be increasing by one and column will increase or decrease by one
    // within bounds
    // row > 0 && row <= 7
    // column > 0 && column <= 7

    // isEmpty()
    // return board[rowEnd][columnEnd] == emptySpace;

    // 

    // bool falling, rising = false;

    // for(int row = 0; row < board.size(); row++)
    // {
    //     for (int column = 0; column < board.size(); column++)
    //     {
            
    //         falling = (row == 2 && 0 <= column && column <= 1) || // starting from top-left: falling --> row++ and col++
    //                   (column == 0 && 0 < row && row < 1);

    //         rising = (row == 6 && 0 <= column && column <= 1) || // starting from bottom-left:  rising --> row--,col++
    //                  (column == 0 && 1 <= row && row <= 2);

    //     }
    // }
    return false;
}


