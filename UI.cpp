#include "UI.h"

#include <iostream>
#include "Game.h"
#include "Board.h"

void UI::clear_page() {
    std::cout << "\033[H\033[2J";
}
// 给一个游戏对象，把它画在屏幕上
void UI::display_game(const Game& game) {
    display_board(game.get_board());
    std::cout << "上一次输入用时" << game.get_used_time() << "s.\n";
    display_string(game.message);
    if (game.get_player() == 1) {
        display_string("当前玩家: player1 ●");
    } else {
        display_string("当前玩家: player2 ○");
    }
    display_string("请输入坐标(例如 A1 或 1A):");
}

void UI::display_board(const Board& board) {
    std::cout << board.to_string() << std::endl;
}

void UI::display_string(const std::string& str) {
    std::cout << str << std::endl;
}