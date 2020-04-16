#include <iostream>
#include <limits>
#include <unordered_map>

using umi32i = std::unordered_map<uint32_t, int>;

struct Node
{
    int data;
    std::shared_ptr<Node> left, right;
    Node(int data, std::shared_ptr<Node> left=nullptr, std::shared_ptr<Node> right=nullptr)
    : data(data),
    left(left),
    right(right) {}
};

uint32_t FlattenLevelMinSum(std::shared_ptr<Node> root, umi32i &level_map, uint32_t min_level = 0, uint32_t curr_level = 0)
{
    uint32_t ret_level = min_level;
    if(!root) return ret_level;

    level_map[curr_level] += root->data;
    if(level_map[ret_level] > level_map[curr_level]) ret_level = curr_level;

    auto min_level_left = FlattenLevelMinSum(root->left, level_map, ret_level, curr_level+1);
    auto min_level_right = FlattenLevelMinSum(root->right, level_map, ret_level, curr_level+1);

    if(level_map[min_level_left] < level_map[ret_level]) ret_level = min_level_left;
    if(level_map[min_level_right] < level_map[ret_level]) ret_level = min_level_right;

    return ret_level;
}

int main()
{

    umi32i level_map;

    // test case 1:
    auto root = std::make_shared<Node>(10, 
                    std::make_shared<Node>(2, 
                        std::make_shared<Node>(4), 
                        std::make_shared<Node>(1)), 
                    std::make_shared<Node>(8, 
                        nullptr, 
                        std::make_shared<Node>(2)));
    std::cout<<level_map[FlattenLevelMinSum(root, level_map)]<<"\n";
    level_map.clear();

    // test case 2:
    auto root1 = std::make_shared<Node>(9);
    std::cout<<level_map[FlattenLevelMinSum(root1, level_map)]<<"\n";
    level_map.clear();

    // test case 3:
    auto root2 = nullptr;
    std::cout<<level_map[FlattenLevelMinSum(root2, level_map)]<<"\n";
    level_map.clear();

    // test case 4:
    auto root3 = std::make_shared<Node>(10, 
                    nullptr,
                    std::make_shared<Node>(8, 
                        nullptr, 
                        std::make_shared<Node>(2)));
    std::cout<<level_map[FlattenLevelMinSum(root3, level_map)]<<"\n";
    level_map.clear();

    return 0;
}