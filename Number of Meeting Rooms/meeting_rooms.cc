#include <iostream>
#include <vector>
#include <tuple>
#include <map>

using vtii = std::vector<std::tuple<uint32_t, uint32_t>>;

uint32_t GetMinMeetingRooms(const vtii& schedule)
{
    uint32_t rooms = 0;
    if(schedule.empty()) return rooms;

    auto total_meetings = schedule.size();
    std::map<uint32_t, int> timeline;
    for (const auto &iter : schedule)
    {
        auto [start_time, end_time] = iter;
        if(start_time < end_time)
        {
            timeline[start_time]++; // tick timeline - meeting starts
            timeline[end_time-1]--; // untick timeline - meeting ends
        }
    }
    
    int counter = 0;
    uint64_t total_non_overlapping_meetings = 0;
    for (const auto &iter : timeline) // iterate over timeline to calculate tick counters
    {
        if(!counter) total_non_overlapping_meetings++; // when tick becomes 0, at least 1 non-overlapping meeting starts
        counter += iter.second;
    }

    rooms = total_meetings - total_non_overlapping_meetings + 1;
    
    return rooms;
}

int main()
{
    // test-case 1:
    vtii schedule1{{0, 10}, {10, 20}};
    std::cout<<GetMinMeetingRooms(schedule1)<<"\n";

    // test-case 2:
    vtii schedule2{{20, 30}, {10, 21}, {0, 50}};
    std::cout<<GetMinMeetingRooms(schedule2)<<"\n";

    return 0;
}