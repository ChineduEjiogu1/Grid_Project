// https://www.youtube.com/watch?v=TjOnDt_vBaY

#include <iostream>
#include <string>

#define NUM_OF_ROWS 6
#define NUM_OF_COLUMNS 7
#define WINNING_PATTERN 4

const std::string SIZEOFGRID = "2";
char disc = 'X';
int chooseColumn = 7;

std::string ColorBlue(char z)
{
    return "\e[01;34m" + std::string(1, z) + "\e[0m";
}

std::string ColorBlue(std::string z)
{
    return "\e[01;34m" + z + "\e[0m";
}

std::string ColorYellow(char q)
{
    return "\e[01;33m" + std::string(1, q) + "\e[0m";
}

std::string ColorRed(char w)
{
    return "\e[033;31m" + std::string(1, w) + "\e[0m";
}

std::string colorElement(char s)
{
    if (s == 'O')
        return ColorRed(s);
    if (s == 'X')
        return ColorYellow(s);
    else
        return ColorBlue(s);
}

bool checkEmptyBoard(char board[NUM_OF_ROWS][NUM_OF_COLUMNS])
{
    // My Row, X or I
    for (int x = 0; x < NUM_OF_ROWS; x++)
    {
        // My colunm, Y or J
        for (int y = 0; y < NUM_OF_COLUMNS; y++)
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

// 1. Visit every cell with nested for loop
// 2. Look at each character to see if their in consecutive rows
// 2a. Check to see if it's a uppercase "X" or "O"
// 2b. Compare the next index (Y + 1)
// 2c. If they are equal,compare the next neighboring index.
bool findWinnerHorizontial(char board[NUM_OF_ROWS][NUM_OF_COLUMNS], char player)
{
    unsigned int consecutiveCount = 0;
    for (int x = 0; x < NUM_OF_ROWS; x++)
    {
        consecutiveCount = 0;
        for (int y = 0; y < NUM_OF_COLUMNS; y++)
        {
            if (board[x][y] != player)
            {
                // std::cout << "No Match: " << player << " [" << board[x][y] << "]\n";
                consecutiveCount = 0;
            }
            else
            {
                consecutiveCount++;
                // std::cout << "Match: consecutiveCount " << consecutiveCount << " " <<  player << " [" << board[x][y] << "]\n";
            }

            if (consecutiveCount == 4)
            {
                std::cout << "The winner is horizontial: " << board[0][y] << "\n";
                return true;
            }
        }
    }

    return false;
}

bool findWinnerVertical(char board[NUM_OF_ROWS][NUM_OF_COLUMNS], char player)
{
    unsigned int consecutiveCount = 0;

    for (int y = 0; y < NUM_OF_COLUMNS; y++)
    {
        consecutiveCount = 0;
        for (int x = 0; x < NUM_OF_ROWS; x++)
        {
            if (board[x][y] != player)
            {
                // std::cout << "No Match: " << player << " [" << board[x][y] << "]\n";
                consecutiveCount = 0;
            }
            else
            {
                consecutiveCount++;
                // std::cout << "Match: consecutiveCount " << consecutiveCount << " " <<  player << " [" << board[x][y] << "]\n";
            }

            if (consecutiveCount == 4)
            {
                std::cout << "The winner is Vertical: " << board[x][y] << "\n";
                return true;
            }
        }
    }

    return false;
}

/*
    x,y  x,y  x,y
    [0,0][0,1][0,2][0,3][0,4][0,5][0,6]
    [1,0][1,1][1,2][1,3][1,4][1,5][1,6]
    [2,0][2,1][2,2][2,3][2,4][2,5][2,6]
    [3,0][3,1][3,2][3,3][3,4][3,5][3,6]
    [4,0][4,1][4,2][4,3][4,4][4,5][4,6]
    [5,0][5,1][5,2][5,3][5,4][5,5][5,6]
*/
bool checkDiagonal_1(char board[NUM_OF_ROWS][NUM_OF_COLUMNS], int row, int col)
{
    // there are 2 diagonals
    // x++ y++ to bottom left to right
    // x-- y-- to go from top left bottom right.
    // but verify somehow
    // also check your for loop constraints either the end condition or the start condition

    // first diagonal
    int count = 0;

    for (; row < NUM_OF_ROWS - 1 && col < NUM_OF_COLUMNS - 1; row++, col++)
    {
        if (board[row][col] != ' ' && board[row][col] == board[row + 1][col + 1])
        {
            count += 1;
            std::cout << "Found match, count " << count << std::endl;
            if (count == 3)
            {
                return true;
            }
        }
        else
        {
            count = 0;
        }
    }
    return false;
}

bool checkDiagonal_2(char board[NUM_OF_ROWS][NUM_OF_COLUMNS], int row, int col)
{
    int count2 = 0;

    for (; row > 0 && col < NUM_OF_COLUMNS - 1; row--, col++)
    {
        if (board[row][col] != ' ' && board[row][col] == board[row - 1][col + 1])
        {
            count2 += 1;
            std::cout << "Found match, count " << count2 << std::endl;
            if (count2 == 3)
            {
                return true;
            }
        }
        else
        {
            count2 = 0;
        }
    }

    return false;
}

bool isStartOfDiagonal1Valid(int row, int col)
{
    /*
     For Diag1 and connect 4:
         \
          \
           \
            \
             \

     FROM Top-Left --> to Bottom-Right
        Diag1 = [0,0],[1,1],[2,2],[3,3],[4,4],[5,5]
        Diag2 = [0,1],[1,2],[2,3],[3,4],[4,5],[5,6]
        Diag3 = [0,2],[1,3],[2,4],[3,5],[4,6]
        Diag4 = [0,3],[1,4],[2,5],[3,6]
                  |
                  +----Look at the starting value of the diagonal: row=0, 0 <= col <=3
        More over:
        Diag5 = [1,0],[2,1],[3,2],[4,3][5,4]
        Diag6 = [2,0], [3,1],[4,2],[5,3]
                  |
                  +----Look at the starting value of the diagonal: col=0,  0 < row < 3

      Diagonal shouls start form row=0, 0 <= col <=3
                             OR  col=0, 0 < row < 3
     */
    return (row == 0 && 0 <= col && col <= 3) ||
           (col == 0 && 0 < row && row < 3);

    // test this if we want to make a Connect x  game
    // return
    //       ( row == 0 &&  0 <= col && col <= COL - diagLength) ||
    //       ( col == 0 &&  0 <  row && row <= ROW - diagLength );
}

bool isStartOfDiagonal2Valid(int row, int col)
{
    /*
     For Diag2 and connect 4:
            /
           /
          /
         /
        /

       Diag1 = [5,0],[4,1],[3,2],[2,3][1,4],[0,5]
       Diag2 = [5,1],[4,2],[3,3],[2,4][1,5],[0,6]
       Diag3 = [5,2],[4,3],[3,4],[2,5][1,6]
       Diag4 = [5,3],[4,4],[3,5],[2,6]
                 |
                 +----Look at the starting value of the diagonal: row=5, 0 <= col <=3

       More over:
       Diag5 = [4,0],[3,1],[2,2],[1,3],[0,4]
       Diag6 = [3,0],[2,1],[1,2],[0,3]
                 |
                 +----Look at the starting value of the diagonal: col=0, 3 <= row <= 4

    */
    return (row == 5 && 0 <= col && col <= 3) ||
           (col == 0 && 3 <= row && row <= 4);

    // test this if we want to make a Connect x game
    //  return
    //       ( row == (ROW - 1) &&  0 <= col && col <= (COL - diagLength)  ) ||
    //       ( col == 0 &&  (diagLength-1) <= row  && row < ROW - diagLength + row );
}

bool findDiagonal(char board[NUM_OF_ROWS][NUM_OF_COLUMNS])
{
    for (int row = 0; row < NUM_OF_ROWS; row++)
    {
        for (int col = 0; col < NUM_OF_COLUMNS; col++)
        {

            if (isStartOfDiagonal1Valid(row, col))
            {
                if (checkDiagonal_1(board, row, col))
                {
                    return true;
                }
            }

            if (isStartOfDiagonal2Valid(row, col))
            {
                if (checkDiagonal_2(board, row, col))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

void printConnect4(char board[NUM_OF_ROWS][NUM_OF_COLUMNS], bool &player, const bool winner)
{
    char header[] = "  1   2   3   4   5   6   7  ";
    std::cout << header << "\n";
    std::cout << ColorBlue("+---+---+---+---+---+---+---+");
    std::cout << "\n";

    // Row
    for (int i = 0; i < NUM_OF_ROWS; i++)
    {
        std::cout << ColorBlue("|");
        // Column
        for (int j = 0; j < NUM_OF_COLUMNS; j++)
        {
            std::cout << " " << colorElement(board[i][j]) << " ";
            std::cout << ColorBlue("|");
        }
        // Printing newline of rows (0 - 2) or (1 - SIZE)
        std::cout << "\n";
        std::cout << ColorBlue("+---+---+---+---+---+---+---+");
        std::cout << "\n";
    }

    std::cout << "\n";

    if (winner == false)
    {
        std::cout << "It's player " << disc << " turn"
                  << "\n";
    }
}

bool winner(char board[NUM_OF_ROWS][NUM_OF_COLUMNS], char player)
{

    return (findWinnerHorizontial(board, player) || findWinnerVertical(board, player) || findDiagonal(board));
}

void fillInGameBoard(char board[NUM_OF_ROWS][NUM_OF_COLUMNS], int chosenColumn)
{
    // fills the bin according to what's already in there:
    /* lowest level or bottom of the board */
    int row = 0;
    for (row = NUM_OF_ROWS - 1; row >= 0; row--)
    {
        if (board[row][chosenColumn] == ' ')
        {
            // To-do
            board[row][chosenColumn] = disc;
            break;
        }
    }
}

bool chooseColumnPosition(char board[NUM_OF_ROWS][NUM_OF_COLUMNS], bool &player)
{
    // choose 1 2 3 4 5 6 7:
    char choose;

    while (1)
    {
        printf("\nPlease choose a column: ");
        scanf(" %c", &choose);
        std::cout << "\n";
        switch (choose)
        {
        case '1':
            chooseColumn = 0;
            break;
        case '2':
            chooseColumn = 1;
            break;
        case '3':
            chooseColumn = 2;
            break;
        case '4':
            chooseColumn = 3;
            break;
        case '5':
            chooseColumn = 4;
            break;
        case '6':
            chooseColumn = 5;
            break;
        case '7':
            chooseColumn = 6;
            break;
        default:
            chooseColumn = 666;
            printf("\nOut of bounds!, wrong column position, Try again.\n\n");
            printConnect4(board, player, winner);
        }
        // break out of while loop if the right letter was chosen:
        if ((chooseColumn >= 0 && chooseColumn <= 6) && (board[0][chooseColumn] == ' '))
        {
            fillInGameBoard(board, chooseColumn);

            bool winnerOfGame = winner(board, disc);

            if (!winnerOfGame)
            {
                disc = (disc == 'X') ? 'O' : 'X';
            }
            return winnerOfGame;
        }
    }

    return false;
}

bool hasEmptyProperties(char emptyBoard[NUM_OF_ROWS][NUM_OF_COLUMNS])
{

    for (int row = 0; row < NUM_OF_ROWS; row++)
    {
        for (int column = 0; column < NUM_OF_COLUMNS; column++)
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
    char emptyBoard[NUM_OF_ROWS][NUM_OF_COLUMNS];

    for (int row = 0; row < NUM_OF_ROWS; row++)
    {
        for (int column = 0; column < NUM_OF_COLUMNS; column++)
        {
            emptyBoard[row][column] = ' ';
        }
    }

    bool test1 = checkEmptyBoard(emptyBoard);

    char notAnEmptyBoard[NUM_OF_ROWS][NUM_OF_COLUMNS];

    bool test2 = !checkEmptyBoard(notAnEmptyBoard);

    char winningBoardHorizontial[NUM_OF_ROWS][NUM_OF_COLUMNS] = {{'X', 'X', 'O', 'O', 'O', 'O', 'X'}, // line 1 or 0 (row) of the board/grid (O is the answer)
                                                                 {'X', 'X', 'X', 'O', 'O', 'X', 'O'},
                                                                 {'O', 'X', 'X', 'X', 'O', 'O', 'O'},
                                                                 {'X', 'X', 'X', 'O', 'X', 'O', 'O'},
                                                                 {'X', 'O', 'X', 'O', 'O', 'X', 'O'},
                                                                 {'X', 'X', 'X', 'O', 'X', 'O', 'O'}};

    bool test3 = findWinnerHorizontial(winningBoardHorizontial, 'O');

    char winningBoardVertical[NUM_OF_ROWS][NUM_OF_COLUMNS] = {{'O', 'X', 'O', 'X', 'O', 'O', 'X'}, //  Column 3 of the board/grid (X is the answer)
                                                              {'X', 'O', 'X', 'X', 'O', 'X', 'O'},
                                                              {'O', 'X', 'O', 'X', 'O', 'O', 'O'},
                                                              {'X', 'X', 'X', 'X', 'X', 'O', 'X'},
                                                              {'X', 'O', 'O', 'O', 'X', 'X', 'O'},
                                                              {'X', 'X', 'X', 'O', 'X', 'O', 'O'}};

    bool test4 = findWinnerVertical(winningBoardVertical, 'X');

    char winningBoardDiagonal[NUM_OF_ROWS][NUM_OF_COLUMNS] = {{'O', 'X', 'O', 'O', 'O', 'X', 'X'}, //  Diagonal in the middle of board (O is the answer)
                                                              {'X', 'O', 'X', 'O', 'O', 'X', 'O'},
                                                              {'O', 'X', 'O', 'X', 'X', 'O', 'O'},
                                                              {'X', 'X', 'O', 'O', 'O', 'O', 'X'},
                                                              {'X', 'O', 'O', 'X', 'X', 'X', 'O'},
                                                              {'X', 'X', 'X', 'O', 'X', 'O', 'O'}};

    bool test5 = findDiagonal(winningBoardDiagonal);

    char winningBoardDiagonal2[NUM_OF_ROWS][NUM_OF_COLUMNS] = {{'O', 'X', 'O', 'O', 'O', 'X', 'X'}, //  Diagonal in the middle of board (X is the answer)
                                                               {'X', 'X', 'O', 'O', 'O', 'X', 'O'},
                                                               {'O', 'O', 'X', 'X', 'X', 'O', 'O'},
                                                               {'X', 'O', 'O', 'X', 'X', 'X', 'X'},
                                                               {'X', 'O', 'O', 'O', 'O', 'X', 'O'},
                                                               {'X', 'X', 'X', 'O', 'X', 'O', 'O'}};

    bool test6 = findDiagonal(winningBoardDiagonal2);

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

    std::cout << "\n";

    bool player = true;
    bool winnerOfGame = false;

    char connect4Board[NUM_OF_ROWS][NUM_OF_COLUMNS] = {{' ', ' ', ' ', ' ', ' ', ' ', ' '}, //  Diagonal in the middle of board (X is the answer)
                                                       {' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                                       {' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                                       {' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                                       {' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                                       {' ', ' ', ' ', ' ', ' ', ' ', ' '}};

    while (!winnerOfGame && hasEmptyProperties(connect4Board))
    {
        printConnect4(connect4Board, player, winnerOfGame);
        winnerOfGame = chooseColumnPosition(connect4Board, player);
        // fillInGameBoard(connect4Board, player);
    }

    if (winner(connect4Board, disc))
    {
        std::cout << "The winner is: " << disc << "\n\n";
        printConnect4(connect4Board, player, winnerOfGame);
    }
    else
    {
        std::cout << "\n";
        std::cout << "The game is a draw, please play again\n";

        printConnect4(connect4Board, player, winnerOfGame);
    }

    return 0;
}