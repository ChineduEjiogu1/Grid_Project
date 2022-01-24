// https://www.techiedelight.com/use-std-pair-key-std-map-cpp/

#include <iostream>
#include <tuple> // std::tuple, std::get, std::tie, std::ignore
#include <vector>

#include "colorcode.h"
#define WINNING_PATTERN 4
// this holds the pair (row, col) or rows and columns.
// typedef std::pair<int, int> diagonals;

typedef std::tuple<std::string, int, int> diagonal; // 'rising|falling',row,column

/*
     x,y  x,y  x,y
    [0,0][0,1][0,2][0,3][0,4][0,5][0,6]
    [1,0][1,1][1,2][1,3][1,4][1,5][1,6]
    [2,0][2,1][2,2][2,3][2,4][2,5][2,6]
    [3,0][3,1][3,2][3,3][3,4][3,5][3,6]
    [4,0][4,1][4,2][4,3][4,4][4,5][4,6]
    [5,0][5,1][5,2][5,3][5,4][5,5][5,6]

*/

class connect4
{
private:
public:
    char players = 'X';
    bool winnerOfGame = false;
    const static int NUM_OF_ROWS = 6;
    const static int NUM_OF_COLUMNS = 7;
    std::vector<diagonal> diagonals; // main structure that holds all of the starting points for the diagonals

    char board[NUM_OF_ROWS][NUM_OF_COLUMNS];
    int chosenColumn = 0;
    connect4();
    void printConnect4();
    bool hasEmptyProperties();
    bool chooseColumnPosition();
    void fillInGameBoard();
    bool findWinnerHorizontial();
    bool findWinnerVertical();
    bool isStartOfDiagonal1Valid(int, int);
    bool isStartOfDiagonal2Valid(int, int);
    bool checkFallingDiagonal(int row, int col);
    bool checkRisingDiagonal(int row, int col);
    bool findWinnerDiagonal();
    bool winner();
    void setup();
    void start();
};
// Intializing the board
connect4::connect4()
{
    setup();
}

void connect4::setup()
{
    for (int row = 0; row < NUM_OF_ROWS; row++)
    {
        for (int column = 0; column < NUM_OF_COLUMNS; column++)
        {
            board[row][column] = ' ';
        }
    }

    bool falling, rising = false;
    // populate the vector with starting point of diagonals
    for (int row = 0; row < NUM_OF_ROWS; row++)
    {
        for (int col = 0; col < NUM_OF_COLUMNS; col++)
        {
            falling = (row == 0 && 0 <= col && col <= 3) || // starting from top-left: falling --> row++ and col++
                      (col == 0 && 0 < row && row < 3);

            rising = (row == 5 && 0 <= col && col <= 3) || // starting from bottom-left:  rising --> row--,col++
                     (col == 0 && 3 <= row && row <= 4);

            if (falling)
            {
                diagonals.push_back(std::make_tuple("falling", row, col));
            }

            if (rising)
            {
                diagonals.push_back(std::make_tuple("rising", row, col));
            }
        }
    }

    winnerOfGame = false; // reset back to default value
}

void connect4::printConnect4()
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

    if (winnerOfGame == false)
    {
        std::cout << "It's player " << players << " turn"
                  << "\n";
    }
}

void connect4::fillInGameBoard()
{
    // fills the bin according to what's already in there:
    /* lowest level or bottom of the board */
    int row = 0;
    for (row = NUM_OF_ROWS - 1; row >= 0; row--)
    {
        if (board[row][chosenColumn] == ' ')
        {
            // To-do
            board[row][chosenColumn] = players;
            break;
        }
    }
}

bool connect4::chooseColumnPosition()
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
            chosenColumn = 0;
            break;
        case '2':
            chosenColumn = 1;
            break;
        case '3':
            chosenColumn = 2;
            break;
        case '4':
            chosenColumn = 3;
            break;
        case '5':
            chosenColumn = 4;
            break;
        case '6':
            chosenColumn = 5;
            break;
        case '7':
            chosenColumn = 6;
            break;
        default:
            chosenColumn = 666;
            printf("\nOut of bounds!, wrong column position, Try again.\n\n");
            printConnect4();
        }
        // break out of while loop if the right letter was chosen:
        if ((chosenColumn >= 0 && chosenColumn <= 6) && (board[0][chosenColumn] == ' '))
        {
            fillInGameBoard();

            bool winnerOfGame = winner();

            std::cout << winnerOfGame << "\n";

            if (!winnerOfGame)
            {
                players = (players == 'X') ? 'O' : 'X';
            }
            return winnerOfGame;
        }
    }

    return false;
}

bool connect4::hasEmptyProperties()
{

    for (int row = 0; row < NUM_OF_ROWS; row++)
    {
        for (int column = 0; column < NUM_OF_COLUMNS; column++)
        {
            if (board[row][column] == ' ')
            {
                return true;
            }
        }
    }

    std::cout << "\n";
    std::cout << "Failed to find empty space on the game board\n";
    return false;
}

bool connect4::findWinnerVertical()
{
    unsigned int consecutiveCount = 0;

    for (int y = 0; y < NUM_OF_COLUMNS; y++)
    {
        consecutiveCount = 0;

        for (int x = 0; x < NUM_OF_ROWS; x++)
        {
            if (board[x][y] != players)
            {
                // std::cout << "No Match: " << player << " [" << board[x][y] << "]\n";
                consecutiveCount = 0;
            }
            else
            {
                consecutiveCount++;
                // std::cout << "Match: consecutiveCount " << consecutiveCount << " " <<  player << " [" << board[x][y] << "]\n";
            }

            if (consecutiveCount == WINNING_PATTERN)
            {
                std::cout << "The winner is Vertical: " << board[x][y] << "\n";
                return true;
            }
        }
    }

    return false;
}

bool connect4::findWinnerHorizontial()
{
    unsigned int consecutiveCount = 0;

    for (int x = 0; x < NUM_OF_ROWS; x++)
    {
        consecutiveCount = 0;
        for (int y = 0; y < NUM_OF_COLUMNS; y++)
        {
            if (board[x][y] != players)
            {
                // std::cout << "No Match: " << player << " [" << board[x][y] << "]\n";
                consecutiveCount = 0;
            }
            else
            {
                consecutiveCount++;
                // std::cout << "Match: consecutiveCount " << consecutiveCount << " " <<  player << " [" << board[x][y] << "]\n";
            }

            if (consecutiveCount == WINNING_PATTERN)
            {
                // std::cout << "The winner is horizontial: " << board[0][y] << "\n";
                return true;
            }
        }
    }

    return false;
}

bool connect4::isStartOfDiagonal1Valid(int row, int col)
{
    return (row == 0 && 0 <= col && col <= 3) ||
           (col == 0 && 0 < row && row < 3);
}

bool connect4::isStartOfDiagonal2Valid(int row, int col)
{
    return (row == 5 && 0 <= col && col <= 3) ||
           (col == 0 && 3 <= row && row <= 4);
}

bool connect4::checkFallingDiagonal(int row, int col)
{
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

bool connect4::checkRisingDiagonal(int row, int col)
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

bool connect4::findWinnerDiagonal()
{

    std::string direction;
    int row = -1;
    int col = -1;

    for (auto diagonal : diagonals)
    {
        direction = std::get<0>(diagonal);
        row = std::get<1>(diagonal);
        col = std::get<2>(diagonal);

        if (direction == "falling" && checkFallingDiagonal(row, col))
        {
            return true;
        }

        if (direction == "rising" && checkRisingDiagonal(row, col))
        {
            return true;
        }
    }

    return false;
}

bool connect4::winner()
{
    return (findWinnerHorizontial() || findWinnerVertical() || findWinnerDiagonal());
}

void connect4::start()
{
    while (!winnerOfGame && hasEmptyProperties())
    {
        printConnect4();
        winnerOfGame = chooseColumnPosition();
    }

    printConnect4();
    if (winnerOfGame)
    {
        std::cout << "The winner is: " << players << "\n";
    }
    else
    {
        std::cout << "No winner was found. \n";
    }

    std::string answer;

    do
    {
        std::cout << "would you like to play again? Y/N :";
        std::getline(std::cin, answer);
        answer = std::tolower(answer[0]);
    } while (answer != "y" && answer != "n");

    if (answer == "y")
    {
        std::cout << "Starting a new game." << std::endl;

        setup();
        start();
    }

    std::cout << "Done." << std::endl;
}