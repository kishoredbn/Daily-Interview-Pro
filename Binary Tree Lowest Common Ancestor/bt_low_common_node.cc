#include <iostream>
#include <stack>

struct Node
{
    int data;
    std::shared_ptr<Node> left, right;
    Node(int data, std::shared_ptr<Node> left=nullptr, std::shared_ptr<Node> right=nullptr)
    : data(data),
    left(left),
    right(right) {}
};

int FindNodeFromPositionStack(std::shared_ptr<Node> node, std::stack<int> &stk_node, const int curr_position = 1)
{ // traverses a tree in the given stack path and gets the value out of it
    int ret = -1;
    if(!node) return ret;
    
    if(curr_position == stk_node.top())
    {
        stk_node.pop();

        if(stk_node.empty()) return node->data;

        ret = FindNodeFromPositionStack(node->left, stk_node, 2*curr_position);
        if(ret != -1) return ret;
        ret = FindNodeFromPositionStack(node->right, stk_node, 2*curr_position + 1);
    }
    return ret;
}

int FindNode(std::shared_ptr<Node> node, const int position) // create a stack of path from root to required position
{
    int ret = -1;
    if(!node) return ret;
    if(!position) return ret;

    std::stack<int> stk_node;
    auto next_position = position;
    while(next_position)
    {
        stk_node.emplace(next_position);
        next_position /= 2;
    }

    ret = FindNodeFromPositionStack(node, stk_node);
    return ret;
}

int FindNodePosition(std::shared_ptr<Node> node, const int val, int curr_node = 1) // search for a value in node and get the position
{
    int ret = 0;
    if(!node) return ret;

    if(node->data == val) return curr_node;

    ret= FindNodePosition(node->left, val, 2*curr_node);
    if(!ret)
    ret = FindNodePosition(node->right, val, 2*curr_node + 1);

    return ret;
}

int FindCommonPosition(int a, int b) // find the lowest common ancestor position mathematically
{
    if(!a || !b) return 0;
    while(a != b)
    {
        if(a > b)
            a /= 2;
        else
            b /= 2;
    }
    return a;
}

int LowCommonNode(std::shared_ptr<Node> node, int a, int b) // master function
{
    int ret = -1;
    if(!node) return -1;

    if(a == b) // if node a and b are same, they are thenselves the common node
    {
        auto position = FindNodePosition(node, a); // Finds only position of a given node
        if(position) ret = FindNode(node, position);
    }
    else // a != b
    {
        auto position_a = FindNodePosition(node, a);
        if(!position_a) return ret; // if a is found then search for b, or just exit
        auto position_b = FindNodePosition(node, b);
        if(!position_b) return ret; // if b is found then do further processing, or just exit
        
        auto common_ancestor_position = FindCommonPosition(position_a, position_b); // find the common ancestor position
        ret = FindNode(node, common_ancestor_position); // now get the element
    }

    return ret;
}

int main()
{
    // test case 1:
    auto root = std::make_shared<Node>(1,
                    std::make_shared<Node>(4,
                        std::make_shared<Node>(3),
                        std::make_shared<Node>(2)),
                    std::make_shared<Node>(5,
                        std::make_shared<Node>(4),
                        std::make_shared<Node>(6)));
    std::cout<<LowCommonNode(root, 4, 6)<<"\n";

    // test case 2:
    auto root1 = std::make_shared<Node>(9);
    std::cout<<LowCommonNode(root1, 9, 9)<<"\n";

    // test case 3:
    auto root2 = nullptr;
    std::cout<<LowCommonNode(root2, 4, 6)<<"\n";

    // test case 4:
    auto root3 = std::make_shared<Node>(10,
                    nullptr,
                    std::make_shared<Node>(8,
                        nullptr,
                        std::make_shared<Node>(20)));
    std::cout<<LowCommonNode(root3, 8, 12)<<"\n";

    // test case 5:
    auto root4 = std::make_shared<Node>(10,
                    nullptr,
                    std::make_shared<Node>(8,
                        nullptr,
                        std::make_shared<Node>(20)));
    std::cout<<LowCommonNode(root4, 8, 20)<<"\n";

    return 0;
}
