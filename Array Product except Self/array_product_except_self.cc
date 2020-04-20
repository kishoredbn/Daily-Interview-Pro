#include<iostream>
#include <vector>

std::vector<int> Product(const std::vector<int> &input)
{
    std::vector<int> ret(input.size(), 1);
    if(input.empty()) return ret;

    auto size = input.size();

    auto vec1 = ret;
    auto vec2 = ret;
    for(auto iter = 0; iter < size - 1; iter++ ) // O(N)
    {
        vec1[iter+1] = vec1[iter] * input[iter];
    }

    for(auto iter = size - 1 ; iter > 0; iter-- ) // O(N)
    {
        vec2[iter-1] = vec2[iter] * input[iter];
    }

    for(auto iter = 0; iter < size; iter++) // O(N)
    {
        ret[iter] = vec1[iter] * vec2[iter];
    }

    return ret; // O(N) = O(N) + O(N) + O(N) = 3x O(N) 
}

void Display(const std::vector<int> &input)
{
    for (auto &iter : input) std::cout<<iter<<" ";
    std::cout<<"\n";
}

int main()
{
    // test case 1:
    std::vector<int> vec1 = {1, 2, 3, 4, 5};
    auto out1 = Product(vec1);
    Display(out1);

    // test case 2:
    std::vector<int> vec2 = {1, 2, 3};
    auto out2 = Product(vec2);
    Display(out2);

    // test case 3:
    std::vector<int> vec3 = {2, 3};
    auto out3 = Product(vec3);
    Display(out3);

    // test case 4:
    std::vector<int> vec4 = {6};
    auto out4 = Product(vec4);
    Display(out4);

    return 0;
}