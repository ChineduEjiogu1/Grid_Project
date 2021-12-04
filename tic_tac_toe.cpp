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

    char notAnEmptyBoard[3][3];

    // Put !(not) because it's expected to check the non-empty board to come back false.
    bool test2 = !checkEmptyBoard(notAnEmptyBoard);

    // pseduo-code
    // return true (test1 && test2) == true;

    return (test1 && test2);

}

int main()
{
    bool results = tests();

    if(results == false){

        std::cout << "Test Failed" << std::endl;

    }else{

        std::cout << "Test was a Success" << std::endl;
    }

    return 0;
}