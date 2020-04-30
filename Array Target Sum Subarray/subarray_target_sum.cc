#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>

using vui64 = std::vector<uint64_t>;
using umui64ui64 = std::unordered_map<uint64_t, uint64_t>;

vui64 GetSubarraySum(const vui64 &input, uint64_t val)
{
    vui64 ret;
    if(input.empty()) return ret;

    uint64_t counter = 0, next_value = 0;
    umui64ui64 circular_map;
    std::stack<uint64_t> track_entry;
    bool bFound = false;
    for (auto &iter : input) // O(N) where N is input vector size
    {
        next_value = iter;
        circular_map[counter] = next_value;
        track_entry.emplace(counter);
        counter = (counter + next_value) % val;
        if(circular_map.find(counter) != circular_map.end()) {bFound = true; break;}
    }

    while(bFound) // bounded by O(N), where N is input vector size
    {
        next_value = track_entry.top(); track_entry.pop();
        ret.emplace(ret.begin(), circular_map[next_value]);
        if(counter != next_value) continue;
        break;
    }

    return ret;
}

void Display(const vui64 &input)
{
    for (auto &iter : input) std::cout<<iter<<", "; std::cout<<"\n";
}

int main()
{
    // test case 1:
    vui64 vec1 = {1, 3, 2, 5, 7, 2};
    auto out1 = GetSubarraySum(vec1, 14);
    Display(out1);

    // test case 2:
    vui64 vec2 = {5, 5, 7, 3, 1, 2, 3};
    auto out2 = GetSubarraySum(vec2, 13);
    Display(out2);

    // test case 3:
    vui64 vec3 = {5, 7, 13, 14, 12, 3, 11, 10, 9};
    auto out3 = GetSubarraySum(vec3, 15);
    Display(out3);

    // test case 4:
    vui64 vec4 = {5, 7, 13, 14, 12, 3, 11, 10, 9};
    auto out4 = GetSubarraySum(vec4, 25);
    Display(out4);

    // test case 5:
    vui64 vec5 = {5, 15, 10};
    auto out5 = GetSubarraySum(vec5, 20);
    Display(out5);

    return 0;
}