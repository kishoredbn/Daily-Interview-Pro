#include <iostream>
#include <vector>
#include <queue>

using vi32 = std::vector<int32_t>;
using pqi32 = std::priority_queue<int32_t, vi32, std::greater<int32_t>>;

int32_t LongestSubSeq(const vi32 &input)
{
    int32_t ret = 0;
    if(input.empty()) return ret;

    pqi32 min_heap;
    for (auto &iter : input) min_heap.emplace(iter); // caution: this is not linear time
    
    int32_t count = 0, prev = 0;
    while (min_heap.size())
    {
        auto curr = min_heap.top(); min_heap.pop();
        if(curr - 1 == prev ) {
            count++;
            if(count > ret) ret = count;
        }
        else 
        {
            count=1;
        }
        prev = curr;
    }
    return ret;
}

int main()
{
    // test case 1:
    vi32 input1 = {100, 4, 200, 1, 3, 2};
    std::cout<<LongestSubSeq(input1)<<"\n";

    // test case 2:
    vi32 input2 = {6, 4, 5, 1, 3, 2};
    std::cout<<LongestSubSeq(input2)<<"\n";

    // test case 3:
    vi32 input3 = {1,3,2};
    std::cout<<LongestSubSeq(input3)<<"\n";

    // test case 4:
    vi32 input4 = {1,3,2,5};
    std::cout<<LongestSubSeq(input4)<<"\n";

    return 0;
}