#include <iostream>
#include <unordered_map>

uint64_t ConvertRomanDecimal(const std::string &input)
{
    static const std::unordered_map<char, uint32_t> char_map {{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}};
    
    uint64_t ret = 0;
    if(input.empty()) return ret;

    uint64_t prev = 0;
    for(auto &iter : input)
    {
        auto find = char_map.find(iter);
        if(find != char_map.end())
        {
            if(prev < find->second) ret += find->second - (2 * prev);
            else ret += find->second;

            prev = find->second;
        }
    }

    return ret;
}

int main()
{
    std::cout<<ConvertRomanDecimal("MCMX")<<std::endl; // test case 1
    std::cout<<ConvertRomanDecimal("I")<<std::endl; // test case 2
    std::cout<<ConvertRomanDecimal("IV")<<std::endl; // test case 3
    std::cout<<ConvertRomanDecimal("V")<<std::endl; // test case 4
    std::cout<<ConvertRomanDecimal("IX")<<std::endl; // test case 5
    std::cout<<ConvertRomanDecimal("X")<<std::endl; // test case 6
    std::cout<<ConvertRomanDecimal("XI")<<std::endl; // test case 7
    std::cout<<ConvertRomanDecimal("XL")<<std::endl; // test case 8
    std::cout<<ConvertRomanDecimal("L")<<std::endl; // test case 9
    std::cout<<ConvertRomanDecimal("LX")<<std::endl; // test case 10
    std::cout<<ConvertRomanDecimal("LXI")<<std::endl; // test case 11
    std::cout<<ConvertRomanDecimal("LC")<<std::endl; // test case 12
    std::cout<<ConvertRomanDecimal("C")<<std::endl; // test case 13
    std::cout<<ConvertRomanDecimal("CL")<<std::endl; // test case 14
    std::cout<<ConvertRomanDecimal("CD")<<std::endl; // test case 15
    std::cout<<ConvertRomanDecimal("D")<<std::endl; // test case 16
    std::cout<<ConvertRomanDecimal("DC")<<std::endl; // test case 17
    std::cout<<ConvertRomanDecimal("DM")<<std::endl; // test case 18
    std::cout<<ConvertRomanDecimal("M")<<std::endl; // test case 19
    std::cout<<ConvertRomanDecimal("MD")<<std::endl; // test case 20
    std::cout<<ConvertRomanDecimal("MM")<<std::endl; // test case 21
    std::cout<<ConvertRomanDecimal("MMM")<<std::endl; // test case 22
    std::cout<<ConvertRomanDecimal("MMMM")<<std::endl; // test case 23
    std::cout<<ConvertRomanDecimal("XXXX")<<std::endl; // test case 24
    std::cout<<ConvertRomanDecimal("III")<<std::endl; // test case 25
    std::cout<<ConvertRomanDecimal("CCCC")<<std::endl; // test case 26

    return 0;
}