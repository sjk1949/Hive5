#pragma once

#include <array>
#include "Board.h"

class Shape{
public:
    int direction; // 0: ——, 1: |, 2: /, 3: \.
    int length; // including break
    int breaking; // if continues after break (breaking=0:没有空格；1:某个side方向有一个空格；2：side=1方向有一个空格，side=-1方向没有空格；3：side=1方向没有空格，side=-1方向有一个空格；4：side=1方向有一个空格，side=-1方向有一个空格)
    bool vacancy1; // true: can add piece at one end (right or down, side=1)
    bool vacancy2; // true: can add piece at the other end (left or up, side=-1)

    Shape();

    /**
     * @brief 这个函数没有给定pos位置的棋子类型，这说明棋盘上这个位置已经存在棋子，需要判断已经存在的棋子的连子情况
     */
    static Shape getShape(const Board& board, std::array<int, 2> position, int direction);
    /**
     * @brief 这个函数给定pos位置的棋子类型，这说明需要判断假设落子player类型在棋盘上，棋子的连子情况
     */
    static Shape getShape(const Board& board, std::array<int, 2> position, int player, int direction);
    /**
     * @brief 这个函数给定pos位置的棋形，这说明需要判断假设落子player类型在棋盘上，棋子的连子情况
     * @param side 决定向给定方向的哪一边获取棋形(1: 右 下； -1： 左 上)
     */
    static Shape getShape(const Board& board, std::array<int, 2> position, int player, int direction, int side);

private:
    /**
     * @brief 将同一个方向向两边延申的棋形合并起来
     * @param shape1 the shape that side=1
     * @param shape2 the shape that side=-1
     */
    static Shape mergeShape(const Shape& shape1, const Shape& shape2);

    /**
     * @brief side=1:向右或下，side=-1:向左或上
     */
    static std::array<int, 2> next_position(std::array<int, 2> position, int direction, int side);

    /**
     * @brief 将某一边的vacancy的状态修改为staus
     */
    void vacancy_status(int side, bool status);
};