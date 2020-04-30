#include <iostream>
#include <vector>
#include <stack>

std::vector<int> NextLargerindices(const std::vector<int> &input)
{
    auto size = input.size();
    std::vector<int> ret(size, -1);
    if(!size) return ret;

    std::stack<uint32_t> stack; // pops elemets in ascending order ie, smaller elements first, larger element last
    for(uint32_t index = 0; index < size - 1; index++) // for each element in input
    {
        while(stack.size()) // check if there is any stack element
        {
            auto top_index = stack.top();
            if(input[index] > input[top_index]) // check if currently indexed elemt is greater than top of the stack
            {
                ret[top_index] = index; // if so, assign stack tops index to current index
                stack.pop(); // pop off the top & continue until stack goes empty
            }
            else // else break the loop
            {
                break;
            }
        }
        if(input[index] < input[index+1]) // check if next element is larger than current element
        {
            ret[index] = index+1;
        }
        else // else push to stack
        {
            stack.emplace(index);
        }
    }

    return ret;
}

void Display(const std::vector<int> &input)
{
    for (auto &iter : input) std::cout<<iter<<", ";
    std::cout<<"\n";
}

int main()
{
    // test case 1:
    std::vector<int> input1 = {3, 2, 5, 6, 9, 8};
    auto output1 = NextLargerindices(input1);
    Display(output1);

    // test case 2:
    std::vector<int> input2 = {30, 20, 10, 15, 25, 40, 90, 80, 85};
    auto output2 = NextLargerindices(input2);
    Display(output2);

    // test case 3:
    std::vector<int> input3 = {30};
    auto output3 = NextLargerindices(input3);
    Display(output3);

    // test case 4:
    std::vector<int> input4 = {30, 20};
    auto output4 = NextLargerindices(input4);
    Display(output4);

    return 0;
}