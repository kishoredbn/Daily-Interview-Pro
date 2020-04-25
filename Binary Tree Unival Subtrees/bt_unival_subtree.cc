#include <iostream>

struct Node
{
    int32_t data;
    std::shared_ptr<Node> left, right;
    Node(int32_t data, std::shared_ptr<Node> left=nullptr, std::shared_ptr<Node> right=nullptr)
    : data(data),
    left(left),
    right(right) {}
};

int32_t CountUnival(std::shared_ptr<Node> node, int val = 0)
{
    int32_t ret = 0;
    if(!node) return ret;

    auto ret_l = CountUnival(node->left, node->data);
    auto ret_r = CountUnival(node->right, node->data);

    if(val != node->data) ret = 1;
    ret += ret_l + ret_r;

    return ret;
}

int32_t GetCountUnival(std::shared_ptr<Node> node)
{
    if(!node) return 0;
    return CountUnival(node, !node->data);
}

int main()
{
    // test case 1:
    std::shared_ptr<Node> root1 = std::make_shared<Node>(0,
                                        std::make_shared<Node>(1),
                                        std::make_shared<Node>(0,
                                                std::make_shared<Node>(1,
                                                        std::make_shared<Node>(1),
                                                        std::make_shared<Node>(1)),
                                                std::make_shared<Node>(0)));
    std::cout<<GetCountUnival(root1)<<"\n";

    // test case 2:
    std::shared_ptr<Node> root2 = std::make_shared<Node>(0,
                                        std::make_shared<Node>(0),
                                        std::make_shared<Node>(0,
                                                std::make_shared<Node>(0,
                                                        std::make_shared<Node>(0),
                                                        std::make_shared<Node>(0)),
                                                std::make_shared<Node>(0)));
    std::cout<<GetCountUnival(root2)<<"\n";

    // test case 3:
    std::shared_ptr<Node> root3 = std::make_shared<Node>(0,
                                        std::make_shared<Node>(1),
                                        std::make_shared<Node>(2,
                                                std::make_shared<Node>(3,
                                                        std::make_shared<Node>(4),
                                                        std::make_shared<Node>(5)),
                                                std::make_shared<Node>(6)));
    std::cout<<GetCountUnival(root3)<<"\n";

    // test case 4:
    std::shared_ptr<Node> root4 = std::make_shared<Node>(0,
                                        std::make_shared<Node>(1),
                                        std::make_shared<Node>(2,
                                                std::make_shared<Node>(3,
                                                        std::make_shared<Node>(3),
                                                        std::make_shared<Node>(3)),
                                                std::make_shared<Node>(3)));
    std::cout<<GetCountUnival(root4)<<"\n";
    return 0;
}