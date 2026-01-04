#pragma once

#include "Board.h"
#include "Input.h"
#include "UI.h"
#include "AI.h"

#include <array>
#include <chrono>

class Game{
public:
    static const int TIME_LIMIT = 15; // time limit (seconds) for each player in each turn

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
    const int get_used_time() const;

private:
    // Game Components
    Board board;
    Input input;
    UI ui;
    AI ai;

    // Game States
    bool is_over;
    std::chrono::steady_clock::time_point start_time;
    int used_time; // time (seconds) player used to make a valid move.

    // Game Settings
    int player; // the player that is playing in this turn (player1: player=1, black; player2: player=-1, white)
    bool isAI1; // player1 is AI: true, player1 is real person: false
    bool isAI2; // player2 is AI: true, player2 is real person: false
    bool useTimer; // time limit is applied: true

    std::array<int, 2> get_position(Board board, int player);
    /**
     * @return true: this position is empty, false:this position already have piece
     */
    bool check_position(std::array<int, 2>);
    /**
     * @return true: this player win; false: the game is playing
     */
    bool check_win();
    /**
     * @return time (seconds) passed by last move.
     */
    int get_time_elapsed();
    void switch_player();
    void write_message(std::string);
    void clear_message();
    bool current_player_isAI();
};