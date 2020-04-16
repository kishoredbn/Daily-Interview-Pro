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

uint32_t FlattenLevelMaxSum(std::shared_ptr<Node> root, umi32i &level_map, uint32_t max_level = 0, uint32_t curr_level = 0)
{
    uint32_t ret_level = max_level;
    if(!root) return ret_level; // caution: for null value returning 0

    level_map[curr_level] += root->data;
    if(level_map[ret_level] < level_map[curr_level]) ret_level = curr_level;

    auto max_level_left = FlattenLevelMaxSum(root->left, level_map, ret_level, curr_level+1);
    auto max_level_right = FlattenLevelMaxSum(root->right, level_map, ret_level, curr_level+1);

    if(level_map[max_level_left] > level_map[ret_level]) ret_level = max_level_left;
    if(level_map[max_level_right] > level_map[ret_level]) ret_level = max_level_right;

    return ret_level;
}

int main()
{

    umi32i level_map;

    // test case 1:
    auto root = std::make_shared<Node>(1, 
                    std::make_shared<Node>(4, 
                        std::make_shared<Node>(3), 
                        std::make_shared<Node>(2)), 
                    std::make_shared<Node>(5, 
                        std::make_shared<Node>(4), 
                        std::make_shared<Node>(-1)));
    std::cout<<FlattenLevelMaxSum(root, level_map)<<"\n";
    level_map.clear();

    // test case 2:
    auto root1 = std::make_shared<Node>(9);
    std::cout<<FlattenLevelMaxSum(root1, level_map)<<"\n";
    level_map.clear();

    // test case 3:
    auto root2 = nullptr;
    std::cout<<FlattenLevelMaxSum(root2, level_map)<<"\n";
    level_map.clear();

    // test case 4:
    auto root3 = std::make_shared<Node>(10, 
                    nullptr,
                    std::make_shared<Node>(8, 
                        nullptr, 
                        std::make_shared<Node>(20)));
    std::cout<<FlattenLevelMaxSum(root3, level_map)<<"\n";
    level_map.clear();

    return 0;
}