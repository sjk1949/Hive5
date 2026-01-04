#pragma once

#include "Board.h"
#include "Input.h"
#include "UI.h"
#include "AI.h"

#include <array>

class Game{
public:
    std::string message;

    Game();

    /**
     * @brief Initailize game settings.
     */
    void init_game();
    /**
     * @brief Realize game loop.
     */
    void game_turn();
    void update();
    const Board& get_board() const;
    const int get_player() const;

private:
    Board board;
    Input input;
    UI ui;
    AI ai;
    int player; // the player that is playing in this turn (player1: player=1, black; player2: player=-1, white)
    bool isAI1; // player1 is AI: true, player1 is real person: false
    bool isAI2; // player2 is AI: true, player2 is real person: false
    std::array<int, 2> get_position(Board board, int player);
    /**
     * @return true: this position is empty, false:this position already have piece
     */
    bool check_position(std::array<int, 2>);
    /**
     * @return true: this player win; false: the game is playing
     */
    bool check_win();
    void switch_player();
    void write_message(std::string);
    void clear_message();
    bool current_player_isAI();
};