#include <iostream>
#include <vector>
#include <tuple>
#include <map>

using tii = std::tuple<int, int>;
using tiii = std::tuple<int, int, int>;
using vtii = std::vector<tii>;
using vtiii = std::vector<tiii>;

vtii generate_skyline(const vtiii &vcity)
{
    vtii skyline;
    if(vcity.empty()) return skyline; // validate input

    std::map<int, int> timeline; // make a timeline-like "decrete points" to compare heights later
    for(auto &iter : vcity) // for every build - make an entry to timeline
    {
        auto [start_point, last_point, height] = iter;
        if(timeline.find(start_point) == timeline.end()) // for start of building 
            timeline[start_point] = height; // make an entry if it was not added
        else if(timeline[start_point] < height) // in case of contention, add only if existing height is lesser
        {
            timeline[start_point] = height; 
        }
        
        if(timeline.find(last_point) == timeline.end()) // only add the end point if an entry is missing
        {
            timeline[last_point] = 0; // 0 denoted end of a building
        }
    }

    for(auto &iter : vcity) // visit each building
    {
        auto [start_point, last_point, height] = iter;
        auto map_start_point = timeline.find(start_point); // get its start and last point from timeline...
        auto map_last_point = timeline.find(last_point);
        for(auto &iter_map = map_start_point; iter_map != map_last_point; iter_map++) // ...and iterate over every point in-between
        {
            if(iter_map->second < height) iter_map->second = height; // check where height dominates, that updates
        }
    }

    int last_height = 0; // results almost ready at this point - but remove duplicate heights**...
    for(auto &iter_map : timeline) // ...and move results from map to vector
    {
        if(iter_map.second != last_height) // **remove duplicate entry of same height
        {
            last_height = iter_map.second;
            skyline.emplace_back(iter_map.first, iter_map.second);
        }
    }

    return skyline;
}

void display(const vtii &skyline)
{
    for (auto &&iter : skyline)
    {
        std::cout<<"("<<std::get<0>(iter)<<", "<<std::get<1>(iter)<<"), ";
    }
    std::cout<<"\n";
}

int main()
{
    //test case 1:
    vtiii  building{{2, 8, 3}, {4, 6, 5}};
    auto skyline = generate_skyline(building);
    display(skyline);

    //test case 2:
    vtiii  building1{{2, 5, 3}, {4, 6, 5}};
    auto skyline1 = generate_skyline(building1);
    display(skyline1);
    
    return 0;
}