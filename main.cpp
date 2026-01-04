#include <iostream>
#include <array>

#include "Board.h"
#include "Game.h"
#include "Test.h"

int main() {

    //Test::shapeTest();

    //
    Game game;
    game.init_game();
    game.game_turn();
    //

    return 0;
}