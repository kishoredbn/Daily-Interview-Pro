#include <iostream>
#include <unordered_map>

using umi64i64 = std::unordered_map<uint64_t, uint64_t>;

uint64_t NFibonacci(uint64_t input, umi64i64 &memoize)
{
    uint64_t ret = 0;
    if(!input) return ret;

    auto find = memoize.find(input);
    if(find != memoize.end()) return find->second;

    ret = NFibonacci(input - 2, memoize) + NFibonacci(input - 1, memoize);
    memoize[input] = ret;
    return ret;
}

int main()
{
    umi64i64 memoize {{0,0}, {1, 1}};
    std::cout<<NFibonacci(9, memoize)<<"\n"; // test case 1
    std::cout<<NFibonacci(1, memoize)<<"\n"; // test case 2
    std::cout<<NFibonacci(2, memoize)<<"\n"; // test case 3
    std::cout<<NFibonacci(3, memoize)<<"\n"; // test case 4
    std::cout<<NFibonacci(4, memoize)<<"\n"; // test case 5
    std::cout<<NFibonacci(5, memoize)<<"\n"; // test case 6
    std::cout<<NFibonacci(6, memoize)<<"\n"; // test case 7
    std::cout<<NFibonacci(7, memoize)<<"\n"; // test case 8
    std::cout<<NFibonacci(8, memoize)<<"\n"; // test case 9
    std::cout<<NFibonacci(10, memoize)<<"\n"; // test case 10
    std::cout<<NFibonacci(50, memoize)<<"\n"; // test case 11
    std::cout<<NFibonacci(75, memoize)<<"\n"; // test case 12
    std::cout<<NFibonacci(90, memoize)<<"\n"; // test case 13
    std::cout<<NFibonacci(93, memoize)<<"\n"; // test case 14
    return 0;
}