#include <iostream>
#include "colorcode.h"
#define WINNING_PATTERN 4


class connect4
{
    private:
        
    public:
        char players = 'X';
        bool player = true;
        bool winnerOfGame = false;
        const static int NUM_OF_ROWS = 6;
        const static int NUM_OF_COLUMNS = 7;
        char board[NUM_OF_ROWS][NUM_OF_COLUMNS];
        int chosenColumn = 0;
        connect4();
        void printConnect4();
        bool hasEmptyProperties();
        bool chooseColumnPosition();
        void fillInGameBoard();
        bool findWinnerHorizontial();
        bool findWinnerVertical();
        bool winner();

};

    connect4::connect4()
    {
        for (int row = 0; row < NUM_OF_ROWS; row++)
        {
            for (int column = 0; column < NUM_OF_COLUMNS; column++)
            {
                board[row][column] = ' ';
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

    bool connect4::findWinnerHorizontial()
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

    bool connect4::winner()
    {
        return (findWinnerHorizontial() || findWinnerVertical());
    }