#include <iostream>
#include <vector>

void Perform3NumSort(std::vector<int> &vec)
{
    if(vec.empty()) return;

    int index = 0, counter_2 = 0, next_place = 0;
    const auto size = vec.size();
    while(index < size) // iterate to count only 2's and in-place only 1's, for now forget about 3's
    {
        if(vec[index] == 2) counter_2++; // count only 2's 
        else if(vec[index] == 1) vec[next_place++] = 1; // in-place only 1's
        
        index++; // increment index
    }

    while(counter_2) // in-place only 2's based on counter
    {
        counter_2--;
        vec[next_place++] = 2;
    }

    while(next_place < size) // in-place only 3's for everything else
    {
        vec[next_place++] = 3;
    }
}

void Display(const std::vector<int> &input)
{
    for (const auto &i : input) std::cout<<i<<" "; 
    std::cout<<"\n";
}

int main()
{
    // Test case 1:
    std::vector<int> vec1{3, 3, 2, 1, 3, 2, 1};
    Perform3NumSort(vec1);
    Display(vec1);

    // Test case 2:
    std::vector<int> vec2{1, 1, 3, 3, 2, 1, 3, 2, 1};
    Perform3NumSort(vec2);
    Display(vec2);

    // Test case 3:
    std::vector<int> vec3{1, 1, 3, 3, 1, 3, 1};
    Perform3NumSort(vec3);
    Display(vec3);

    // Test case 4:
    std::vector<int> vec4{3, 2, 2, 2, 2, 2, 1};
    Perform3NumSort(vec4);
    Display(vec4);

    // Test case 5:
    std::vector<int> vec5{1, 1, 1, 1, 1};
    Perform3NumSort(vec5);
    Display(vec5);

    // Test case 6:
    std::vector<int> vec6{2, 2, 2, 2, 2, 2};
    Perform3NumSort(vec6);
    Display(vec6);

    // Test case 7:
    std::vector<int> vec7{3, 3, 3, 3, 3};
    Perform3NumSort(vec7);
    Display(vec7);

    return 0;
}