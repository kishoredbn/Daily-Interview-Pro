#include <iostream>
#include <stack>
#include <unordered_map>

uint64_t CountInvalidParenthesis(const std::string &input)
{
    uint64_t ret = 0;
    if(input.empty()) return ret;

    static const std::unordered_map<char, char> brace_complete_map {{'(', ')'}}; // map is an over-kill here for this problem
    std::stack<char> stack;
    for(auto &iter : input)
    {
        auto find = brace_complete_map.find(iter);
        if(find != brace_complete_map.end())
        {
            stack.emplace(find->second);
        }
        else if(stack.size() && (stack.top() == iter))
        {
            stack.pop();
        }
        else
        {
            ret++;
        }
    }

    while(stack.size()) {
        stack.pop();
        ret++;
    }

    return ret;
}

int main()
{
    std::cout<<CountInvalidParenthesis("()())()")<<"\n"; // test case 1
    std::cout<<CountInvalidParenthesis("((((((((((")<<"\n"; // test case 2
    std::cout<<CountInvalidParenthesis("))))))))))")<<"\n"; // test case 3
    std::cout<<CountInvalidParenthesis("")<<"\n"; // test case 4
    std::cout<<CountInvalidParenthesis("()")<<"\n"; // test case 5
    std::cout<<CountInvalidParenthesis("((()())())")<<"\n"; // test case 6
    std::cout<<CountInvalidParenthesis(")))((((())")<<"\n"; // test case 7
    std::cout<<CountInvalidParenthesis(")))))(())((()((((")<<"\n"; // test case 8
    std::cout<<CountInvalidParenthesis("))))())))((())))(((")<<"\n"; // test case 9
    std::cout<<CountInvalidParenthesis("))))(((")<<"\n"; // test case 10
    return 0;
}