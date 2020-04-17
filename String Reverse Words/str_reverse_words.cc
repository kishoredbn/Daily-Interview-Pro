#include <iostream>

void ReverseString(std::string &input, uint64_t first_index, uint64_t last_index)
{
    while(first_index < last_index)
    {
        input[first_index] += input[last_index];
        input[last_index] = input[first_index] - input[last_index];
        input[first_index] -= input[last_index];
        first_index++;
        last_index--;
    }
}

void ReverseWords(std::string &input) // inplace - and constant buffer
{
    if(input.empty()) return; // validate

    uint64_t first_index = 0;
    auto str_size = input.size();

    if(str_size == 1) return; // optimization for 1 letter string input

    auto last_index = str_size - 1;
    ReverseString(input, first_index, last_index); // reverse the whole input string

    uint64_t prev_index = first_index = last_index = 0;
    while(str_size >= last_index) // now reverse each words in the string
    {
        if(input[last_index] == ' ' || input[last_index] == '\0')
        {
            ReverseString(input, first_index, prev_index);
            first_index = ++last_index;
        }
        prev_index = last_index++;
    }
}

int main()
{
    // test case 1:
    std::string input1 = "can you read this";
    ReverseWords(input1);
    std::cout<<input1<<"\n";

    // test case 2:
    std::string input2 = "canyoureadthis";
    ReverseWords(input2);
    std::cout<<input2<<"\n";

    // test case 3:
    std::string input3 = "c";
    ReverseWords(input3);
    std::cout<<input3<<"\n";

    // test case 4:
    std::string input4 = "ca";
    ReverseWords(input4);
    std::cout<<input4<<"\n";

    return 0;
}