#include <iostream>
#include "connect4.h"

int main()
{
    connect4 game;
    while (!game.winnerOfGame && game.hasEmptyProperties())
    {
        game.printConnect4();
        game.winnerOfGame = game.chooseColumnPosition();
        // fillInGameBoard(connect4Board, player);
    }
    // game.printConnect4();
    // game.chooseColumnPosition();
    // game.fillInGameBoard();
    // game.winner();
    // game.winner();
}