#include <cassert>
#include <array>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>

using Grid = std::pair <int, int>;
using Point = std::pair <int, int>;
using Offset = std::pair <int, int>;

static std::pair <Grid, Point> localize(int n, Point pos)
{
    int gridx = n;
    int gridy = n;
    int x = pos.first;
    int y = pos.second;

    auto process = [](int &grid, int &z)
    {
        int halve = grid/2;
        int mod = halve%2;
        int left = halve-mod;
        int right = halve+mod;
        if(z < left)
        {
            grid = left;
        }
        else
        {
            grid = right;
            z -= left;
        }
    };

    while((std::min(gridx, gridy) > 10) ||
           (std::max(gridx, gridy) > 12))
    {
        process(gridx, x);
        process(gridy, y);
    }

    return std::make_pair(std::make_pair(gridx, gridy), std::make_pair(x, y));
}

static bool atEdge(int n, Point pos, std::pair <Grid, Point> grid)
{
    return (pos.first != 0 && pos.first != n-1 && pos.second != 0 && pos.second != n-1) &&
            (((grid.second.first == 0 || grid.second.first == grid.first.first-1) &&
              (grid.second.second < 3 || grid.second.second >= grid.first.second-3)) ||
             ((grid.second.second == 0 || grid.second.second == grid.first.second-1) &&
              (grid.second.first < 3 || grid.second.first >= grid.first.first-3)));
}

static const std::array <const Offset *, 8> d =
{
    new Offset(-2,-1),
    new Offset(-1,-2),
    new Offset(1,-2),
    new Offset(2,-1),
    new Offset(2,1),
    new Offset(1,2),
    new Offset(-1,2),
    new Offset(-2,1)
};

static const std::vector <std::vector <std::vector <unsigned int>>> Grid66 =
{
    {{4,5}, {6,5}, {7,4}, {7,4}, {7,5}, {7,6}},
    {{3,4}, {3,6}, {0,3}, {3,5}, {0,6}, {0,7}},
    {{2,5}, {1,4}, {0,1}, {3,4}, {2,5}, {1,6}},
    {{2,5}, {6,5}, {7,4}, {0,2}, {1,5}, {0,6}},
    {{3,4}, {1,4}, {7,4}, {7,4}, {0,2}, {1,7}},
    {{2,3}, {1,3}, {1,0}, {0,3}, {0,2}, {1,0}}
};

static const std::vector <std::vector <std::vector <unsigned int>>> Grid88 =
{
    {{5,4}, {5,6}, {5,7}, {4,7}, {5,7}, {4,7}, {5,7}, {6,7}},
    {{3,5}, {3,6}, {3,0}, {3,6}, {3,6}, {3,0}, {5,6}, {0,7}},
    {{2,5}, {1,6}, {1,7}, {1,5}, {4,5}, {1,3}, {2,5}, {1,6}},
    {{2,3}, {1,5}, {2,5}, {2,4}, {6,7}, {2,4}, {0,5}, {1,6}},
    {{2,5}, {1,6}, {3,7}, {4,5}, {1,6}, {0,1}, {2,5}, {0,1}},
    {{3,5}, {5,6}, {1,4}, {1,2}, {4,5}, {0,5}, {2,5}, {1,6}},
    {{2,4}, {1,4}, {4,7}, {2,7}, {0,1}, {4,7}, {0,7}, {1,7}},
    {{2,3}, {1,3}, {0,1}, {0,3}, {0,3}, {1,3}, {1,2}, {1,0}}
};

static const std::map <Grid, const std::vector <std::vector <std::vector <unsigned int>>> &> m =
{
    {{6,6}, Grid66},
    {{8,8}, Grid88}
};

static Point nextPoint(int n, Point pos, Point lastPos)
{
    std::pair <Grid, Point> ret = localize(n, pos);
    const std::vector <std::vector <std::vector <unsigned int>>> &grid = m.at(ret.first);
    const std::vector <unsigned int> &v = grid[ret.second.second][ret.second.first];
    const Offset *o1 = d[v[0]];
    const Offset *o2 = atEdge(n, pos, ret) ? d[v[2]] : d[v[1]];
    Point newpoint1 = std::make_pair(pos.first+o1->first, pos.second+o1->second);
    Point newpoint2 = std::make_pair(pos.first+o2->first, pos.second+o2->second);
    if(lastPos == newpoint1) return newpoint2;
    else if(lastPos == newpoint2) return newpoint1;
    assert(0);
}

static Point make_point(int x, int y)
{
    return std::make_pair(x, y);
}

static int getFirst(Point p)
{
    return p.first;
}

static int getSecond(Point p)
{
    return p.second;
}
