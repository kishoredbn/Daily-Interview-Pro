#include <iostream>

struct Node
{
    char data;
    std::shared_ptr<Node> next;
    Node(char data, std::shared_ptr<Node> next=nullptr)
    : data(data),
    next(next) {}
};

bool CheckPalindromeHelperLL(std::shared_ptr<Node> list, std::shared_ptr<Node> &rev_node)
{
    bool ret = false;
    if(!list) return true; // empty list is assumed to be palindromic

    ret = CheckPalindromeHelperLL(list->next, rev_node);
    if(ret && list->data == rev_node->data) ret = true; // we use function stack itself to check Palindrome
    else ret = false;

    rev_node = rev_node->next;

    return ret;
}

bool CheckPalindromeLL(std::shared_ptr<Node> list)
{
    bool ret = CheckPalindromeHelperLL(list, list);
    return ret;
}

int main()
{
    // test case 1:
    auto head1 = std::make_shared<Node>('a', std::make_shared<Node>('b', std::make_shared<Node>('a')));
    std::cout<<CheckPalindromeLL(head1)<<"\n";

    // test case 2:
    auto head2 = std::make_shared<Node>('a', std::make_shared<Node>('b', std::make_shared<Node>('a',std::make_shared<Node>('a', std::make_shared<Node>('b', std::make_shared<Node>('a'))))));
    std::cout<<CheckPalindromeLL(head2)<<"\n";

    // test case 3:
    auto head3 = std::make_shared<Node>('a');
    std::cout<<CheckPalindromeLL(head3)<<"\n";

    // test case 4:
    auto head4 = std::make_shared<Node>('a', std::make_shared<Node>('a'));
    std::cout<<CheckPalindromeLL(head4)<<"\n";

    // test case 5:
    auto head5 = nullptr;
    std::cout<<CheckPalindromeLL(head5)<<"\n";

    // test case 6:
    auto head6 = std::make_shared<Node>('a', std::make_shared<Node>('b'));
    std::cout<<CheckPalindromeLL(head6)<<"\n";

    // test case 7:
    auto head7 = std::make_shared<Node>('a', std::make_shared<Node>('b', std::make_shared<Node>('c')));
    std::cout<<CheckPalindromeLL(head7)<<"\n";

    return 0;
}
