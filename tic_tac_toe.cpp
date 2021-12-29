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

// color code reference https://opensource.com/article/19/9/linux-terminal-colors

#include <iostream>
#include <string>
#include <regex>

#define SIZE 3
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

// https://www.cplusplus.com/reference/regex/regex_match/
// goal 1 - user board input has a [SPACE]
// goal 2 - left of space should be valid integer (board location)
// goal 3 - right of space should be valid integer (board location)
void regexUserInput(char board[SIZE][SIZE], bool &player)
{
    std::string pattern_string = "^([0-" + SIZEOFGRID + "]{1}) ([0-" + SIZEOFGRID + "]{1})$";
    // std::string pattern_string = "^([0-2]{1}) ([0-2]{1})$";
    const std::regex pattern(pattern_string);

    std::string usersBoardInput = "";

    // flag to indicate if we want to show the error message
    bool show_error = false;
    std::smatch matches;

    do
    {
        if (show_error == true)
            std::cout << "\n[ Error ] your input: " << usersBoardInput << " is not a valid input\n" 
            "It must be in the boundaries of 0 - 2 of both row and column\n";
        std::cout << "\n";
        std::cout << "Please enter numerical values for the grid location in this format: [""Row""] [""SPACE""] [""Column""]:\n";
        std::getline(std::cin, usersBoardInput);
        show_error = true;

    } while (!std::regex_match(usersBoardInput, matches, pattern));

    // https://www.cplusplus.com/reference/string/stoi/
    //  extract index values
    int row = stoi(matches[1].str());
    int column = stoi(matches[2].str());

    std::cout << "\n";
    std::cout << "row is " << row << "\n";
    std::cout << "column is " << column << "\n";
    std::cout << "\n";

    if (board[row][column] == '.') // it's a period
    {
        board[row][column] = players[player];
        // player switching between X and
        player = player ^ true;
    }
    // Paired with the if statement block, for checking if the cell is (not) a period
    else
    {
        // implemention - If your previous input is the same as the next input.
        std::cout << "You entered a position that has been occuped by: " << board[row][column];
        std::cout << "\n";

        regexUserInput(board, player);
        // std::cout << "Invalid input: rows must be 0 - " << (SIZE - 1) << " and columns must be  0 - " << (SIZE - 1) << "\n";
        // std::cout << "\n";
    }
}

// A function for an empty board that will contain period characters and will be checked or
// be guaranteed that it is infact a period.
bool checkEmptyBoard(char board[SIZE][SIZE])
{
    // My Row, X or I
    for (int x = 0; x < SIZE; x++)
    {
        // My colunm, Y or J
        for (int y = 0; y < SIZE; y++)
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

void userInputBoard(char board[SIZE][SIZE], bool &player)
{
    int row = 0, column = 0;

    std::cout << "\n";
    std::cout << "Please enter your desired row and column [" << row << "] [SPACE] [" << column << "]: \n";
    std::cin >> row;
    std::cin >> column;
    std::cout << "\n";

    // https://stackoverflow.com/questions/18728754/checking-cin-input-stream-produces-an-integer
    while (std::cin.fail())
    {
        std::cout << "Invalid input (Integer not found): Enter your desired row and column this way please [" << row << "] [SPACE] [" << column << "]: \n";
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cin >> row;
        std::cin >> column;
    }

    // Checking for bounds, array bounds
    // if (row <= 2 && column <= 2 && row >= 0 && column >= 0)
    if (row < SIZE && column < SIZE && row >= 0 && column >= 0)
    {
        if (board[row][column] == '.') // it's a period
        {
            board[row][column] = players[player];
            // player switching between X and
            player = player ^ true;
        }
        // Paired with line 37 if statement block, for checking if the cell is (not) a period
        else
        {
            // implemention - If your previous input is the same as the next input.
            std::cout << "You entered the same row and column again [" << row << "] [SPACE] [" << column << "]:\nPlease enter again: \n";
            userInputBoard(board, player);
        }
    }
    else
    {
        std::cout << "Invalid input: rows must be 0 - " << (SIZE - 1) << " and columns must be  0 - " << (SIZE - 1) << "\n";
        std::cout << "\n";
    }
}

bool isInRange(int x)
{
    return 0 <= x && x <= SIZE - 1;
}

std::pair<int, int> getValidTokens(std::vector<std::string> tokens, int correct_size)
{
    // we have correct number of tokens 2
    if (tokens.size() == correct_size && 
        // each token is of length 1
        tokens[0].size() == 1 &&         
        tokens[1].size() == 1 &&
        isdigit(tokens[0][0]) &&
        // each token looks like an digit 
        isdigit(tokens[1][0]))
    {
        int row = stoi(tokens[0]);
        int col = stoi(tokens[1]);

        if (isInRange(row) && isInRange(col))
        {
            return std::pair<int, int>(row, col);
        }
        else
        {
            // index out of range
            return std::pair<int, int>(-1, -1); 
        }
    }
    // not an integer or too many spaces
    return std::pair<int, int>(-2, -2); 
}

void delimiterUserInput(char board[SIZE][SIZE], bool &player)
{
    std::vector<std::string> tokens;
    std::string inputs;

    std::cout << "Please enter your desired row and column [""Row""] [SPACE] [""Column""]:\n";

    bool terminate = false;

    while (!terminate && std::getline(std::cin, inputs))
    {
        std::istringstream iss(inputs);
        std::string token;

        while (std::getline(iss, token, ' '))
            tokens.push_back(token);

        std::pair<int, int> indexValues = getValidTokens(tokens, 2);

        if (indexValues.first >= 0)
        {
            // board[indexValues.first][indexValues.second] = players[player];
            // terminate = true;

            if (board[indexValues.first][indexValues.second] == '.') // it's a period
            {
                board[indexValues.first][indexValues.second] = players[player];
                terminate = true;
                player = player ^ true;
            }
            // Paired with the if statement block, for checking if the cell is (not) a period
            else
            {
                // implemention - If your previous input is the same as the next input.
                std::cout << "You entered a position that has been occuped by: " << board[indexValues.first][indexValues.second];
                std::cout << "\n";
            }
        }
        else if (indexValues.first == -1)
            std::cout << "Index out of range (0 - 2) both row and column \n";

        else
            std::cout << "Index is not valid: No integer found or too many spaces\n";
        tokens.clear();
    }
}

void printTicTacToe(char board[SIZE][SIZE], bool player, const bool winner)
{

    std::cout << "+---+---+---+";
    std::cout << "\n";

    // Row
    for (int i = 0; i < SIZE; i++)
    {
        std::cout << "|";
        // Column
        for (int j = 0; j < SIZE; j++)
        {
            std::cout << " " << colorElement(board[i][j]) << " ";
            std::cout << "|";
        }
        // Printing newline of rows (0 - 2) or (1 - SIZE)
        std::cout << "\n";
        std::cout << "+---+---+---+";
        std::cout << "\n";
    }

    std::cout << "\n";

    if (winner == false)
    {
        std::cout << "The player is: " << players[player] << "\n";
    }
}

bool findWinnerHorizontial(char board[SIZE][SIZE])
{
    // 1. Visit every cell with nested for loop
    // 2. Look at each character to see if their in consecutive rows
    // 2a. Check to see if it's a uppercase "X" or "O"
    // 2b. Compare the next index (Y + 1)
    // 2c. If they are equal,compare the next neighboring index.

    for (int x = 0; x < SIZE; x++)
    {
        if (board[x][0] == 'X' || board[x][0] == 'O')
        {
            if (board[x][0] == board[x][1] && board[x][0] == board[x][2])
            {
                // std::cout << "The winner is horizontial: " << board[x][0] << "\n";
                return true;
            }
        }
    }

    return false;
}

bool findWinnerVertical(char board[SIZE][SIZE])
{

    for (int y = 0; y < SIZE; y++)
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

bool findWinnerDiagonial(char board[SIZE][SIZE])
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

bool winner(char board[SIZE][SIZE])
{
    return (findWinnerHorizontial(board) || findWinnerVertical(board) || findWinnerDiagonial(board));
}

bool hasEmptyProperties(char emptyBoard[SIZE][SIZE])
{

    for (int row = 0; row < SIZE; row++)
    {
        for (int column = 0; column < SIZE; column++)
        {
            if (emptyBoard[row][column] == '.')
            {
                return true;
            }
        }
    }

    std::cout << "\n";
    std::cout << "Failed to find empty space on the game board\n";
    return false;
}

// Testing functions for successes and/or failures. AKA Test cases
bool tests()
{
    char emptyBoard[SIZE][SIZE];

    for (int row = 0; row < SIZE; row++)
    {
        for (int column = 0; column < SIZE; column++)
        {
            emptyBoard[row][column] = '.';
        }
    }

    bool test1 = checkEmptyBoard(emptyBoard);

    // Populated with periods so we considerate it empty.
    char notAnEmptyBoard[SIZE][SIZE];

    // Put !(not) because it expects to check the non-empty board to come back false.
    bool test2 = !checkEmptyBoard(notAnEmptyBoard);

    // Horizontially winning Tic-Tac-Toe.
    char winningBoardHorizontial[SIZE][SIZE] = {{'O', 'X', 'O'},
                                                {'X', 'X', 'X'},
                                                {'X', 'O', 'O'}};
    // Vertically winning Tic-Tac-Toe
    char winningBoardVertical[SIZE][SIZE] =
        {
            {'O', 'X', 'O'},
            {'X', 'O', 'O'},
            {'X', 'O', 'O'}};

    // Diagonially winning Tic-Tac-Toe in two directions (looking up or looking down) - **looking down** (Top left to bottom right)
    char winningBoardDiagonial[SIZE][SIZE] =
        {
            {'O', 'X', 'X'},
            {'X', 'O', 'O'},
            {'X', 'O', 'O'}};

    // Diagonially winning Tic-Tac-Toe in two directions (looking up or looking down) - **looking up** (Bottom left to top right)
    char winningBoardDiagonial2[SIZE][SIZE] =
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
    bool winnerOfGame = false;

    char gameBoard[3][3] = {{'.', '.', '.'},
                            {'.', '.', '.'},
                            {'.', '.', '.'}};

    while (!winnerOfGame && hasEmptyProperties(gameBoard))
    {
        // userInputBoard(gameBoard, player);
        regexUserInput(gameBoard, player);
        // delimiterUserInput(gameBoard, player);
        winnerOfGame = winner(gameBoard);
        printTicTacToe(gameBoard, player, winnerOfGame);
    }

    if (winner(gameBoard))
    {
        std::cout << "The winner is: " << players[(player ^ true)] << "\n";
    }

    else
    {
        std::cout << "\n";
        std::cout << "The game is a draw, please play again\n";
    }

    return 0;
}