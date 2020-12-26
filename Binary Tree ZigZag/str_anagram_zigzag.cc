#include <iostream>
#include <vector>
#include <queue>

struct Node
{
    int data;
    std::shared_ptr<Node> left, right;
    Node(int data, std::shared_ptr<Node> left=nullptr, std::shared_ptr<Node> right=nullptr)
    : data(data),
    left(left),
    right(right) {}
};

using vi = std::vector<uint32_t>;
using vvi = std::vector<vi>;
using qnode = std::queue<std::shared_ptr<Node>>;

vvi GetTreeLayers(std::shared_ptr<Node> node) {
    vvi bfs_storage;

    uint32_t current_layer_nodes = 1, next_layer_nodes = 0;

    //bfs - storage all node in a layer to a vector
    // store each vector to bfs_storage vector of vector
    // display result in zigzag based on flipper value
    qnode bfs_traverse_que;
    vi tree_layer;
    bfs_traverse_que.emplace(node);
    while(bfs_traverse_que.size())
    {
        auto curr_node = bfs_traverse_que.front();
        tree_layer.emplace_back(curr_node->data);
        bfs_traverse_que.pop();

        if(curr_node->left) {
            next_layer_nodes++;
            bfs_traverse_que.emplace(curr_node->left);
        }
        if(curr_node->right) {
            next_layer_nodes++;
            bfs_traverse_que.emplace(curr_node->right);
        }

        current_layer_nodes--;
        if(!current_layer_nodes) { // now that we have come to the end of a layer
            current_layer_nodes = next_layer_nodes;
            next_layer_nodes = 0;
            bfs_storage.emplace_back(tree_layer); // set the vector
            tree_layer = vi(); // and clear it for the next layer
        }

    }

    return bfs_storage;
}

void DisplayNodeZigZag(std::shared_ptr<Node> node)
{
    if(!node) return;

    vvi bfs_storage = GetTreeLayers(node);
    bool flipper = true;

    for(auto &v_iter : bfs_storage)
    {
        if(flipper)
        {
            for(auto &iter : v_iter)
                std::cout<<iter<<", ";
        }
        else
        {
            for(auto iter=v_iter.rbegin(); iter!=v_iter.rend(); iter++ )
                std::cout<<*iter<<", ";
        }
        flipper = !flipper;
    }
    std::cout<<"\n";
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
    DisplayNodeZigZag(root1);
    
    // test case 2:
    auto root2 = std::make_shared<Node>(1);
    DisplayNodeZigZag(root2);
    
    // test case 3:
    auto root3 = std::make_shared<Node>(1,
                     std::make_shared<Node>(2,
                         std::make_shared<Node>(4,
                            std::make_shared<Node>(8),
                            std::make_shared<Node>(9)),
                         std::make_shared<Node>(5,
                            std::make_shared<Node>(10),
                            std::make_shared<Node>(11))),
                     std::make_shared<Node>(3,
                         std::make_shared<Node>(6,
                            std::make_shared<Node>(12),
                            std::make_shared<Node>(13)),
                         std::make_shared<Node>(7,
                           std::make_shared<Node>(14),
                           std::make_shared<Node>(15))));
    DisplayNodeZigZag(root3);
    
    //test case 4:
    std::shared_ptr<Node> root4=nullptr;
    DisplayNodeZigZag(root4);

    return 0;
}
