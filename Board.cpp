#include "Board.h"

#include <iostream>

Board::Board(){
    for (auto& row : board) {
        for (auto& order : row) {
            order = 0;
        }
    }
}

void Board::display_board() {
    int i=1;
    for (auto row : board) {
        for (auto order : row) {
            if (order==0){
                std::cout << "+" << " ";
            } else if (order>0){
                std::cout << "●" << " ";
            } else if (order<0){
                std::cout << "○" << " ";
            } else {
                std::cout << "😼" << " ";
            }
        }
        std::cout << " " << i << std::endl;
        i++;
    }
}