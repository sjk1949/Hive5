#include "Shape.h"

Shape::Shape(){
    direction = 0;
    length = 1;
    breaking = 0;
    vacancy1 = true;
    vacancy2 = true;
}

Shape Shape::getShape(const Board& board, std::array<int, 2> position, int direction) {
    return getShape(board, position, board.get_piece(position[0], position[1]), direction); // 以该position处棋子为player
}

Shape Shape::getShape(const Board& board, std::array<int, 2> position, int player, int direction){
    return mergeShape(getShape(board, position, player, direction, 1), getShape(board, position, player, direction, -1));
}

Shape Shape::getShape(const Board& board, std::array<int, 2> position, int player, int direction, int side) {
    // 新建空的Shape对象
    Shape shape;
    shape.direction = direction; // 传入direction参数
    // 记录目前所在的位置
    std::array<int, 2> current_position = position;
    std::array<int, 2> if_next_position; // 特殊情况（两个位置连起来会形成特殊情况）需在这一步就检查下一个position
    // 获取在当前位置的棋子类型
    // int current_piece = player;
    // 不需要， 只是从position开始，以player为假设的连子情况检查

    // 如果当前位置的棋子类型与之前的棋子类型都相同
    //int side = 1;
    for (int i = 0; i < 15; i++)
    {
        current_position = next_position(current_position, direction, side);
        if_next_position = next_position(current_position, direction, side);
        if (shape.breaking == 0)
        {
            if (board.is_on_board(current_position[0], current_position[1])) // 先判断是否在界内
            {
                if (board.get_piece(current_position[0],current_position[1]) == player) //仍为连子        
                {
                    shape.length += 1; //continue;
                }else if (board.get_piece(current_position[0],current_position[1]) == (player * (-1))) //在该处被对方棋子截断
                {
                    shape.vacancy_status(side, false);//shape.vacancy1 = false;
                    return shape;
                }else if (board.get_piece(current_position[0],current_position[1]) == 0) //在该处被空位截断，将breaking改为1
                {
                    // 特殊情况需先检查下一个位置
                    if (board.is_on_board(if_next_position[0], if_next_position[1])) //下一个位置不在界外
                    {
                        if (board.get_piece(if_next_position[0],if_next_position[1]) == player) // 空格后仍为连子，正常处理 
                        {
                            shape.breaking = 1; // 这里breaking会从0变为1，但假装无事发生，breaking=2是两边加起来后可能出现的情况
                            shape.length += 1; //continue;
                        }else if (board.get_piece(if_next_position[0],if_next_position[1]) == (player * (-1))) // 空格后被对方棋子截断，即为没有breaking，连子在上一步已结束
                        {
                            shape.breaking = 0; // 不需要这句，图个安心
                            shape.vacancy_status(side, true);// 没啥用，图个安心
                            //shape.length -= 1;
                            return shape;
                        }else if (board.get_piece(if_next_position[0],if_next_position[1]) == 0) //空格后仍为空格
                        {
                            shape.breaking = 0; // 不需要这句，图个安心
                            shape.vacancy_status(side, true);// 没啥用，图个安心
                            //shape.length -= 1;
                            return shape;
                        }
                    }else // 一个空格后直接到边界
                    {
                        shape.breaking = 0;
                        shape.vacancy_status(side, true);
                        //shape.length -= 1;
                        return shape;
                    }
                    //shape.breaking += 1; // 这里breaking会从0变为1，但假装无事发生，breaking=2是两边加起来后可能出现的情况
                    //continue; //shape.length += 1;
                }
            }else // 接到界外了
            {
                shape.vacancy_status(side, false);//shape.vacancy1 = false;
                return shape;
            }   
        }else if (shape.breaking == 1) // 如果前面已有断点
        {
            if (board.is_on_board(current_position[0], current_position[1])) // 先判断是否在界内
            {
                if (board.get_piece(current_position[0],current_position[1]) == player) //仍为连子        
                {
                    shape.length += 1; //continue;
                }else if (board.get_piece(current_position[0],current_position[1]) == (player * (-1))) //在该处被对方棋子截断
                {
                    shape.vacancy_status(side, false);//shape.vacancy1 = false;
                    return shape;
                }else if (board.get_piece(current_position[0],current_position[1]) == 0) //在该处被空位截断
                {
                    shape.vacancy_status(side, true);// 没啥用，图个安心
                    return shape;
                }
            }else //接到界外了，正常处理，不能算头上有空位，因为那种特殊情况已经排除掉了
            {
                shape.vacancy_status(side, false);//shape.vacancy1 = false;
                return shape;
            }   
        }
    }  
    // 更新Shape对象
    // 如果不同，分情况
    // 是空位？
    // 是棋盘边界？
    // 是对手棋子？
    // 同样更新Shape对象
    // 如果没有获取完整个棋形，当前位置向这个方向上下一个需要观察的位置移动（注意方向包含两边，可以分别生成一个独立的Shape，再合并到一起，可以写一个单独的辅助函数，头文件里已给出），回到获取棋子类型那一步
    // 获取完棋形，返回Shape对象
}

Shape Shape::mergeShape(const Shape& shape1, const Shape& shape2){
    Shape shape;
    shape.direction = shape1.direction; // noly for two shapes with the same direction and starting point, and opposite side
    shape.length = shape1.length + shape2.length -1;
    shape.vacancy1 = shape1.vacancy1;
    shape.vacancy2 = shape2.vacancy2;

    if (shape1.breaking == 0)
    {
        if (shape2.breaking == 0)
        {
            shape.breaking = 0;
        }else if (shape2.breaking == 1)
        {
            shape.breaking = 3;
        }
    }else if (shape1.breaking == 1)
    {
        if (shape2.breaking == 0)
        {
            shape.breaking = 2;
        }else if (shape2.breaking == 1)
        {
            shape.breaking = 4;
        }
    }

    return shape;
}

std::array<int, 2> Shape::next_position(std::array<int, 2> position, int direction, int side){
    if (direction == 0)
    {
        return {position[0], position[1] + side};
    }else if (direction == 1)
    {
        return {position[0] + side, position[1]};
    }else if (direction == 2)
    {
        return {position[0] - side, position[1] + side};
    }else if (direction == 3)
    {
        return {position[0] + side, position[1] + side};
    }else
    {
        return {-1, -1};
    }
}

void Shape::vacancy_status(int side, bool status){
    if (side == 1)
    {
        vacancy1 = status;
    }else if (side == -1)
    {
        vacancy2 = status;
    }
}