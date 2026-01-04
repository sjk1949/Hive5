#include "Game.h"
#include "Board.h"
#include "Input.h"
#include "UI.h"
#include "AI.h"
#include "Shape.h"

#include <iostream>
#include <array>

Game::Game() {
    player = 1;
    isAI1 = false;
    isAI2 = false;
    useTimer = false;
    is_over = false;
    used_time = 0;
}

const Board& Game::get_board() const{
    return board;
}

const int Game::get_player() const{
    return player;
}

const int Game::get_used_time() const{
    return used_time;
}

void Game::init_game() {
    char get_char;
    std::cout << "玩家1是否是AI？(Y/N)";
    std::cin >> get_char;
    isAI1 = (get_char == 'Y' || get_char == 'y') ? true : false;
    std::cout << "玩家2是否是AI？(Y/N)";
    std::cin >> get_char;
    isAI2 = (get_char == 'Y' || get_char == 'y') ? true : false;
    std::cout << "是否启用时间限制？(Y/N)";
    std::cin >> get_char;
    useTimer = (get_char == 'Y' || get_char == 'y') ? true : false;
}

void Game::game_turn(){
    start_time = std::chrono::steady_clock::now();
    while (!is_over) {
        update();
    }
    // 如果游戏结束，最后一次绘制屏幕
    ui.clear_page();
    ui.display_game(*this);
}

void Game::update(){
    ui.clear_page();
    ui.display_game(*this); //所有的显示都在这里进行，每一次循环刷新一次
    // 获取用户输入
    std::array<int, 2> position;
    position = get_position(board, player);
    if (position[0] == -1) {
        write_message("输入非法，请输入 A1 到 O15 范围内的坐标。");
        return;
    }
    // 检查位置是否可以落子：非乱码，范围内（否则position={-1,-1}），无子
    // 如果可以落子，修改棋盘，换玩家
    if (!check_position(position)) {
        write_message("输入非法，该位置已有棋子");
        return;
    }
    clear_message();
    // 更新落子用时
    used_time = get_time_elapsed();
    // 如果开启计时器且时间已到，该玩家直接判负
    if (useTimer && used_time > TIME_LIMIT) {
        write_message("时间已到，自动认输！");
        is_over = true;
        return;
    }
    // 改棋盘
    board.add_piece(position[0], position[1], player);
    // 弃用，我们不再单独展示改完后的棋盘，直接随游戏统一刷新，这样更新逻辑里就不需要考虑怎么显示的问题了
    // display_board();
    // 检查输赢，如果赢了跳出循环
    if (check_win()) {
        is_over = true;
        return;
    } else {
        // 切换玩家
        switch_player();
        // 重置计时器
        start_time = std::chrono::steady_clock::now();
    }

    /* 测试Shape.cpp
    std::cout << "shape from H8, for player1: " << std::endl;
    Shape shape0 = Shape::getShape(board, {7,7}, 1, 0);
    Shape shape1 = Shape::getShape(board, {7,7}, 1, 1);
    Shape shape2 = Shape::getShape(board, {7,7}, 1, 2);
    Shape shape3 = Shape::getShape(board, {7,7}, 1, 3);
    std::cout << "direction 0 (0: ——, 1: |, 2: /, 3: \\ ): length: " << shape0.length << ", real length: " << shape0.real_length << ", breaking: " << shape0.breaking << ", vacancy1 and vacancy2: " << shape0.vacancy1 << shape0.vacancy2 << std::endl;
    std::cout << "direction 1 (0: ——, 1: |, 2: /, 3: \\ ): length: " << shape1.length << ", real length: " << shape1.real_length << ", breaking: " << shape1.breaking << ", vacancy1 and vacancy2: " << shape1.vacancy1 << shape1.vacancy2 << std::endl;
    std::cout << "direction 2 (0: ——, 1: |, 2: /, 3: \\ ): length: " << shape2.length << ", real length: " << shape2.real_length << ", breaking: " << shape2.breaking << ", vacancy1 and vacancy2: " << shape2.vacancy1 << shape2.vacancy2 << std::endl;
    std::cout << "direction 3 (0: ——, 1: |, 2: /, 3: \\ ): length: " << shape3.length << ", real length: " << shape3.real_length << ", breaking: " << shape3.breaking << ", vacancy1 and vacancy2: " << shape3.vacancy1 << shape3.vacancy2 << std::endl;
    std::cout << "score for i8, for player 1: " << ai.calculate_score(board, {7,8},1) << std::endl;
    std::cout << "score for j8, for player 1: " << ai.calculate_score(board, {7,9},1) << std::endl;
    */
}

std::array<int, 2> Game::get_position(Board board, int player){
    if (current_player_isAI())
    {
        return ai.place_piece(board, player);
    }else
    {
        return input.get_input();
    }
}

bool Game::check_win(){
    // @todo
    return false;
}

int Game::get_time_elapsed() {
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start_time).count();
    return static_cast<int>(elapsed);
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
        write_message("Something is wrong, please look around if there is a third player...");
    }
}

bool Game::check_position(std::array<int, 2> position){
    return board.get_piece(position[0], position[1]) == 0;
}

void Game::write_message(std::string str){
    message += str;
    message += "\n";
}

void Game::clear_message(){
    message = "";
}

bool Game::current_player_isAI(){
    if (player == 1)
    {
        return isAI1;
    }else
    {
        return isAI2;
    }
}