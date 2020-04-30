#include <iostream>
#include <memory>

struct Node {
    char32_t data;
    std::shared_ptr<Node> left, right;
    Node(char32_t data, std::shared_ptr<Node> left=nullptr, std::shared_ptr<Node> right=nullptr)
    : data(data), left(left), right(right) {}
};

int32_t PerformArthmeticOperation(std::shared_ptr<Node> node)
{
    int32_t ret = 0;
    if(!node) return ret;

    if(node->data >= '0' && node->data <= '9') return (node->data - '0'); 

    auto ret_l = PerformArthmeticOperation(node->left);
    auto ret_r = PerformArthmeticOperation(node->right);

    switch (node->data)
    {
    case '+':
        ret = ret_l + ret_r;
        break;
    case '-':
        ret = ret_l - ret_r;
        break;
    case '*':
        ret = ret_l * ret_r;
        break;
    case '/':
        if(ret_r) ret = ret_l * ret_r; // edge case: divide by 0
        else ret = ret_l;
        break;
    default: // not going to be invoked, provided inputs are correct
        ret = node->data; 
        break;
    }

    return ret;
}

int main()
{
    // test case 1:
    std::shared_ptr<Node> input1 = std::make_shared<Node>('*',
                                            std::make_shared<Node>('+',
                                                    std::make_shared<Node>(3),
                                                    std::make_shared<Node>(2)),
                                            std::make_shared<Node>('+',
                                                    std::make_shared<Node>(4),
                                                    std::make_shared<Node>(5)));
    std::cout<<PerformArthmeticOperation(input1)<<"\n";

    // test case 2:
    std::shared_ptr<Node> input2 = std::make_shared<Node>('*',
                                            std::make_shared<Node>(-10),
                                            std::make_shared<Node>('+',
                                                    std::make_shared<Node>(4),
                                                    std::make_shared<Node>(5)));
    std::cout<<PerformArthmeticOperation(input2)<<"\n";
    return 0;
}