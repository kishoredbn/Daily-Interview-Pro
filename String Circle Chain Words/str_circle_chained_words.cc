#include <iostream>
#include <vector>
#include <unordered_map>

using vs = std::vector<std::string>;
using ummcc = std::unordered_multimap<char, char>;

bool CheckCircle(const ummcc dict)
{
    bool ret = false;

    char fast = 0, slow = 0; 
    for(auto &iter : dict)
    {
        fast = slow = iter.first;
        while(dict.find(fast) != dict.end())
        {
            if(dict.find(fast) != dict.end()) fast = dict.find(fast)->second; else break;
            if(dict.find(fast) != dict.end()) fast = dict.find(fast)->second; else break;
            slow = dict.find(slow)->second;

            if(slow == fast) return true;
        }
    }

    return ret;
}

bool CheckCircleChain(const vs &vstr)
{
    bool ret = false;
    if(vstr.empty()) return ret;

    ummcc dict; // step 1: get the first and last character of all the words
    for (auto &iter : vstr)
    {
        if(iter.front() == iter.back()) return true; // any word in the list with first and last char same - makes circle
        dict.emplace(iter.front(), iter.back());
    }

    ret = CheckCircle(dict); // step 2: check if the dict has cycles in it

    return ret;
}

int main()
{
    // test case: 1
    vs vstr1 = {"apple", "eggs", "snack", "karat", "tuna"};
    std::cout<<CheckCircleChain(vstr1)<<"\n";

    // test case: 2
    vs vstr2 = {"auna"};
    std::cout<<CheckCircleChain(vstr2)<<"\n";

    // test case: 3
    vs vstr3 = {"apple", "eggs"};
    std::cout<<CheckCircleChain(vstr3)<<"\n";

    // test case: 4
    vs vstr4 = {"apple", "eggs", "snack", "karat"};
    std::cout<<CheckCircleChain(vstr4)<<"\n";

    return 0;
}