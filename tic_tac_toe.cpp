#include <iostream>

// A function for an empty board that will contain period characters and will be checked or
// be guaranteed that it is infact a period.
bool checkEmptyBoard(char board[3][3])
{
    for (int x = 0; x < 3; x++) // My Row, X or I
    {
        for (int y = 0; y < 3; y++) // My colunm, Y or J
        {
            if (board[x][y] == '.')
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

void userInputBoard(char board[3][3])
{
    int row = 0, column = 0;
    bool player = true;

    std::cout << "\n";
    std::cout << "Please enter your desired row and column [" << row << "][" << column << "]: \n";
    
    std::cin >> row; std::cin >> column;

    if (row <= 2 && column <= 2 && row >= 0 && column >= 0) // Checking for bounds, array bounds
    {
        if (board[row][column] == '.') // it's a period
        {
            if (player) // if it equals true is player1 turn
            {
                board[row][column] = 'X'; // Mark the cell with an 'X'
            }
            else
            {
                board[row][column] = 'O'; // Mark the cell with a 'O'
            }
        }
        else // Paired with line 37 if statement block, for checking if the cell is (not) a period
        {
            while (board[row][column] == 'X' || board[row][column] == 'O')
            {
                std::cout << "Please enter your desired row and column [" << row << "][" << column << "]: \n";
                std::cin >> row ; std::cin >> column;
            }

            if (player)
            {
                board[row][column] = 'X'; // Mark the cell with an 'X'
            }
            else
            {
                board[row][column] = 'O'; // Mark the cell with a 'O'
            }
        }
    }
    else
    {
        std::cout << "Invalid input: rows must be 0 - 2, and columns must be  0 - 2 \n";
    }

    for (int i = 0; i < 3; i++) // Row
    {

        for (int j = 0; j < 3; j++) // Column
        {
            std::cout << board[i][j];
        }

        std::cout << "\n";
    }
}
/*
 x,y  x,y  x,y
[0,0][0,1][0,2]
[1,0][1,1][1,2]
[2,0][2,1][2,2]

First diagonal - Has the same numbers or the two indexs for both (x,y) in that cell.
Second diagonal - The two indexs are the inverse of each or they add to the number '2'
Horizontial - All in the same row - the y changes, the x stays the same, i.e. y + 1,.
Vertical - All in the same column the x changes, the y stays the same i.e x + 1.
*/

char findWinnerHorizontial(char board[3][3])
{
    // 1. Visit every cell with nested for loop
    // 2. Look at each character to see if their in consecutive rows
    // 2a. Check to see if it's a uppercase "X" or "O"
    // 2b. Compare the next index (Y + 1)
    // 2c. If they are equal,compare the next neighboring index.

    for (int x = 0; x < 3; x++)
    {
        if (board[x][0] == 'X' || board[x][0] == 'O')
        {
            if (board[x][0] == board[x][1] && board[x][0] == board[x][2])
            {
                std::cout << "The winner is: " << board[x][0] << std::endl;
                return board[x][0];
            }
        }
    }

    return board[3][3];
}

char findWinnerVertical(char board[3][3])
{

    for (int y = 0; y < 3; y++)
    {
        if (board[0][y] == 'X' || board[0][y] == 'O')
        {
            if (board[0][y] == board[1][y] && board[0][y] == board[2][y])
            {
                std::cout << "The winner is: " << board[0][y] << std::endl;
                return board[0][y];
            }
        }
    }

    return board[3][3];
}

char findWinnerDiagonial(char board[3][3])
{
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            if (board[x][y] == 'X' || board[x][y] == 'O')
            {
                // First Diagonal
                if (x == y)
                {
                    x++;
                    y++;

                    std::cout << "The winner is: " << board[x][y] << std::endl;
                    return board[x][y];
                }
                else
                {   
                    // Second Diagonal

                    // if(board[2][0] == 2 && board[1][1] == 2 && board[0][2] == 2) - Alternative way of checking for second diagonal
                    if ((x + y) == 2) 
                    {
                        std::cout << "The winner is: " << board[x][y] << std::endl;
                        return board[x][y];
                    }
                }
            }
        }
    }

    return board[3][3];
}

// Testing functions for successes and failures.
bool tests()
{
    char emptyBoard[3][3];

    for (int row = 0; row < 3; row++)
    {
        for (int column = 0; column < 3; column++)
        {
            emptyBoard[row][column] = '.';
        }
    }

    bool test1 = checkEmptyBoard(emptyBoard);

    char notAnEmptyBoard[3][3]; // Populated with spaces so we considerate it empty.

    // Put !(not) because it expects to check the non-empty board to come back false.
    bool test2 = !checkEmptyBoard(notAnEmptyBoard);

    char winningBoardHorizontial[3][3] = {{'O', 'X', 'O'},
                                          {'X', 'X', 'X'},
                                          {'X', 'O', 'O'}}; // Horizontially winning Tic-Tac-Toe.

    char winningBoardVertical[3][3] =
        {
            {'O', 'X', 'O'},
            {'X', 'O', 'O'},
            {'X', 'O', 'O'}}; // Vertically winning Tic-Tac-Toe

    char winningBoardDiagonial[3][3] =
        {
            {'O', 'X', 'X'},
            {'X', 'O', 'O'},
            {'X', 'O', 'O'}}; // Diagonially winning Tic-Tac-Toe in two directions (looking up or looking down) - **looking down** (Top left to bottom right)

    char winningBoardDiagonial2[3][3] =
        {
            {'O', 'X', 'X'},
            {'X', 'X', 'O'},
            {'X', 'O', 'O'}}; // Diagonially winning Tic-Tac-Toe in two directions (looking up or looking down) - **looking up** (Bottom left to top right)

    bool test3 = findWinnerHorizontial(winningBoardHorizontial);

    bool test4 = findWinnerVertical(winningBoardVertical);

    bool test5 = findWinnerDiagonial(winningBoardDiagonial);

    bool test6 = findWinnerDiagonial(winningBoardDiagonial2);

    // pseduo-code
    // return true (test1 && test2) == true;

    return (test1 && test2 && test3 && test4 && test5 && test6);
}
int main()
{
    bool results = tests();

    if (results == false)
    {

        std::cout << "Test Failed" << std::endl;
    }
    else
    {
        std::cout << "Test was a Success" << std::endl;
    }

    char testInputOfBoard[3][3] = {{'.', '.', '.'}, 
                                   {'.', '.', '.'}, 
                                   {'.', '.', '.'}};

    userInputBoard(testInputOfBoard);

    return 0;
}