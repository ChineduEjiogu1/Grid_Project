// https://www.youtube.com/watch?v=TjOnDt_vBaY

#include <iostream>
#include <string>
#include <regex>

#define SIZE_1 6
#define SIZE_2 7
#define WINNING_PATTERN 4

const std::string SIZEOFGRID = "2";
const char players[2] = {'O', 'X'};

std::string ColorBlue(char z)
{
    return "\e[01;34m" + std::string(1, z) + "\e[0m";
}

std::string ColorYellow(char q)
{
    return "\e[01;33m" + std::string(1, q) + "\e[0m";
}

std::string ColorGreen(char w)
{
    return "\e[01;32m" + std::string(1, w) + "\e[0m";
}

std::string colorElement(char s)
{
    if (s == 'O')
        return ColorGreen(s);
    if (s == 'X')
        return ColorBlue(s);
    else
        return ColorYellow(s);
}

bool checkEmptyBoard(char board[SIZE_1][SIZE_2])
{
    // My Row, X or I
    for (int x = 0; x < SIZE_1; x++)
    {
        // My colunm, Y or J
        for (int y = 0; y < SIZE_2; y++)
        {
            if (board[x][y] == ' ')
            {
                continue;
            }
            else
            {
                return false;
            }
        }
    }

    return true;
}

bool findWinnerHorizontial(char board[SIZE_1][SIZE_2])
{
    // 1. Visit every cell with nested for loop
    // 2. Look at each character to see if their in consecutive rows
    // 2a. Check to see if it's a uppercase "X" or "O"
    // 2b. Compare the next index (Y + 1)
    // 2c. If they are equal,compare the next neighboring index.

    for (int x = 0; x < SIZE_1 - 1; x++)
    {
        for (int y = 0; y < SIZE_2 - 1; y++)
        {
            if (board[x][0] == 'X' || board[x][0] == 'O')
            {
                if (board[0][y++] == board[x][WINNING_PATTERN - 1] || board[1][y++] == board[x][WINNING_PATTERN - 1] || board[x][y++] == board[x][WINNING_PATTERN - 1] ||
                    board[3][y++] == board[x][WINNING_PATTERN - 1] || board[4][y++] == board[x][WINNING_PATTERN - 1] || board[x][y++] == board[x][WINNING_PATTERN - 1])
                {
                    std::cout << "The winner is horizontial: " << board[0][y] << "\n";
                    return true;
                }               
            }
        }
    }

    return false;
}

bool findWinnerVertical(char board[SIZE_1][SIZE_2])
{
    for (int x = 0; x < SIZE_1 - 1; x++)
    {
        for (int y = 0; y < SIZE_2 - 1; y++)
        {
            if (board[0][y] == 'X' || board[0][y] == 'O')
            {
                if (board[x++][0] == board[WINNING_PATTERN - 1][y] || board[x++][1] ==  board[WINNING_PATTERN - 1][y] || board[x++][2] == board[WINNING_PATTERN - 1][y] || board[x++][3] == board[WINNING_PATTERN - 1][y]
                || board[x++][4] == board[WINNING_PATTERN - 1][y] || board[x++][5] == board[WINNING_PATTERN - 1][y])
                {
                    std::cout << "The winner is vertical: " << board[x][0] << "\n";
                    return true;
                }
            }
        }
    }
    
    return false;
}

bool findWinnerDiagonial(char board[SIZE_1][SIZE_2])
{
    for (int x = 0; x < SIZE_1 - 1; x++)
    {
        for (int y = 0; y < SIZE_2 - 1; y++)
        {
            if (board[x][y] == 'X' || board[x][y] == 'O')
            {
                if (board[x][y] == (x == y))
                {
                    std::cout << "The winner is diagonal: " << board[3][3] << "\n";
                    return true;
                }
                
                //int total = 0;
                if ( board[x][y] == ((x + y) % 2) == 0 )
                {
                    std::cout << "The winner is diagonal: " << board[3][3] << "\n";
                    return true;
                }
            }
        }
    }
    
    return false;
}

void printConnect4(char board[SIZE_1][SIZE_2], bool player, const bool winner)
{

    std::cout << "+---+---+---+---+---+---+---+";
    std::cout << "\n";

    // Row
    for (int i = 0; i < SIZE_1; i++)
    {
        std::cout << "|";
        // Column
        for (int j = 0; j < SIZE_2; j++)
        {
            std::cout << " " << colorElement(board[i][j]) << " ";
            std::cout << "|";
        }
        // Printing newline of rows (0 - 2) or (1 - SIZE)
        std::cout << "\n";
        std::cout << "+---+---+---+---+---+---+---+";
        std::cout << "\n";
    }

    std::cout << "\n";
    
    if (winner == false)
    {
        std::cout << "The player is: " << players[player] << "\n";
    }
}

bool winner(char board[SIZE_1][SIZE_2])
{
    return (findWinnerHorizontial(board) || findWinnerVertical(board) || findWinnerDiagonial(board));
}

bool hasEmptyProperties(char emptyBoard[SIZE_1][SIZE_2])
{

    for (int row = 0; row < SIZE_1; row++)
    {
        for (int column = 0; column < SIZE_2; column++)
        {
            if (emptyBoard[row][column] == ' ')
            {
                return true;
            }
        }
    }

    std::cout << "\n";
    std::cout << "Failed to find empty space on the game board\n";
    return false;
}

bool tests()
{

    char emptyBoard[SIZE_1][SIZE_2];

    for (int row = 0; row < SIZE_1; row++)
    {
        for (int column = 0; column < SIZE_1; column++)
        {
            emptyBoard[row][column] = ' ';
        }
    }

    bool test1 = checkEmptyBoard(emptyBoard);

    char notAnEmptyBoard[SIZE_1][SIZE_2];

    bool test2 = !checkEmptyBoard(notAnEmptyBoard);

    char winningBoardHorizontial[SIZE_1][SIZE_2] = {{'X', 'X', 'O', 'O', 'O', 'O', 'X'}, // line 1 or 0 (row) of the board/grid (O is the answer)
                                                    {'X', 'X', 'X', 'O', 'O', 'X', 'O'},
                                                    {'O', 'X', 'X', 'X', 'O', 'O', 'O'},
                                                    {'X', 'X', 'X', 'O', 'X', 'O', 'O'},
                                                    {'X', 'O', 'X', 'O', 'O', 'X', 'O'}, 
                                                    {'X', 'X', 'X', 'O', 'X', 'O', 'O'}};

    bool test3 = findWinnerHorizontial(winningBoardHorizontial);

    char winningBoardVertical[SIZE_1][SIZE_2] = {{'X', 'X', 'O', 'O', 'O', 'O', 'X'}, //  column 2 of the board/grid (X is the answer)
                                                 {'X', 'X', 'X', 'O', 'O', 'X', 'O'},
                                                 {'O', 'X', 'X', 'X', 'O', 'O', 'O'},
                                                 {'X', 'X', 'X', 'O', 'X', 'O', 'X'},
                                                 {'X', 'O', 'O', 'O', 'O', 'X', 'O'}, 
                                                 {'X', 'X', 'X', 'O', 'X', 'O', 'O'}};

    bool test4 = findWinnerVertical(winningBoardVertical);

    char winningBoardDiagonal[SIZE_1][SIZE_2] = {{'X', 'X', 'O', 'O', 'O', 'O', 'X'}, //  Diagonal in the middle of board (O is the answer)
                                                 {'X', 'X', 'X', 'O', 'O', 'X', 'O'},
                                                 {'O', 'X', 'X', 'X', 'O', 'O', 'O'},
                                                 {'X', 'X', 'X', 'O', 'X', 'O', 'X'},
                                                 {'X', 'O', 'O', 'O', 'O', 'X', 'O'}, 
                                                 {'X', 'X', 'X', 'O', 'X', 'O', 'O'}};

    bool test5 = findWinnerDiagonial(winningBoardDiagonal);

    char winningBoardDiagonal2[SIZE_1][SIZE_2] = {{'X', 'X', 'O', 'O', 'O', 'O', 'X'}, //  Diagonal in the middle of board (X is the answer)
                                                  {'X', 'X', 'X', 'O', 'O', 'X', 'O'},
                                                  {'O', 'X', 'X', 'X', 'O', 'O', 'O'},
                                                  {'X', 'O', 'O', 'X', 'X', 'x', 'X'},
                                                  {'X', 'O', 'O', 'O', 'O', 'X', 'O'}, 
                                                  {'X', 'X', 'X', 'O', 'X', 'O', 'O'}};

    bool test6 = findWinnerDiagonial(winningBoardDiagonal2);


    return (test1 && test2 || test3 || test4 || test5 || test6);
}


int main()
{
    bool results = tests();

    if (results == false)
    {

        std::cout << "Test has Failed" << std::endl;
    }
    else
    {
        std::cout << "Test was a Success!" << std::endl;
    }

    std::cout << "\n";

    bool player = true;
    bool winnerOfGame = false;

    char connect4Board[SIZE_1][SIZE_2] = {{' ', ' ', ' ', ' ', ' ', ' ', ' '}, //  Diagonal in the middle of board (X is the answer)
                                          {' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                          {' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                          {' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                          {' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
                                          {' ', ' ', ' ', ' ', ' ', ' ', ' '}};


    printConnect4(connect4Board, player, winnerOfGame);
    // while (!winnerOfGame && hasEmptyProperties(connect4Board))
    // {
    //     printConnect4(connect4Board, player, winnerOfGame);
    // }
    
    return 0;
}