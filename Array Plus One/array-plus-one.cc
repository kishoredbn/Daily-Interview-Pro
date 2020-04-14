#include <iostream>
#include <vector>

std::vector<int> plus_one(std::vector<int> &input)
{
    std::vector<int> rec;
    int plus_1 = 1;
    for_each(input.rbegin(), input.rend(), [&](int x){rec.emplace(rec.begin(), (plus_1 += x)%10); plus_1 /= 10;});
    if(plus_1) rec.emplace(rec.begin(), plus_1);
    return rec;
}

int main()
{
    std::vector<int> input{9, 9, 9};
    std::vector<int> output = plus_one(input);
    for (auto &&i : output) std::cout<<i<<" "; 
    std::cout<<"\n";
}