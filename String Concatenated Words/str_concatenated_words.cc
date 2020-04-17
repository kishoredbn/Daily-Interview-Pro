#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using vs = std::vector<std::string>;
using ums = std::unordered_set<std::string>;

struct cstring
{
    std::string data;
    bool operator<(const cstring &other) const
    {
        return data.size() > other.data.size();
    }
    cstring(std::string data) : data(data) {}
};

bool CheckWordConcate(std::string str, const ums &word_map) // Check parts of word in dictonary
{
    bool ret = false;
    if(word_map.empty()) return ret;

    uint32_t start_index = 0, chr_count = 1;
    auto word_size = str.size();

    while(chr_count < word_size) // break each words into subwords
    {
        auto sub_str_1 = str.substr(start_index, chr_count); 
        if(word_map.find(sub_str_1) != word_map.end()) // if first subword is part of dict...
        {
            auto sub_str_2 = str.substr(start_index + chr_count);
            if(word_map.find(sub_str_2) != word_map.end() || CheckWordConcate(sub_str_2, word_map)) // ...and 2nd subword part of dictonary or further divide
            {
                ret = true; break; // return true
            }
        }
        chr_count++; // keep checking for more possible combinations of first word
    }

    return ret;
}

vs FindAllConcatenatedWordsInDict(const vs &input) // find concatenated words
{
    vs ret;
    if(input.empty()) return ret;

    // step 1: put all words to priorit queue to partially sort by length
    std::priority_queue<cstring> pqueue;
    for(const auto &iter : input) pqueue.emplace(iter);

    ums word_map;
    while(pqueue.size()) // get smaller words first followed by larger words
    {
        auto str = pqueue.top(); pqueue.pop();
        if(CheckWordConcate(str.data, word_map)) // if parts of current word is in dictonary then make an entry to return vector
            ret.emplace_back(str.data);
        else // else - make that part of dictonary 
            word_map.emplace(str.data);
    }

    return ret;
}

void Display(const vs &input)
{
    for(auto &iter : input) std::cout<<iter<<", ";
    std::cout<<"\n";
}

int main()
{
    // test case 1:
    vs str1{"tech", "lead", "techlead", "cat", "cats", "dog", "catsdog"};
    vs ans1 = FindAllConcatenatedWordsInDict(str1);
    Display(ans1);

    // test case 2:
    vs str2{"tech", "lead", "techlead", "cat", "cats", "dog", "dogs", "catsdog", "catsdogs"};
    vs ans2 = FindAllConcatenatedWordsInDict(str2);
    Display(ans2);

    // test case 3:
    vs str3{"cat", "catcat", "catcatcat", "cat", "cats"};
    vs ans3 = FindAllConcatenatedWordsInDict(str3);
    Display(ans3);

    return 0;
}