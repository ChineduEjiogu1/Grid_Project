// https://www.youtube.com/watch?v=TjOnDt_vBaY

#include <iostream>

#define NUM_OF_ROWS 6
#define NUM_OF_COLUMNS 7
#define WINNING_PATTERN 4

const std::string SIZEOFGRID = "2";
// const char players[2] = {'O', 'X'};
char disc = 'X';
int chooseColumnSize = 7;

std::string ColorBlue(char z)
{
    return "\e[01;34m" + std::string(1, z) + "\e[0m";
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
        return ColorBlue(s);
    else
        return ColorYellow(s);
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
                consecutiveCount ++;
                // std::cout << "Match: consecutiveCount " << consecutiveCount << " " <<  player << " [" << board[x][y] << "]\n";
            }

            if(consecutiveCount == 4)
            {
                // std::cout << "The winner is horizontial: " << board[0][y] << "\n";
                std::cout << "The winner is horizontial: " << board[x][y] << "\n";
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
                consecutiveCount ++;
                // std::cout << "Match: consecutiveCount " << consecutiveCount << " " <<  player << " [" << board[x][y] << "]\n";
            }

            if(consecutiveCount == 4)
            {
                // std::cout << "The winner is horizontial: " << board[0][y] << "\n";
                std::cout << "The winner is Vertical: " << board[x][y] << "\n";
                return true;
            }               
        }
    }
    
    return false;
}

bool findWinnerDiagonial(char board[NUM_OF_ROWS][NUM_OF_COLUMNS], char player)
{
    //there are 2 diagonals
    //x++ y++ to bottom left to right
    //x-- y-- to go from top left bottom right.
    //but verify somehow
    //also check your for loop constraints either the end condition or the start condition

    for (int x = 0; x < NUM_OF_ROWS; x++)
    {
        // unsigned int consecutiveCount = 0;
    
        for (int y = 0; y < NUM_OF_COLUMNS; y++)
        {
            // consecutiveCount = 0;

            if (board[x][y] == 'X' || board[x][y] == 'O')
            {
                if ((x == y))
                {
                    x--;
                    y++;
                    //consecutiveCount++;
                    // std::cout << "The winner is diagonal: " << board[3][3] << "\n";
                    // std::cout << "Match: consecutiveCount " << consecutiveCount << " " <<  player << " [" << board[x][y] << "]\n";
                    std::cout << "The winner is diagonal: " << board[x][y] << "\n";
                    return true;
                }
                
                //int total = 0;
                if ( ((x + y) % 2) == 0)
                {
                    x++;
                    y++;
                    //consecutiveCount--;
                    // std::cout << "The winner is diagonal: " << board[3][3] << "\n";
                    // std::cout << "Match: consecutiveCount " << consecutiveCount << " " <<  player << " [" << board[x][y] << "]\n";
                    std::cout << "The winner is diagonal: " << board[x][y] << "\n";
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
    std::cout << "+---+---+---+---+---+---+---+";
    std::cout << "\n";

    // Row
    for (int i = 0; i < NUM_OF_ROWS; i++)
    {
        std::cout << "|";
        // Column
        for (int j = 0; j < NUM_OF_COLUMNS; j++)
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
        std::cout << "It's player " << disc << " turn" << "\n";
    }
}

bool winner(char board[NUM_OF_ROWS][NUM_OF_COLUMNS], char player)
{
    return (findWinnerHorizontial(board, player) || findWinnerVertical(board, player)) || findWinnerDiagonial(board, player);
}

void fillInGameBoard(char board[NUM_OF_ROWS][NUM_OF_COLUMNS], int chosenColumn)
{
    // fills the bin according to what's already in there:
    /* lowest level or bottom of the board */
    int row = 0;     
    for (row = NUM_OF_ROWS-1; row >= 0; row--)
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
        switch(choose)
        {
            case '1':
                chooseColumnSize = 0;
                break;
            case '2':
                chooseColumnSize = 1;
                break;
            case '3':
                chooseColumnSize = 2;
                break;
            case '4':
                chooseColumnSize = 3;
                break;
            case '5':
                chooseColumnSize = 4;
                break;
            case '6':
                chooseColumnSize = 5;
                break;
            case '7':
                chooseColumnSize = 6;
                break;
            default:
                chooseColumnSize = 666;
                printf("\nOut of bounds!, wrong column position, Try again.\n\n");
                printConnect4(board, player, winner);
        }
        // break out of while loop if the right letter was chosen:
        if ((chooseColumnSize >= 0 && chooseColumnSize <= 6) && (board[0][chooseColumnSize] == ' '))
        {
            fillInGameBoard(board, chooseColumnSize);

            bool winnerOfGame = winner(board, disc);

            if(!winnerOfGame)
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
        for (int column = 0; column < NUM_OF_ROWS; column++)
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

    char winningBoardVertical[NUM_OF_ROWS][NUM_OF_COLUMNS] = {{'X', 'X', 'O', 'O', 'O', 'O', 'X'}, //  Column 2 of the board/grid (X is the answer)
                                                              {'X', 'X', 'X', 'O', 'O', 'X', 'O'},
                                                              {'O', 'X', 'X', 'X', 'O', 'O', 'O'},
                                                              {'X', 'X', 'X', 'O', 'X', 'O', 'X'},
                                                              {'X', 'O', 'O', 'O', 'O', 'X', 'O'}, 
                                                              {'X', 'X', 'X', 'O', 'X', 'O', 'O'}};

    bool test4 = findWinnerVertical(winningBoardVertical, 'X');

    char winningBoardDiagonal[NUM_OF_ROWS][NUM_OF_COLUMNS] = {{'X', 'X', 'O', 'O', 'O', 'O', 'X'}, //  Diagonal in the middle of board (O is the answer)
                                                              {'X', 'X', 'X', 'O', 'O', 'X', 'O'},
                                                              {'O', 'X', 'X', 'X', 'O', 'O', 'O'},
                                                              {'X', 'X', 'X', 'O', 'X', 'O', 'X'},
                                                              {'X', 'O', 'O', 'O', 'O', 'X', 'O'}, 
                                                              {'X', 'X', 'X', 'O', 'X', 'O', 'O'}};

    bool test5 = findWinnerDiagonial(winningBoardDiagonal, 'O');

    char winningBoardDiagonal2[NUM_OF_ROWS][NUM_OF_COLUMNS] = {{'X', 'X', 'O', 'O', 'O', 'O', 'X'}, //  Diagonal in the middle of board (X is the answer)
                                                               {'X', 'X', 'X', 'O', 'O', 'X', 'O'},
                                                               {'O', 'X', 'X', 'X', 'O', 'O', 'O'},
                                                               {'X', 'O', 'O', 'X', 'X', 'X', 'X'},
                                                               {'X', 'O', 'O', 'O', 'O', 'X', 'O'}, 
                                                               {'X', 'X', 'X', 'O', 'X', 'O', 'O'}};

    //bool test6 = findWinnerDiagonial(winningBoardDiagonal2);


    return (test1 && test2 && test3 && test4 && test5);// && test4 && test5 && test6);
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
        std::cout << "The winner is: " << disc << "\n";
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