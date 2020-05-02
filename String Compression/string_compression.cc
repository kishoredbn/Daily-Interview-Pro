#include <iostream>

std::string StringCompression(const std::string &input)
{
    std::string ret = "";
    if(input.empty()) return ret;

    char32_t prev = '0';
    uint64_t count = 1;
    for(auto &iter : input)
    {
        if(prev != iter) {
            if(count != 1) ret += std::to_string(count);
            count = 1;
        }
        else count++;

        if(count == 1) ret += iter;
        prev = iter;
    }

    if(count != 1) ret += std::to_string(count);

    return ret;
}

int main()
{
    // test case 1:
    std::string input1 = "aabccc";
    std::cout<<StringCompression(input1)<<"\n";

    // test case 2:
    std::string input2 = "abcdef";
    std::cout<<StringCompression(input2)<<"\n";

    // test case 3:
    std::string input3 = "aaaaaaaaaaaaaaaaa";
    std::cout<<StringCompression(input3)<<"\n";

    // test case 4:
    std::string input4 = "a";
    std::cout<<StringCompression(input4)<<"\n";

    return 0;
}