#include "checkers.h"

int main()
{
    checkers game;
    game.intializePiecesOnBoard();
    game.printBoard();
    game.move();
    game.printBoard();
    return 0;
}