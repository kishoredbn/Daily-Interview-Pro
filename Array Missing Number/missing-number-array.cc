#include <iostream>
#include <vector>

std::vector<int> missing_num(std::vector<int> &input)
{
    std::vector<int> res;
    std::vector<bool> vec(input.size(), true);

    for (auto &iter : input)
    {
        vec[iter-1] = false;
    }

    int index = 0;
    for (auto iter : vec)
    {
        if(iter) res.emplace_back(index+1);
        index++;
    }

    return res;
}

int main()
{
    std::vector<int> input{4,5,2,6,8,2,1,5};
    std::vector<int>  ans = missing_num(input);

    std::cout<<"missing numbers: ";
    for (auto &i : ans)
    {
        std::cout<<i<<" ";
    }
    std::cout<<"\n";

    return 0;
}