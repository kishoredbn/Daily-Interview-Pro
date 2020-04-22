#include <iostream>
#include <vector>
#include <unordered_map>

using vstr = std::vector<std::string>;
using vvstr = std::vector<std::vector<std::string>>;
using umi32vi64 = std::unordered_map<uint32_t, std::vector<uint64_t>>;

uint32_t GetWordCode(std::string word) // crux: every anagrams flips bits and generate same code
{
    uint32_t ret = 0;
    if(word.empty()) return ret;

    for (auto &iter : word)
    {
        if(iter >= 'A' && iter <= 'Z') iter = iter - 'A';
        ret = ret | (1 << ((uint32_t)iter));
    }
    return ret;
}

vvstr GetWordsGrouped(const vstr &input)
{
    vvstr ret{0};
    if(input.empty()) return ret;

    umi32vi64 word_map_code;
    uint64_t index = 0;
    for (const auto &iter : input)
    {
        auto code = GetWordCode(iter);
        word_map_code[code].emplace_back(index++); // store index and not strings to save memory
    }

    vstr temp;
    for (const auto &iter_v : word_map_code)
    {
        temp.clear();
        for (const auto &iter : iter_v.second)
        {
            temp.emplace_back(input[iter]);
        }
        ret.emplace_back(temp);
    }

    return ret;
}

void Display(const vvstr& input)
{
    std::cout<<"{";
    for(const auto &iter_v : input)
    {
        std::cout<<"{ ";
        for (const auto &iter : iter_v) std::cout<<iter<<", ";
        std::cout<<"},";
    }
    std::cout<<"}\n";
}

int main()
{
    // test case 1:
    vstr vec1 = {"abc", "bcd", "cba", "cbd", "efg"};
    auto group1 = GetWordsGrouped(vec1);
    Display(group1);

    return 0;
}