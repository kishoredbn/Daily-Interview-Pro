#include <iostream>
#include <functional>
#include <queue>
#include <tuple>
#include <unordered_map>

const uint32_t kaprekars_const = 6174;

using umi32i8 = std::unordered_map<uint32_t, uint8_t>;

std::tuple<uint32_t, uint32_t> GenerateNumber(uint32_t input) // for sorting the letters in number
{
    uint32_t asc = 0, des = 0;
    std::priority_queue<uint8_t, std::vector<uint8_t>, std::greater<uint8_t>> min_heap; // use min heap

    while(input > 0) // store each letter to min heap
    {
        auto letter = input%10;
        input /= 10;
        min_heap.emplace(letter);
    }

    while(min_heap.size() < 4) // fill the unfilled spaces with 0
    {
        min_heap.emplace(0);
    }

    uint32_t unit = 1;
    while (min_heap.size()) // generate ascending number and descending number
    {
        auto letter = min_heap.top(); min_heap.pop();
        asc = (asc * 10) + letter; // in ascending number, add letter from min heap to back
        des = des + (letter * unit); // in descending number, add letter from min heap to front
        unit *= 10;
    }

    return {asc, des};
}

uint16_t GenIterKaprekars(const uint32_t input, umi32i8 &memo, int count = 0) // checks first if the problem is solved
{
    if(input == kaprekars_const) // quick validation - return on receiving kaprekars const
    {
        memo[input] = 0;
        return 0;
    }
    if(memo.find(input) != memo.end()) // memoization
    {
        return memo[input];
    }
    
    auto [ascending_number, decending_number] = GenerateNumber(input); // get the ascending and descending number
    auto output = decending_number - ascending_number; // output stores the new value

    if(memo.find(output) != memo.end()) // memoization
    {
        return memo[output];
    }

    memo[output] = 1 + GenIterKaprekars(output, memo, count+1); // call function again to check if that solves

    return memo[output];
}

void display(uint32_t number, umi32i8 &memo)
{
    std::cout<<"kaprekars_const iter for "<<number<<" : "<<GenIterKaprekars(number, memo)<<"\n";
}

int main()
{
    umi32i8 memo; // memoization 
    display(3, memo);    // test case 1
    display(34, memo);   // test case 2
    display(213, memo);  // test case 3
    display(3156, memo); // test case 4
    display(5345, memo); // test case 5
    display(6174, memo); // test case 6
    return 0;
}