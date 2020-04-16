#include <iostream>
#include <vector>
#include <unordered_set>
#include <tuple>

struct THash;
struct TEqual;

using vi = std::vector<int>;
using vvi = std::vector<vi>;
using coord = std::tuple<int, int>;
using vcoord = std::vector<coord>;
using ustii = std::unordered_set<coord, THash, TEqual>; // reason why people don't like C++

struct THash { // forgive c++
    size_t operator()(const std::tuple<int, int> & tr) const {
        int x = (std::get<0>(tr) * 100000 + std::get<1>(tr) & std::get<1>(tr) ) + (std::get<0>(tr) + 100000 *  std::get<1>(tr) & std::get<0>(tr) );
        return std::hash<int>()(x);
    }
};

struct TEqual { // forgive c++ again
    bool operator()(const std::tuple<int, int> & tr1, const std::tuple<int, int> & tr2) const {

        if (std::get<0>(tr1) == std::get<0>(tr2) && std::get<1>(tr1) == std::get<1>(tr2))
            return true;
        else
            return false;
    }
};

vi SpiralTraversal(const vvi & grid) // we are not going to make any change in the input grid
{
    static const vcoord steering {{0,1}, {1,0}, {0,-1}, {-1,0}};
    static const uint32_t steer_count = steering.size();

    vi ret;
    if(grid.empty()) return ret;

    auto grid_side_x = grid.size();
    auto grid_side_y = grid[0].size();
    auto grid_size = grid_side_x * grid_side_y;

    coord curr_point {0,0}, next_point {0, 0}; 
    ret.emplace_back(grid[std::get<0>(curr_point)][std::get<1>(curr_point)]); // assume first value already traversed
    uint32_t dist_covered = 1;

    ustii track_boundary_points;
    track_boundary_points.emplace(curr_point); // we will not traverse these points again

    
    int curr_steer = 0;
    bool boundary_value = false;
    while(grid_size > dist_covered)
    {
        next_point = {std::get<0>(curr_point) + std::get<0>(steering.at((size_t)curr_steer)), 
                      std::get<1>(curr_point) + std::get<1>(steering.at((size_t)curr_steer))};

        if(std::get<0>(next_point) >= 0 && std::get<0>(next_point) < grid_side_x //  check x-coordinate boundary condition
        && std::get<1>(next_point) >= 0 && std::get<1>(next_point) < grid_side_y //  check y-coordinate boundary condition
        && track_boundary_points.find(next_point) == track_boundary_points.end()) // check NOT among boundary values
        {
            ret.emplace_back(grid[std::get<0>(next_point)][std::get<1>(next_point)]);
            if(boundary_value) // we don't save all point, only effeciently update: track_boundary_points
            {
                boundary_value = false;
                track_boundary_points.emplace(next_point);
            }
        }
        else // we have reach boundary here
        {
            curr_steer = (1 + curr_steer) % steer_count;
            boundary_value = true;
            continue;
        }

        curr_point = next_point;
        dist_covered++;
    }

    return ret;
}

void Display(const vi &vec)
{
    for (const auto &iter : vec)
    {
        std::cout<<iter<<" ";
    }
    std::cout<<"\n";
}

int main()
{
    // test case 1:
     vvi grid1 {{1,  2,  3,  4,  5},
                {6,  7,  8,  9,  10},
                {11, 12, 13, 14, 15},
                {16, 17, 18, 19, 20}};
    auto spiral1 = SpiralTraversal(grid1);
    Display(spiral1);

    // test case 2:
    vvi grid2 {{1,  2,  3,  4},
               {6,  7,  8,  9},
               {11, 12, 13, 14}};
    auto spiral2 = SpiralTraversal(grid2);
    Display(spiral2);

    // test case 3:
    vvi grid3 {{1}};
    auto spiral3 = SpiralTraversal(grid3);
    Display(spiral3);

    // test case 4:
    vvi grid4 {{1, 2}};
    auto spiral4 = SpiralTraversal(grid4);
    Display(spiral4);

    // test case 5:
    vvi grid5 {{1, 2},
               {3, 4}};
    auto spiral5 = SpiralTraversal(grid5);
    Display(spiral5);

    return 0;
}