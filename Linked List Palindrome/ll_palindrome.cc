#include <iostream>
#include <queue>

struct Node
{
    char data;
    std::shared_ptr<Node> next;
    Node(char data, std::shared_ptr<Node> next=nullptr)
    : data(data),
    next(next) {}
};

bool CheckPalindromeLL(std::shared_ptr<Node> list, std::queue<char> &cqueue)
{
    bool ret = false;
    if(!list) return true; // empty list is assumed to be palindromic

    cqueue.emplace(list->data);
    ret = CheckPalindromeLL(list->next, cqueue);
    if(!ret) return ret;

    ret = cqueue.front() == list->data;
    cqueue.pop();

    return ret;
}

int main()
{
    // test case 1:
    std::queue<char> cqueue1;
    auto head1 = std::make_shared<Node>('a', std::make_shared<Node>('b', std::make_shared<Node>('a')));
    std::cout<<CheckPalindromeLL(head1, cqueue1)<<"\n";

    // test case 2:
    std::queue<char> cqueue2;
    auto head2 = std::make_shared<Node>('a', std::make_shared<Node>('b', std::make_shared<Node>('a',std::make_shared<Node>('a', std::make_shared<Node>('b', std::make_shared<Node>('a'))))));
    std::cout<<CheckPalindromeLL(head2, cqueue2)<<"\n";

    // test case 3:
    std::queue<char> cqueue3;
    auto head3 = std::make_shared<Node>('a');
    std::cout<<CheckPalindromeLL(head3, cqueue3)<<"\n";

    // test case 4:
    std::queue<char> cqueue4;
    auto head4 = std::make_shared<Node>('a', std::make_shared<Node>('a'));
    std::cout<<CheckPalindromeLL(head4, cqueue4)<<"\n";

    // test case 5:
    std::queue<char> cqueue5;
    auto head5 = nullptr;
    std::cout<<CheckPalindromeLL(head5, cqueue5)<<"\n";

    // test case 6:
    std::queue<char> cqueue6;
    auto head6 = std::make_shared<Node>('a', std::make_shared<Node>('b'));
    std::cout<<CheckPalindromeLL(head6, cqueue6)<<"\n";

    // test case 7:
    std::queue<char> cqueue7;
    auto head7 = std::make_shared<Node>('a', std::make_shared<Node>('b', std::make_shared<Node>('c')));
    std::cout<<CheckPalindromeLL(head7, cqueue7)<<"\n";

    return 0;
}