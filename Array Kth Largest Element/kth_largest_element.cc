#include <iostream>
#include <vector>
#include <queue>

using vi32 = std::vector<int32_t>;
using pqi32 = std::priority_queue<int32_t, vi32, std::greater<int32_t>>;

int32_t KthLargest(const vi32 &input, const int32_t k)
{
    int32_t ret = 0;
    if(input.empty()) return ret;
    if(k > input.size()) return ret;
    if(!k) return ret;

    pqi32 min_heap;
    for(auto &iter : input) {
        min_heap.emplace(iter);
        if(min_heap.size() > k) min_heap.pop();
    }

    ret = min_heap.top(); 
    return ret;
}

int main()
{
    // test case 1:
    vi32 input1 = {3, 5, 2, 4, 6, 8};
    std::cout<<KthLargest(input1, 3)<<"\n";

    // test case 2:
    vi32 input2 = {1,2,3};
    std::cout<<KthLargest(input2, 3)<<"\n";

    // test case 3:
    vi32 input3 = {1,2,3, 4, 7, 5, 6, 8};
    std::cout<<KthLargest(input3, 3)<<"\n";

    return 0;
}