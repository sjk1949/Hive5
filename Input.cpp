#include "Input.h"

#include <iostream>
#include <array>

std::array<int, 2> Input::get_input(){
    std::array<int, 2> input_result;
    std::cout << "请输入位置（行数）" << std::endl;
    std::cin >> input_result[0];
    std::cout << "请输入位置（列数）" << std::endl;
    std::cin >> input_result[1];
    return input_result;
}