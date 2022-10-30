#include <iostream>
#include "connect4.h"

int main()
{
    connect4 game;
    while (!game.winnerOfGame && game.hasEmptyProperties())
    {
        game.printConnect4();
        game.winnerOfGame = game.chooseColumnPosition();
    }

    game.printConnect4();
    std::cout << "The winner is: " << game.players << "\n";
}