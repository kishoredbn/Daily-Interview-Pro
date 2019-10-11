#include <iostream>

struct Node
{
    int data;
    Node *left, *right;
    Node(int data): data(data), left(nullptr), right(nullptr) {}
};

int g_common_ans = -1;

bool lowest_common_anctr(Node *root, int a, int b)
{

    if(!root) return false;

    if (root->data == a || root->data == b)
    {
        return true;
    }

    bool leftCheck = lowest_common_anctr(root->left, a, b);
    bool rightCheck = lowest_common_anctr(root->right, a, b);

    if(leftCheck && rightCheck)
    {
        g_common_ans = root->data;
    }

    return leftCheck || rightCheck;
}

int main()
{
    Node *root = new Node(1);

    root->left = new Node(2);
    root->right = new Node(3);

    root->left->left = new Node(4);
    root->right->left = new Node(5);
    root->left->right = new Node(6);
    root->right->right = new Node(7);

    root->left->left->left = new Node(8);
    root->right->left->left = new Node(9);
    root->left->right->left = new Node(10);
    root->right->right->left = new Node(11);
    root->left->left->right = new Node(12);
    root->right->left->right = new Node(13);
    root->left->right->right = new Node(14);
    root->right->right->right = new Node(15);

    int a = 11, b = 15;
    lowest_common_anctr(root, a, b);
    std::cout<<"lowest common ancestor: "<<g_common_ans<<"\n";

    return 0;

}