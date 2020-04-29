#include <iostream>
#include <vector>

uint64_t CountSteps(uint64_t step, std::vector<uint64_t> &memo)
{
    uint64_t ret = 0;
    if(!step) return ret;

    while(step > memo.size()) memo.emplace_back( memo[memo.size() - 1] +  memo[memo.size() - 2] );
    ret = memo[step-1];

    return ret;
}

int main()
{
    std::vector<uint64_t> memo = {1, 2};

    // test case 1:
    std::cout<<CountSteps(4, memo)<<"\n";

    // test case 2:
    std::cout<<CountSteps(5, memo)<<"\n";

    return 0;
}