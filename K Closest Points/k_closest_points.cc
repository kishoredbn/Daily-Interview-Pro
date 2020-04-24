#include <iostream>
#include <vector>
#include <queue>

struct Points;
using tii = std::tuple<int32_t, int32_t>;
using vti32i32 = std::vector<tii>;
using pqti32i32 = std::priority_queue<Points>;

struct Points
{
    tii x;
    Points(tii x) : x(x) {}
    bool operator<(const Points &other) const { return (Distance() > other.Distance());}
    uint64_t Distance() const { return (std::get<0>(x) * std::get<0>(x)) + (std::get<1>(x) * std::get<1>(x));} // gets cartesian product (without sq.root for performance)
};

vti32i32 KClosestPoints(const vti32i32 &input, uint32_t k)
{
    vti32i32 ret;
    if(input.empty()) return ret;

    pqti32i32 min_heap;
    for (const auto &iter : input) min_heap.emplace(iter);

    while(k--)
    {
        auto temp = min_heap.top(); min_heap.pop();
        ret.emplace_back(std::get<0>(temp.x), std::get<1>(temp.x));
    }
    
    return ret;
}

void Display(const vti32i32 &input)
{
    std::cout<<"{";
    for (const auto &iter : input)
        std::cout<<"{"<<std::get<0>(iter)<<", "<<std::get<1>(iter)<<"}, ";

    std::cout<<"}\n";
}

int main()
{
    // test case 1:
    vti32i32 input1 = {{0, 0}, {1, 2}, {-3, 4}, {3, 1}};
    vti32i32 output1 = KClosestPoints(input1, 2);
    Display(output1);

    // test case 2:
    vti32i32 input2 = {{0, 0}, {1, 2}, {-3, 4}, {3, 1}, {1, 5}, {1, 1}, {2,3}, {5,1}, {3, 2}};
    vti32i32 output2 = KClosestPoints(input2, 5);
    Display(output2);

    // test case 3:
    vti32i32 input3 = {{4, 0}, {2, 2}, {-3, 4}, {3, 1}, {0,1}};
    vti32i32 output3 = KClosestPoints(input3, 1);
    Display(output3);

    return 0;
}