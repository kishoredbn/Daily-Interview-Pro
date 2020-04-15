#include <iostream>
#include <memory>
#include <vector>
#include <stack>
#include <algorithm>

// BT structure
struct Node
{
    int data;
    std::shared_ptr<Node> left, right;
    Node(int data, std::shared_ptr<Node> left = nullptr, std::shared_ptr<Node>  right = nullptr)
    : data(data),
    left(left),
    right(right) {}
};

// generates the BT from pre-order traversal and  in-order traversal
std::shared_ptr<Node> GenerateTree(std::vector<int> &pre, std::vector<int> &in)
{
    std::shared_ptr<Node> root = nullptr;
    if(pre.empty() || in.empty()) return root; // validate inputs

    const uint32_t size_vc = pre.size(); // get either of the vector size.
    std::stack<std::shared_ptr<Node>> stkNode; // only intermediate data-structure to store nodes

    uint32_t intr_in = 0; // keeps track of index of in-order vector
    uint32_t intr_pre = 0; // keeps track of index of in-order vector

    bool bRight = false; // keep track of when to append to right child

    std::shared_ptr<Node> curr = nullptr; // intermediate storage

    // solution crux: pre-order vector drives the creation of BT
    // in-order vector is only used to refer to check when to add to right child.
    while(intr_pre < size_vc) // exit criteria : if in-order vector exhausted 
    {
        std::shared_ptr<Node> temp = std::make_shared<Node>(pre[intr_pre]); // create new node
        if(curr) // if not first node
        {
            if(bRight) // append child to right node
            {
                curr->right = temp; bRight = false; // flip flag
            }
            else
                curr->left = temp; // add to left child
        }
        else // if first node
        {
            root = temp; // keep track of root - this we will return - only reference point of the tree
        }
        curr = temp; // keeps track of where to append next child node
        stkNode.emplace(temp); // backtracks the node up towards root from leaf nodes
        intr_pre++; // increment index of pre-order vector

        while(intr_in < size_vc && stkNode.size() && stkNode.top()->data == in[intr_in]) // if currrent value of in-order vector equals pre-order vector
        {
            curr = stkNode.top(); // we need to go to top of stack - backtrack until condition fails
            stkNode.pop();
            intr_in++;
            bRight = true; // of course add to the right child
        }
        
    }

    return root;
}

void DisplayPostOrder(std::shared_ptr<Node> root)
{
    if(!root) return;
    DisplayPostOrder(root->left);
    DisplayPostOrder(root->right);
    std::cout<<root->data<<" ";
}

int main()
{
    // test case 1:
    std::vector<int> pre{3, 9, 10, 11, 14, 12, 7, 5, 15, 20, 13, 50},
                in{11, 10, 9, 12, 14, 7, 3, 15, 13, 20, 50, 5};
    auto root = GenerateTree(pre, in);
    DisplayPostOrder(root); std::cout<<"\n";
    
    // test case 2:
    std::vector<int> pre1{11, 10, 9, 12, 14, 7, 3, 15, 13, 20, 50, 5},
                in1{11, 10, 9, 12, 14, 7, 3, 15, 13, 20, 50, 5};
    root = GenerateTree(pre1, in1);
    DisplayPostOrder(root); std::cout<<"\n";
    
    return 0;
}
