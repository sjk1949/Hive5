#include <array>

class Board
{
public:
    static const int SIZE = 15; // board size

    Board();
    /**
     * @brief Make your board after every move visualable?
     */
    void display_board();

private:
    std::array<std::array<int, SIZE>, SIZE> board;

};
