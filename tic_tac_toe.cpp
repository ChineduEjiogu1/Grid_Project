#include <iostream>

// Function for empty board that will contain space characters and be checked or 
// guarantee that it is in fact empty
bool checkEmptyBoard(char board[3][3])
{
    for(int x = 0; x < 3; x++) // My Row, X or I
    {
        for(int y = 0; y < 3; y++) // My colunm, Y or J
        {
            if( board[x][y] == char(32) ) 
            {
                continue;

            }else{

                return false;
            }
            
        }
    }

    return true;
}

/* 
 x, y x, y x, y
[0,0][0,1][0,2]
[1,0][1,1][1,2]
[2,0][2,1][2,2]

First diagonal - Has the same numbers or the two indexs for both (x,y) in that cell.
Second diagonal - The two indexs are the inverse of each or they add to the number '2'
Horizontial - All in the same row.
Vertical - All in the same column.
*/

char findWinnerDiagonial(char board[3][3])
{
    for(int x = 0; x < 3; x++)
    {
        for(int y = 0; y < 3; y++)
        {
            if(board[x][y] == 'X' || board[x][y] == 'O')
            {
                if(board[x] == board[y])
                {
                    std::cout << "The winner is: " << board[x][y] << std::endl;
                    return board[x][y];

                }else
                {
                    if(board[x][y] == 'X' || board[x][y] == 'O')
                    {
                        if(board[x][y] == 2)
                        {
                            std::cout << "The winner is: " << board[x][y] << std::endl;
                            return board[x][y];
                        }
                    }
                }
            }
        }
    }

    return board[3][3]; 
}

char findWinnerHorizontial(char board[3][3])
{
    // 1. Visit every cell with nested for loop
    // 2. Look at each character to see if their in consecutive rows
        // 2a. Check to see if it's a uppercase "X" or "O"
        // 2b. Compare the next index (Y + 1)
        // 2c. If they are equal,compare the next neighboring index.
        
    for(int x = 0; x < 3; x++)
    { 
            if(board[x][0] == 'X' || board[x][0] == 'O')
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

// Testing are functions for successes or failures.
bool tests()
{
    char emptyBoard[3][3];

    for(int row = 0; row < 3; row++)
    {
        for(int column = 0; column < 3; column++)
        {
            emptyBoard[row][column] = char(32);
        }
    }

    bool test1 = checkEmptyBoard(emptyBoard);   

    char notAnEmptyBoard[3][3]; // Populated with spaces so we considerate it empty.

    // Put !(not) because it expects to check the non-empty board to come back false.
    bool test2 = !checkEmptyBoard(notAnEmptyBoard);

    char winningBoardHorizontial[3][3] = {'X','X','X'}; // Horizontially winning Tic-Tac-Toe.

    char winningBoardDiagonial[3][3] = 
    {
        {'O','X','X'}, 
        {'X','O','O'}, 
        {'X','O','O'}
    };

    bool test3 = findWinnerHorizontial(winningBoardHorizontial);

    bool test4 = findWinnerDiagonial(winningBoardDiagonial);


    // pseduo-code
    // return true (test1 && test2) == true;

    return (test1 && test2 && test3 && test4);

}

int main()
{
    bool results = tests();

    if(results == false)
    {

        std::cout << "Test Failed" << std::endl;

    }else{

        std::cout << "Test was a Success" << std::endl;
    }

    return 0;
}