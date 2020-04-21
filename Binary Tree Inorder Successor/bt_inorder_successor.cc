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

void InorderSuccessor(std::shared_ptr<Node> node, std::stack<int> &stack)
{
    if(!node) return;

    InorderSuccessor(node->left, stack);
    stack.emplace(node->data);
    InorderSuccessor(node->right, stack);
}

int InorderFinder(std::shared_ptr<Node> node, const int input)
{
    int ret = -1;
    std::stack<int> stack;
    InorderSuccessor(node, stack);

    bool b_found = false;
    while(stack.size())
    {
        auto val = stack.top();
        if(input == val) {b_found=true; break;}
        ret = stack.top();
        stack.pop();
    }

    if(!b_found) ret = -1;

    return ret;
}

int main()
{
    // test case 1:
    auto head1 = std::make_shared<Node>(3,
                        std::make_shared<Node>(2,
                            std::make_shared<Node>(1)),
                        std::make_shared<Node>(4,
                            nullptr,
                            std::make_shared<Node>(5)));
    std::cout<<InorderFinder(head1, 2)<<"\n";


    // test case 2:
    auto head2 = std::make_shared<Node>(10,
                        std::make_shared<Node>(5,
                            std::make_shared<Node>(1),
                            std::make_shared<Node>(7,
                                   std::make_shared<Node>(6),
                                   std::make_shared<Node>(8))),
                        std::make_shared<Node>(15,
                            std::make_shared<Node>(13),
                            std::make_shared<Node>(18)));
    std::cout<<InorderFinder(head2, 15)<<"\n";
    
    // test case 3:
    auto head3 = std::make_shared<Node>(10,
                        std::make_shared<Node>(5,
                            std::make_shared<Node>(1),
                            std::make_shared<Node>(7,
                                   std::make_shared<Node>(6),
                                   std::make_shared<Node>(8))),
                        std::make_shared<Node>(15,
                            std::make_shared<Node>(13),
                            std::make_shared<Node>(18)));
    std::cout<<InorderFinder(head3, 18)<<"\n";
    
    // test case 4:
    auto head4 = std::make_shared<Node>(10,
                        std::make_shared<Node>(5,
                            std::make_shared<Node>(1),
                            std::make_shared<Node>(7,
                                   std::make_shared<Node>(6),
                                   std::make_shared<Node>(8))),
                        std::make_shared<Node>(15,
                            std::make_shared<Node>(13),
                            std::make_shared<Node>(18)));
    std::cout<<InorderFinder(head4, 8)<<"\n";

    return 0;
}