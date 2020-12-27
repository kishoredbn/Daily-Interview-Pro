#include <iostream>
#include <queue>

struct Node { // represents ll
    std::shared_ptr<Node> next;
    uint32_t data;
    Node(uint32_t data, std::shared_ptr<Node> next=nullptr) :
    data(data),
    next(next) {}
};

struct PNode { // stores ll in priority queue in ascending order of head value
    std::shared_ptr<Node> node;
    PNode(std::shared_ptr<Node> node) : node(node) {}
    bool operator<(const PNode &other) const {
        return node->data > other.node->data;
    }
};

std::shared_ptr<Node> MergeSortList(std::shared_ptr<Node> ll_1, std::shared_ptr<Node> ll_2)
{
    std::shared_ptr<Node> ret_ll = nullptr;
    std::priority_queue<PNode> pq;

    // store heads of the 2 ll in the priority queue
    pq.emplace(ll_1);
    pq.emplace(ll_2);

    std::shared_ptr<Node> temp = nullptr;
    while(pq.size()) // keep poping head, store to return ll, and insert next to head in pq
    {
        auto top = pq.top(); pq.pop();
        auto next = top.node->next;
        if(next) pq.emplace(next);

        if(ret_ll) {
            temp->next = top.node;
            temp = temp->next;
        }
        else {
            ret_ll = top.node;
            temp = ret_ll;
        }
        temp ->next = nullptr;
    }

    return ret_ll;
}

void Display(std::shared_ptr<Node> node) // display header to print list
{
    while(node)
    {
        std::cout<<node->data<<" --> ";
        node = node->next;
    }
    std::cout<<"nullptr\n";
}

int main() {

    // test case 1:
    auto head1_1 = std::make_shared<Node>(1, std::make_shared<Node>(3, std::make_shared<Node>(5)));
    auto head1_2 = std::make_shared<Node>(2, std::make_shared<Node>(4, std::make_shared<Node>(6)));
    Display(MergeSortList(head1_1, head1_2));
    

    // test case 2:
    auto head2_1 = std::make_shared<Node>(8);
    auto head2_2 = std::make_shared<Node>(2, std::make_shared<Node>(4, std::make_shared<Node>(10)));
    Display(MergeSortList(head2_1, head2_2));

    return 0;
}