#pragma once

#include <array>

class Board{
public:
    static const int SIZE = 15; // board size

    Board();

    /**
     * @brief Make your board after every move visualable?
     */
    void display_board();

    /**
     * @brief Add a piece to the board, without any check.
     * @param x x (row, 1-15) 0-14
     * @param y y (order, A-O) 0-14
     * @param player the player that add this piece (player1: player=1, black; player2: player=-1, white)
     */
    void add_piece(int x, int y, int player);

    /**
     * @brief Read the status of any point in the board.
     * @param x x (row, 1-15) 0-14
     * @param y y (order, A-O) 0-14
     * @return status 1: player1, black, -1: player2, white, 0: blank
     */
    int get_piece(int x, int y);

private:
    std::array<std::array<int, SIZE>, SIZE> board; // 1: black, -1: white, 0: blank

};
