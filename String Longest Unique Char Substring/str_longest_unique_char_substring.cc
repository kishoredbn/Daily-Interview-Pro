#include <iostream>
#include <unordered_map>

uint64_t LongestUniqueSubstring(const std::string &input) // assuming input always english small letters
{
    uint64_t ret = 0;
    if(input.empty()) return ret;

    uint64_t index = 0, counter = 0, first = 0, last = 0;
    std::unordered_map<char, uint64_t> index_map;
    for (const char &iter : input)
    {
        last++;
        auto find_index_map = index_map.find(iter);
        if(find_index_map != index_map.end() && first <= find_index_map->second)
        {
            first = find_index_map->second + 1;
        }
        
        index_map[iter] = last - 1;
        counter = last - first;
        if(counter > ret) ret = counter;
    }

    return ret;
}

int main()
{
    // test case 1:
    std::string input1 = "abrkaabcdefghijjxxx";
    std::cout<<LongestUniqueSubstring(input1)<<"\n";

    // test case 2:
    std::string input2 = "aa";
    std::cout<<LongestUniqueSubstring(input2)<<"\n";

    // test case 3:
    std::string input3 = "aaa";
    std::cout<<LongestUniqueSubstring(input3)<<"\n";

    // test case 4:
    std::string input4 = "aaaa";
    std::cout<<LongestUniqueSubstring(input4)<<"\n";

    // test case 5:
    std::string input5 = "aaba";
    std::cout<<LongestUniqueSubstring(input5)<<"\n";

    // test case 6:
    std::string input6 = "aabca";
    std::cout<<LongestUniqueSubstring(input6)<<"\n";

    return 0;
}