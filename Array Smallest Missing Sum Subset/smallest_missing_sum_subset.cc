#include <iostream>
#include <vector>
#include <queue>

using pqui64= std::priority_queue<uint64_t, std::vector<uint64_t>, std::greater<uint64_t>>;

void SmallestMissingNumberHelper(const std::vector<uint32_t> &input, pqui64 &min_heap, const uint64_t last_index, const uint64_t start_index = 0, const uint64_t previous_sum = 0)
{
    uint64_t sum = 0;
    for(auto index = start_index; index<last_index; index++)
    {
        sum = input[index] + previous_sum;
        min_heap.emplace(sum);
        SmallestMissingNumberHelper(input, min_heap, last_index, index+1, sum);
    }
}

uint64_t SmallestMissingNumber(const std::vector<uint32_t> &input)
{
    uint64_t ret = 1;
    if(input.empty()) return ret;

    pqui64 min_heap;
    SmallestMissingNumberHelper(input, min_heap, input.size());

    uint64_t curr = 0, prev = 0;
    while(min_heap.size())
    {
        curr = min_heap.top();
        if(curr != prev) // we have to be aware that min_heap can have redundant values
        {
            if(ret != curr) break; // only for unique values increment ret 
            ret++;
        }
        min_heap.pop();
        prev = curr;
    }

    return ret;
}

int main()
{
    // test case 1:
    std::vector<uint32_t> vec1 = {1, 2, 3, 8, 9, 10};
    std::cout<<SmallestMissingNumber(vec1)<<"\n";

    // test case 2:
    std::vector<uint32_t> vec2 = {};
    std::cout<<SmallestMissingNumber(vec2)<<"\n";

    // test case 3:
    std::vector<uint32_t> vec3 = {1};
    std::cout<<SmallestMissingNumber(vec3)<<"\n";

    // test case 4:
    std::vector<uint32_t> vec4 = {1, 2};
    std::cout<<SmallestMissingNumber(vec4)<<"\n";

    return 0;
}