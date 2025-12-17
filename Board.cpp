#include "Board.h"

#include <iostream>

Board::Board(){
    for (auto& row : board) {
        for (auto& order : row) {
            order = 0;
        }
    }
}

void Board::display_board(){
    int i=1;
    for (auto row : board) {
        for (auto order : row) {
            if (order==0){
                std::cout << " + ";
            } else if (order==1){
                std::cout << " ● ";
            } else if (order==-1){
                std::cout << " ○ ";
            } else {
                std::cout << "😼 ";
            }
        }
        std::cout << " " << i << std::endl;
        i++;
    }
    std::cout << " A  B  C  D  E  F  G  H  I  G  K  L  M  N  O " << std::endl << std::endl;
}

void Board::add_piece(int x, int y, int player){
    board[x][y] = player;
}

int Board::get_piece(int x, int y){
    return board[x][y];
}