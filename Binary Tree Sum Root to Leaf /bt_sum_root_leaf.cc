#include <iostream>

struct Node
{
    uint32_t data;
    std::shared_ptr<Node> left, right;
    Node(uint32_t data, std::shared_ptr<Node> left=nullptr, std::shared_ptr<Node> right=nullptr)
    : data(data),
    left(left),
    right(right) {}
};

uint32_t SumRootLeaf(std::shared_ptr<Node> node, uint32_t sum = 0)
{
    if(!node) return 0;

    auto curr_val = sum*10 + node->data;
    auto sum_l = SumRootLeaf(node->left, curr_val);
    auto sum_r = SumRootLeaf(node->right, curr_val);

    if(!(sum_l + sum_r)) return curr_val; // current node could be a leaf node 

    return sum_l + sum_r;
}

int main()
{
    // test case 1:
    std::shared_ptr<Node> root1 = std::make_shared<Node>(1, 
                                std::make_shared<Node>(2,
                                    std::make_shared<Node>(4),
                                    std::make_shared<Node>(5)),
                                std::make_shared<Node> (3));
    std::cout<<SumRootLeaf(root1)<<"\n";

    // test case 2:
    std::shared_ptr<Node> root2 = std::make_shared<Node>(1, 
                                std::make_shared<Node>(3,
                                    std::make_shared<Node>(7),
                                    std::make_shared<Node>(5)),
                                std::make_shared<Node> (3));
    std::cout<<SumRootLeaf(root2)<<"\n";

    // test case 3:
    std::shared_ptr<Node> root3 = std::make_shared<Node>(1, 
                                std::make_shared<Node>(3),
                                std::make_shared<Node> (3));
    std::cout<<SumRootLeaf(root3)<<"\n";

    // test case 4:
    std::shared_ptr<Node> root4 = std::make_shared<Node>(1, 
                                std::make_shared<Node>(3,
                                    std::make_shared<Node>(5)),
                                std::make_shared<Node> (3));
    std::cout<<SumRootLeaf(root4)<<"\n";

    // test case 5:
    std::shared_ptr<Node> root5 = nullptr;
    std::cout<<SumRootLeaf(root5)<<"\n";

    // test case 6:
    std::shared_ptr<Node> root6 = std::make_shared<Node>(1, std::make_shared<Node>(2, nullptr, std::make_shared<Node>(3)));
    std::cout<<SumRootLeaf(root6)<<"\n";

    // test case 7:
    std::shared_ptr<Node> root7 = std::make_shared<Node>(1, std::make_shared<Node>(0, nullptr, std::make_shared<Node>(0)));
    std::cout<<SumRootLeaf(root7)<<"\n";

    // test case 8:
    std::shared_ptr<Node> root8 = std::make_shared<Node>(1, std::make_shared<Node>(0), std::make_shared<Node>(1));
    std::cout<<SumRootLeaf(root8)<<"\n";

    return 0;
}