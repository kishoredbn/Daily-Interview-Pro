#include <iostream>
#include <vector>

template<typename T>
class Stack
{
private:
    struct Node {
        T max;
        std::shared_ptr<Node> next;
        Node(T max, std::shared_ptr<Node> next): max(max), next(next) {}
    };
    std::shared_ptr<Node> m_max_head;
    std::vector<T> m_container;
public:
    Stack() 
    : m_max_head(std::make_shared<Node>(T(0), nullptr)) {}

    T Pop() {
        T ret;
        if(!m_container.size()) return ret;

        ret = m_container.back();
        if (m_max_head->max == m_container.back()) m_max_head = m_max_head->next;
        m_container.pop_back();
        
        return ret;
    }
    void Push(T t) {
        m_container.emplace_back(t);
        if(m_max_head->max <= t) m_max_head = std::make_shared<Node>(t, m_max_head);
    }
    T Max() {
        return m_max_head->max;
    }
};

int main()
{
    // test case 1:
    Stack<int32_t> stack;
    stack.Push(1);
    stack.Push(2);
    stack.Push(3);
    stack.Push(2);
    std::cout<<stack.Max()<<"\n";
    stack.Pop();
    stack.Pop();
    std::cout<<stack.Max()<<"\n";

    // test case 2:
    Stack<int32_t> stack2;
    stack2.Push(4);
    stack2.Push(3);
    stack2.Push(3);
    stack2.Push(3);
    std::cout<<stack2.Max()<<"\n";
    stack2.Pop();
    stack2.Pop();
    std::cout<<stack2.Max()<<"\n";
    stack2.Pop();
    stack2.Pop();
    std::cout<<stack2.Max()<<"\n";

    // test case 3:
    Stack<char> stack3;
    stack3.Push('n');
    stack3.Push('a');
    stack3.Push('z');
    stack3.Push('m');
    std::cout<<stack3.Max()<<"\n";
    stack3.Pop();
    stack3.Pop();
    std::cout<<stack3.Max()<<"\n";
    stack3.Pop();
    stack3.Pop();
    std::cout<<stack3.Max()<<"\n";

    return 0;
}