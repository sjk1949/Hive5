#pragma once

#include "Board.h"
#include "Input.h"

#include <array>

class Game{
public:
    Game();

    /**
     * @brief Realize game loop.
     */
    void game_turn();

private:
    Board board;
    Input input;
    int player; // the player that is playing in this turn (player1: player=1, black; player2: player=-1, white)
    void display_board();
    std::array<int, 2> get_input();
    /**
     * @return true: this player win; false: the game is playing
     */
    bool check_win();
    void switch_player();
};