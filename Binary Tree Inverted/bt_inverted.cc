#include <iostream>

struct Node
{
    char32_t data;
    std::shared_ptr<Node> left, right;
    Node(char32_t data, std::shared_ptr<Node> left=nullptr, std::shared_ptr<Node> right=nullptr)
    : data(data),
    left(left),
    right(right) {}
};

void InvertBt(std::shared_ptr<Node> *node)
{
    if(!node || !*node) return;

    auto temp = (*node)->left;
    (*node)->left = (*node)->right;
    (*node)->right = temp;

    InvertBt(&((*node)->left));
    InvertBt(&((*node)->right));
}

void Display(const std::shared_ptr<Node> node)
{
    if(!node) return;
    std::cout<<static_cast<char>(node->data)<<" ";
    Display(node->left);
    Display(node->right);
}

int main()
{
    // test case 1:
    std::shared_ptr<Node> head1 = std::make_shared<Node>('a',
                                        std::make_shared<Node>('b',
                                                std::make_shared<Node>('d'),
                                                std::make_shared<Node>('e')),
                                        std::make_shared<Node>('c',
                                                std::make_shared<Node>('f')));
    Display(head1); std::cout<<"\n";
    InvertBt(&head1);
    Display(head1); std::cout<<"\n";

    // test case 2:
    std::shared_ptr<Node> head2 = nullptr;
    Display(head2); std::cout<<"\n";
    InvertBt(&head2);

    // test case 3:
    std::shared_ptr<Node> head3 = std::make_shared<Node>('a',
                                        std::make_shared<Node>('b',
                                                std::make_shared<Node>('d')));
    Display(head3); std::cout<<"\n";
    InvertBt(&head3);

    return 0;
}