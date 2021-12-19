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

void userInputBoard(char board[3][3], bool &player)
{
    int row = 0, column = 0;

    std::cout << "\n";
    std::cout << "Please enter your desired row and column [" << row << "] [SPACE] [" << column << "]: \n";
    std::cin >> row; std::cin >> column;
    std::cout << "\n";

    // https://stackoverflow.com/questions/18728754/checking-cin-input-stream-produces-an-integer
    while(std::cin.fail())
    {
        std::cout << "Invalid input (Integer not found): Enter your desired row and column this way please [" << row << "] [SPACE] [" << column << "]: \n";
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cin >> row ; std::cin >> column;
    }

    // Checking for bounds, array bounds
    if (row <= 2 && column <= 2 && row >= 0 && column >= 0) 
    {
        if (board[row][column] == '.') // it's a period
        {
            // if it equals true is player1 turn
            if (player) 
            {
                // Mark the cell with an 'X'
                board[row][column] = 'X';
                // true is first player 
                player = false;
                // false is second player
            }
            else
            {
                // Mark the cell with a 'O'
                board[row][column] = 'O'; 
                player = true;
            }
        }
        // Paired with line 37 if statement block, for checking if the cell is (not) a period
        else 
        {
            while (board[row][column] == 'X' || board[row][column] == 'O')
            {
               // implemention - If your previous input is the same as the next input.
                if(board[row][column] == 'X' || board[row][column] == 'O')
                {
                    std::cout << "You entered the same row and column again [" << row << "] [SPACE] [" << column << "]:\nPlease enter again: \n";
                    std::cin.clear();
                    std::cin.ignore(256,'\n');
                    std::cin >> row ; std::cin >> column;
                }

            }

            if (player)
            {
               // Mark the cell with an 'X' 
                board[row][column] = 'X'; 
                // true is first player 
                player = false;
            }
            else
            {
                // Mark the cell with a 'O'
                board[row][column] = 'O'; 
                // false is second player
                player = true;
            }
        }
    }

    else
    {
        std::cout << "Invalid input: rows must be 0 - 2, and columns must be  0 - 2 \n";
        std::cout << "\n";
    }
 
    // Row
    for (int i = 0; i < 3; i++) 
    {
        // Column
        for (int j = 0; j < 3; j++) 
        {
            std::cout << board[i][j];
        }
        // Printing newline of rows (0 - 2) or (1 - 3)
        std::cout << "\n";
    }

    std::cout << "\n";
}
/*
    x,y  x,y  x,y
    [0,0][0,1][0,2]
    [1,0][1,1][1,2]
    [2,0][2,1][2,2]
*/

/*
    There are 8 ways of winning Tic-tac-Toe
    3 horizontial ways of winning
    3 vertical ways of winning 
    2 diagonal ways of winning
    (3 + 3) = 6 -> (6 + 2) = 8
    9 - 8 = 1 -> you get one chance at winning
*/

/*
    First diagonal - Has the same numbers or the two indexs for both (x,y) in that cell.
    Second diagonal - The two indexs are the inverse of each or they add to the number '2'
    Horizontial - All in the same row - the y changes, the x stays the same, i.e. y + 1,.
    Vertical - All in the same column the x changes, the y stays the same i.e x + 1.
*/

bool findWinnerHorizontial(char board[3][3])
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
                //std::cout << "The winner is horizontial: " << board[x][0] << "\n";
                return true;
            }
        }
    }

    return false;
}

bool findWinnerVertical(char board[3][3])
{

    for (int y = 0; y < 3; y++)
    {
        if (board[0][y] == 'X' || board[0][y] == 'O')
        {
            if (board[0][y] == board[1][y] && board[0][y] == board[2][y])
            {
                // std::cout << "The winner is vertical: " << board[0][y] << "\n";
                return true;
            }
        }
    }

    return false;
}

bool findWinnerDiagonial(char board[3][3])
{
           
    // First Diagonal
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && (board[0][0] == 'X' || board[0][0] == 'O'))
    {
        // std::cout << "The winner is diagonal: " << board[1][1] << std::endl;
        return true;
    }
        
    // Second Diagonal

    // x,y  x,y  x,y
    // [0,0][0,1][0,2]
    // [1,0][1,1][1,2]
    // [2,0][2,1][2,2]

        // if(board[2][0] == board[1][1] && board[2][0] == board[0][2]) - Alternative way of checking for second diagonal
        // ((x + y) == 2) - diagonal condition advanced way, but not working.
        // x++;*
        // y++;
                    
    if (board[2][0] == board[1][1] && board[2][0] == board[0][2] && (board[2][0] == 'X' || board[2][0] == 'O')) 
    {
        // std::cout << "The winner is: " << board[1][1] << "\n";
        // std::cout << "The winner is diagonal 2: " << board[1][1] << std::endl;
        return true;
    }

    return false;    
}

bool winner(char board[3][3])
{
    return (findWinnerHorizontial(board) || findWinnerVertical(board) || findWinnerDiagonial(board)); 
}

bool hasEmptyProperties(char emptyBoard[3][3]){

    for (int row = 0; row < 3; row++)
    {
        for (int column = 0; column < 3; column++)
        {
            if(emptyBoard[row][column] == '.'){
                return true;
            } 
        }
    }

    std::cout << "Failed to find empty space on game board\n";
    return false;
}

// Testing functions for successes and/or failures. AKA Test cases
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

    // Populated with periods so we considerate it empty.
    char notAnEmptyBoard[3][3]; 

    // Put !(not) because it expects to check the non-empty board to come back false.
    bool test2 = !checkEmptyBoard(notAnEmptyBoard);

    // Horizontially winning Tic-Tac-Toe.
    char winningBoardHorizontial[3][3] = {{'O', 'X', 'O'},
                                          {'X', 'X', 'X'},
                                          {'X', 'O', 'O'}}; 
    // Vertically winning Tic-Tac-Toe
    char winningBoardVertical[3][3] =
        {
            {'O', 'X', 'O'},
            {'X', 'O', 'O'},
            {'X', 'O', 'O'}}; 

    // Diagonially winning Tic-Tac-Toe in two directions (looking up or looking down) - **looking down** (Top left to bottom right)
    char winningBoardDiagonial[3][3] =
        {
            {'O', 'X', 'X'},
            {'X', 'O', 'O'},
            {'X', 'O', 'O'}};
               
    // Diagonially winning Tic-Tac-Toe in two directions (looking up or looking down) - **looking up** (Bottom left to top right)  
    char winningBoardDiagonial2[3][3] =
        {
            {'O', 'X', 'X'},
            {'X', 'X', 'O'},
            {'X', 'O', 'O'}}; 

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

        std::cout << "Test has Failed" << std::endl;
    }
    else
    {
        std::cout << "Test was a Success!" << std::endl;
    }

    bool player = true;

    char testInputOfBoard[3][3] = {{'.', '.', '.'}, 
                                   {'.', '.', '.'}, 
                                   {'.', '.', '.'}};
    
    char players[2] = {'O', 'X'};

    while(!winner(testInputOfBoard) && hasEmptyProperties(testInputOfBoard))
    {
        userInputBoard(testInputOfBoard, player);
    }

    if(winner(testInputOfBoard))
    {
        std::cout << "The winner is: " << players[(player^true)] << "\n";
    }

    else
    {
        std::cout << "\n";
        std::cout << "The game is a draw, please play again\n";
    }
    
    return 0;
}