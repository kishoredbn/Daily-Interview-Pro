#include <iostream>
#include <vector>
#include<limits>

struct Node
{
    int data;
    Node *left, *right;
    Node(int data): data(data), left(nullptr), right(nullptr){}
};

void traverse(Node *root, std::vector<int> &vec, uint32_t level)
{
    if(!root) return;

    if (vec.size() <= level)
    {
        vec.emplace_back(root->data);
    }
    else
    {
        vec[level] += root->data;
    }

    traverse(root->left, vec, level+1);
    traverse(root->right, vec, level+1);

}

int min_sum(Node *root)
{
    if(!root) return 0;

    std::vector<int> vec;
    traverse(root, vec, 0);

    int min = std::numeric_limits<int>::max();
    for_each(vec.begin(), vec.end(), [&](int i) mutable { if(min>i) min=i;});

    return min;
}

int main()
{
    Node *root = new Node(2);

    root->left = new Node(2);
    root->right = new Node(3);

    root->left->left = new Node(2);
    root->right->left = new Node(3);
    root->left->right = new Node(2);
    root->right->right = new Node(3);

    root->left->left->left = new Node(2);
    root->right->left->left = new Node(3);
    root->left->right->left = new Node(2);
    root->right->right->left = new Node(3);
    root->left->left->right = new Node(2);
    root->right->left->right = new Node(-3);
    root->left->right->right = new Node(-2);
    root->right->right->right = new Node(3);

    std::cout<<"Min sum: "<<min_sum(root)<<"\n";
    return 0;
}