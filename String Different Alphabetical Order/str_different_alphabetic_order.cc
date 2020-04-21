#include <iostream>
#include <vector>
#include <unordered_map>

using vstr = std::vector<std::string>;
using umc32i = std::unordered_map<char, uint32_t>;

bool CheckWordOrders(const std::string &input1, const std::string &input2, const umc32i &order_map)
{
    bool ret = false;

    auto size_1 = input1.size();
    auto size_2 = input2.size();
    uint32_t index = 0;
    while(index < size_1 && index < size_2)
    {
        auto curr_find_1 = order_map.find(input1[index]);
        auto curr_find_2 = order_map.find(input2[index]);

        if(curr_find_1 == order_map.end() || curr_find_2 == order_map.end()) return ret; // character not found in order map - exit with error
        if(curr_find_1->second > curr_find_2->second) return ret;
        if(curr_find_1->second < curr_find_2->second) return true;

        index++;
    }

    if(index >= size_1) ret = true; // if word 1 is shorter or equal to words 2 then words are in order

    return ret;
}

bool CheckDifferentOrder(const vstr words, const std::string order)
{
    bool ret = true;
    auto total_words = words.size();
    if(total_words < 2) return ret; // only one word is always ordered with no other to check

    //step 1: convert order from vector to map
    auto index= 0;
    umc32i order_map;
    for(auto iter : order) order_map.emplace(iter, index++);

    // step 2: check word order
    index = 1;
    std::string prev_word = words[0], curr_word = "";
    while(ret && index < total_words)
    {
        curr_word = words[index++];
        ret = CheckWordOrders(prev_word, curr_word, order_map); // check order between 2 words
        prev_word = curr_word;
    } 

    return ret;
}

int main()
{
    // test case 1:
    std::string order1 = "zyxwvutsrqponmlkjihgfedcba";
    vstr word1 = {"abcd", "efgh"};
    std::cout<<CheckDifferentOrder(word1, order1)<<"\n"; 

    // test case 2:
    std::string order2 = "zyxwvutsrqponmlkjihgfedcba";
    vstr word2 = {"zyx", "zyxw", "zyxwy"};
    std::cout<<CheckDifferentOrder(word2, order2)<<"\n"; 

    // test case 3:
    std::string order3 = "zyxwvutsrqponmlkjihgfedcba";
    vstr word3 = {"zyx", "zyx"};
    std::cout<<CheckDifferentOrder(word3, order3)<<"\n"; 

    // test case 4:
    std::string order4 = "zyxwvutsrqponmlkjihgfedcba";
    vstr word4 = {"zyx", "zyxx"};
    std::cout<<CheckDifferentOrder(word4, order4)<<"\n"; 

    // test case 5:
    std::string order5 = "zyxwvutsrqponmlkjihgfedcba";
    vstr word5 = {"zyxx", "zyx"};
    std::cout<<CheckDifferentOrder(word5, order5)<<"\n"; 

    return 0;
}