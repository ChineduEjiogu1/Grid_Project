// https://www.techiedelight.com/use-std-pair-key-std-map-cpp/

#include <iostream>
#include <map>
#include "colorcode.h"
#define WINNING_PATTERN 4
// this holds the pair (row, col) or rows and columns. 
typedef std::pair<int, int> diagonals; 

class connect4
{
    private:
        
    public:
        char players = 'X';
        bool winnerOfGame = false;
        const static int NUM_OF_ROWS = 6;
        const static int NUM_OF_COLUMNS = 7;
        // Multiple pair as starting point
        // int here is the counter 
        // and starting point of diagonals
        std::map<int, diagonals> indexOfDiagonals; 
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
        bool checkDiagonal_1(int row, int col);
        bool checkDiagonal_2(int row, int col);
        bool diagonal();
        bool winner();

};
    // Intializing the board
    connect4::connect4()
    {
        for (int row = 0; row < NUM_OF_ROWS; row++)
        {
            for (int column = 0; column < NUM_OF_COLUMNS; column++)
            {
                board[row][column] = ' ';
            }
        }

        // intializing the indexing of diagonals in the board
        int counter = 0;
        for (int row = 0; row < NUM_OF_ROWS; row++)
        {
            for (int col = 0; col < NUM_OF_COLUMNS; col++)
            {
                if (isStartOfDiagonal1Valid(row, col))
                {
                  indexOfDiagonals[counter++] = std::make_pair(row, col);
                }

                if (isStartOfDiagonal2Valid(row, col))
                {
                    indexOfDiagonals[counter++] = std::make_pair(row, col);
                }
            }
        }
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

    bool connect4::checkDiagonal_1(int row, int col)
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

    bool connect4::checkDiagonal_2( int row, int col)
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

    bool connect4::diagonal()
    {
        for (auto& [key, value]: indexOfDiagonals) 
        {
            std::cout << key << " has value " << value.first << " " << value.second << "\n";

            if (value.first <= 2 && checkDiagonal_1(value.first, value.second))
            {
                return true;
            }

            if (value.first >= 3 && checkDiagonal_2(value.first, value.second))
            {
                return true;
            }
        }

        return false;
    }

    bool connect4::winner()
    {
        return ( findWinnerHorizontial() || findWinnerVertical() || diagonal());
    }