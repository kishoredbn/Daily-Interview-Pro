#include <iostream>
#include <functional>
#include <queue>
#include <tuple>

const uint32_t kaprekars_const = 6174;

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

uint16_t GenIterKaprekars(const uint32_t input) // check if the problem is solved
{
    if(input == kaprekars_const) return 0; // quick validation - return on receiving kaprekars const
    
    auto [ascending_number, decending_number] = GenerateNumber(input); // get the ascending and descending number
    auto output = decending_number - ascending_number; // output stores the new value

    return 1 + GenIterKaprekars(output); // call function again to check if that solves
}

void display(uint32_t number) // just a helper function
{
    std::cout<<"kaprekars_const iter for "<<number<<" : "<<GenIterKaprekars(number)<<"\n";
}

int main()
{
    display(3);    // test case 1
    display(34);   // test case 2
    display(213);  // test case 3
    display(3156); // test case 4
    display(5345); // test case 5
    display(6174); // test case 6
    return 0;
}