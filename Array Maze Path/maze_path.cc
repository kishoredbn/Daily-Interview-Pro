#include <iostream>
#include <vector>

using vb = std::vector<bool>;
using vvb = std::vector<vb>;

int32_t MoveAlongPath(const vvb &input, const int32_t x, const int32_t y, const int32_t destination_x, const int32_t destination_y)
{
    int32_t ret = 0;
    if(x == destination_x && y == destination_y)  return 1;
    if(x > destination_x || y > destination_y) return 0;
    if(input[x][y]) return 0;

    auto ret_right = MoveAlongPath(input, x+1, y, destination_x, destination_y);
    auto ret_down = MoveAlongPath(input, x, y+1, destination_x, destination_y);

    return ret_right + ret_down;
}

int32_t CountMazePath(const vvb &input)
{
    int32_t ret = 0;
    if(input.empty()) return ret;

    ret = MoveAlongPath(input, 0, 0, input.size()-1, input[0].size()-1);

    return ret;
}

int main()
{
    // test case 1:
    vvb input1 = {{0, 1, 0}, {0, 0, 1}, {0, 0, 0}};
    std::cout<<CountMazePath(input1)<<"\n";

    // test case 2:
    vvb input2 = {{0, 1, 0}, {0, 1, 1}, {0, 0, 0}};
    std::cout<<CountMazePath(input2)<<"\n";

     // test case 2:
    vvb input3 = {{0, 1, 0}, {0, 1, 1}, {1, 0, 0}};
    std::cout<<CountMazePath(input3)<<"\n";

    return 0;
}