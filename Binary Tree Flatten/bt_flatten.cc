#include <iostream>

struct Node
{
    int data;
    std::shared_ptr<Node> left, right;
    Node(int data, std::shared_ptr<Node> left=nullptr, std::shared_ptr<Node> right=nullptr)
    : data(data),
    left(left),
    right(right) {}
};

std::shared_ptr<Node> BtFlattenHelper(std::shared_ptr<Node> node, std::shared_ptr<Node>* last_node)
{
    if(!node) return nullptr;

    if(node->left) {
        auto node_child = BtFlattenHelper(node->left, last_node);
        if(last_node && *last_node)
        {
            (*last_node)->right = node->right;
        }
        node->right = node_child;
        node->left = nullptr; // most people will forget this
    }
    *last_node = nullptr;
    BtFlattenHelper(node->right, last_node);
    (*last_node) = node;

    if(node->right)
    {
        while((*last_node)->right) (*last_node) = (*last_node)->right;
    }

    return node;
}

void BtFlatten(std::shared_ptr<Node>* node)
{
    std::shared_ptr<Node> last_node = nullptr;
    BtFlattenHelper(*node, &last_node);
}

void Display(std::shared_ptr<Node> node)
{
    if(!node) { std::cout<<"nullptr"; return;}
    std::cout<<"("<<node->data<<", left: ";
    Display(node->left);
    std::cout<<", right: ";
    Display(node->right);
    std::cout<<") ";
}

int main()
{
    // test case 1:
    std::shared_ptr<Node> head1 = nullptr;
    BtFlatten(&head1);
    Display(head1); std::cout<<std::endl;

    // test case 2:
    std::shared_ptr<Node> head2 = std::make_shared<Node>(1, 
                                        std::make_shared<Node>(2,
                                                std::make_shared<Node>(3)),
                                        std::make_shared<Node>(4,
                                                std::make_shared<Node>(5)));
    BtFlatten(&head2);
    Display(head2); std::cout<<std::endl;

    // test case 3:
    std::shared_ptr<Node> head3 = std::make_shared<Node>(1, 
                                        std::make_shared<Node>(2,
                                                std::make_shared<Node>(3,
                                                    std::make_shared<Node>(4,
                                                        std::make_shared<Node>(5)))));
    BtFlatten(&head3);
    Display(head3); std::cout<<std::endl;

    // test case 4:
    std::shared_ptr<Node> head4 = std::make_shared<Node>(1,
                                        nullptr, 
                                        std::make_shared<Node>(2,
                                                std::make_shared<Node>(3,
                                                    std::make_shared<Node>(4,
                                                        std::make_shared<Node>(5)))));
    BtFlatten(&head4);
    Display(head4); std::cout<<std::endl;

    // test case 5:
    std::shared_ptr<Node> head5 = std::make_shared<Node>(1,
                                        nullptr, 
                                        std::make_shared<Node>(2,
                                                nullptr,
                                                std::make_shared<Node>(3,
                                                    std::make_shared<Node>(4,
                                                        std::make_shared<Node>(5)))));
    BtFlatten(&head5);
    Display(head5); std::cout<<std::endl;

    return 0;
}