#pragma once

#include <array>
#include <string>

class Board{
public:
    static const int SIZE = 15; // board size

    Board();

    /**
     * @brief Store your board.
     */
    std::string to_string() const;

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
    int get_piece(int x, int y) const;

    /**
     * @brief Check if the position is on board.
     */
    bool is_on_board(int x, int y) const;

private:
    std::array<std::array<int, SIZE>, SIZE> board; // 1: black, -1: white, 0: blank

};
