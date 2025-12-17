#include "Game.h"
#include "Board.h"
#include "Input.h"

#include <iostream>
#include <array>

Game::Game() {
    player = 1;
}

void Game::game_turn(){
    // 显示一张空棋盘
    display_board();
    while (true) {
        // 获取用户输入
        std::array<int, 2> position;
        position = get_input();
        // 改棋盘
        board.add_piece(position[0], position[1], player);
        // 展示改完后的棋盘
        display_board();
        // 检查输赢，如果赢了跳出循环
        if (check_win()) {
            return;
        } else {
            // 切换玩家
            switch_player();
        }
    }
}

void Game::display_board(){
    board.display_board();
}

std::array<int, 2> Game::get_input(){
    return input.get_input();
}

bool Game::check_win(){
    // @todo
    return false;
}

void Game::switch_player(){
    if (player == 1)
    {
        player = -1;
    } else if (player == -1)
    {
        player = 1;
    } else
    {
        std::cout << "Something is wrong, please look around if there is a third player..." << std::endl;
    }
}