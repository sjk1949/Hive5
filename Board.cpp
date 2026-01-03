#include "Board.h"

#include <sstream>
#include <string>

Board::Board(){
    for (auto& row : board) {
        for (auto& order : row) {
            order = 0;
        }
    }
}

std::string Board::to_string() const{
    std::stringstream sboard;
    int i=1;
    for (auto row : board) {
        for (auto order : row) {
            if (order==0){
                sboard << " + ";
            } else if (order==1){
                sboard << " ● ";
            } else if (order==-1){
                sboard << " ○ ";
            } else {
                sboard << "😼 ";
            }
        }
        sboard << " " << i << "\n";
        i++;
    }
    sboard << " A  B  C  D  E  F  G  H  I  G  K  L  M  N  O \n";
    return sboard.str();
}

void Board::add_piece(int x, int y, int player){
    board[x][y] = player;
}

int Board::get_piece(int x, int y) const{
    return board[x][y];
}

bool Board::is_on_board(int x, int y) const{
    if ( x >= 0 && x <= 14 && y >=0 && y <= 14 )
    {
        return true;
    }else
    {
        return false;
    }
}