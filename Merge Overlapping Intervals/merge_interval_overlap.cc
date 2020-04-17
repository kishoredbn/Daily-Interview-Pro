#include <iostream>
#include <vector>
#include <tuple>
#include <map>

using vtii = std::vector<std::tuple<uint32_t, uint32_t>>;

vtii MergeIntervals(const vtii& schedule)
{
    vtii ret_merged_intervals {0};
    if(schedule.empty()) return ret_merged_intervals;

    std::map<uint32_t, int> timeline;
    for (const auto &iter : schedule)
    {
        auto [start_time, end_time] = iter;
        if(start_time < end_time)
        {
            timeline[start_time]++; // tick timeline - meeting starts
            timeline[end_time]--; // untick timeline - meeting ends
        }
    }
    
    int counter = 0;
    uint32_t start_merge_interval = 0, stop_merge_interval = 0;
    for (const auto &iter : timeline) // iterate over timeline to calculate tick counters
    {
        if(!counter) start_merge_interval = iter.first; // when tick becomes 0, non-overlapping meeting starts
        counter += iter.second;
        if(!counter) 
        {
            stop_merge_interval = iter.first; // when tick becomes 0, non-overlapping meeting ends
            ret_merged_intervals.emplace_back(start_merge_interval, stop_merge_interval);
        }
    }
    
    return ret_merged_intervals;
}

void Display(const vtii &intervals)
{
    for (auto &iter : intervals)
    {
        std::cout<<"("<<std::get<0>(iter)<<", "<<std::get<1>(iter)<<"), ";
    }
    std::cout<<"\n";
}

int main()
{
    // test-case 1:
    vtii schedule1{{1, 3}, {5, 8}, {4, 10}, {20, 25}};
    auto merge_intervals1 = MergeIntervals(schedule1);
    Display(merge_intervals1);

    // test-case 2:
    vtii schedule2{{20, 30}, {10, 21}, {0, 50}};
    auto merge_intervals2 = MergeIntervals(schedule2);
    Display(merge_intervals2);

    // test-case 3:
    vtii schedule3{{20, 30}, {10, 20}, {31, 50}};
    auto merge_intervals3 = MergeIntervals(schedule3);
    Display(merge_intervals3);

    return 0;
}