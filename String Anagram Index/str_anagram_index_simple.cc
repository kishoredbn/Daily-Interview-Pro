#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

std::vector<uint32_t> FindAnagramIndex(std::string str, std::string txt)
{
    std::vector<uint32_t> ret;
    uint32_t index_size = txt.size();

    std::sort(txt.begin(), txt.end());
    for(auto index=0; index<str.size(); index++)
    {
        auto temp_str = str.substr(index, index_size);
        std::sort(temp_str.begin(), temp_str.end());
        if(temp_str.compare(txt) == 0)
        {
            ret.emplace_back(index);
        }
    }

    return ret;
}

int main()
{
    // test case 1
    std::string str1 {"acdbacdacb"};
    std::string txt1 {"abc"};
    auto out1 = FindAnagramIndex(str1, txt1);
    for(auto index : out1) std::cout<<index<<","; 
    std::cout<<"\n";

    // test case 2
    std::string str2 {"acdbacdacbacbdaceb"};
    std::string txt2 {"abc"};
    auto out2 = FindAnagramIndex(str2, txt2);
    for(auto index : out2) std::cout<<index<<","; 
    std::cout<<"\n";

    return 0;
}