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

struct NodeList
{
    std::shared_ptr<Node>  data;
    std::shared_ptr<NodeList> next;
    NodeList(std::shared_ptr<Node>  data, std::shared_ptr<NodeList> next=nullptr)
    : data(data),
    next(next) {}
};

std::shared_ptr<NodeList> ReachLevel(std::shared_ptr<Node> root, const uint32_t &given_level, uint32_t curr_level = 1)
{
    std::shared_ptr<NodeList> ret_level = nullptr;
    if(!root) return ret_level;

    if(given_level == curr_level) return std::make_shared<NodeList>(root);

    auto node_level_left = ReachLevel(root->left, given_level, curr_level+1);
    auto node_level_right = ReachLevel(root->right, given_level, curr_level+1);

    if(node_level_left)
    {
        ret_level = node_level_left;
        if(node_level_right)
        {
            auto temp = ret_level;
            while(temp->next) temp = temp->next;
            temp->next = node_level_right;
        }
    }
    else if(node_level_right)
    {
        ret_level = node_level_right;
    }

    return ret_level;
}

void Display(const std::shared_ptr<NodeList> head)
{
    std::shared_ptr<NodeList> temp = head;
    while(temp && temp->data)
    {
        std::cout<<temp->data->data<<" -> ";
        temp = temp->next;
    }
    std::cout<<"nullptr\n";
}

int main()
{
    // test case 1:
    auto root1 = std::make_shared<Node>(1, 
                    std::make_shared<Node>(2, 
                        std::make_shared<Node>(4), 
                        std::make_shared<Node>(5)), 
                    std::make_shared<Node>(3, 
                        std::make_shared<Node>(6),
                        std::make_shared<Node>(7)));
    auto nHead1 = ReachLevel(root1, 3);
    Display(nHead1);

    // test case 2:
    auto root2 = std::make_shared<Node>(9);
    auto nHead2 = ReachLevel(root2, 1);
    Display(nHead2);

    // test case 3:
    auto root3 = nullptr;
    auto nHead3 = ReachLevel(root3, 1);
    Display(nHead3);

    // test case 4:
    auto root4 = std::make_shared<Node>(10, 
                    nullptr,
                    std::make_shared<Node>(8, 
                        nullptr, 
                        std::make_shared<Node>(2)));
    auto nHead4 = ReachLevel(root4, 2);
    Display(nHead4);

    return 0;
}