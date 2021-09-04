#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

int TapWater(const std::vector<int>& input) {
    std::stack<int> water_level;
    
    int curr_level = 0;
    // left swipe - assume we can fill water all the way till the end to a hight equals last highest "level"
    for(auto &level : input) {
        if(curr_level > level) {
            water_level.push(curr_level - level);
        } else {
            curr_level = level;
            water_level.push(0);
        }
    }
    
    int total_water = curr_level = 0;
    // right swipe - assume we can fill water all the way till the end to a hight equals last highest "level"
    while(auto size = water_level.size()) {
        auto level = water_level.top();
        if(curr_level  <  input[size - 1]) {
            curr_level = input[size - 1];
        }
        else {
            total_water += std::min(curr_level - input[size - 1], level);
        }
        water_level.pop();
    }
    
    return total_water;
}

int main() {
    // test case 1
    {
        std::vector<int> vinput = {1, 2, 4, 10, 5, 5, 3, 6, 7,  3, 4, 5, 1};
        auto water_tapped = TapWater(vinput);
        std::cout <<  water_tapped << "\n";
    }
    // test case 2
    {
        std::vector<int> vinput = {1, 2, 4, 10, 0, 0, 0, 0, 0, 0, 0, 15, 1};
        auto water_tapped = TapWater(vinput);
        std::cout <<  water_tapped << "\n";
    }
    // test case 3
    {
        std::vector<int> vinput = {1, 2, 8, 10, 0, 0, 0, 0, 0, 0, 0, 15, 14};
        auto water_tapped = TapWater(vinput);
        std::cout <<  water_tapped << "\n";
    }
    // test case 4
    {
        std::vector<int> vinput = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
        auto water_tapped = TapWater(vinput);
        std::cout <<  water_tapped << "\n";
    }
    
    return 0;
}