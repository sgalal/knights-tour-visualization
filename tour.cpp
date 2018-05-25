#include <cassert>
#include <array>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <emscripten/bind.h>

using Grid = std::pair <int, int>;
using Point = std::pair <int, int>;
using Offset = std::pair <int, int>;

using namespace emscripten;

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

static const std::vector <std::vector <std::vector <const Offset *>>> Grid66 =
{
    {{d[4],d[5]}, {d[6],d[5]}, {d[7],d[4]}, {d[7],d[4]}, {d[7],d[5]}, {d[7],d[6]}},
    {{d[3],d[4]}, {d[3],d[6]}, {d[0],d[3]}, {d[3],d[5]}, {d[0],d[6]}, {d[0],d[7]}},
    {{d[2],d[5]}, {d[1],d[4]}, {d[0],d[1]}, {d[3],d[4]}, {d[2],d[5]}, {d[1],d[6]}},
    {{d[2],d[5]}, {d[6],d[5]}, {d[7],d[4]}, {d[0],d[2]}, {d[1],d[5]}, {d[0],d[6]}},
    {{d[3],d[4]}, {d[1],d[4]}, {d[7],d[4]}, {d[7],d[4]}, {d[0],d[2]}, {d[1],d[7]}},
    {{d[2],d[3]}, {d[1],d[3]}, {d[1],d[0]}, {d[0],d[3]}, {d[0],d[2]}, {d[1],d[0]}}
};

static const std::vector <std::vector <std::vector <const Offset *>>> Grid88 =
{
    {{d[5],d[4]}, {d[5],d[6]}, {d[5],d[7]}, {d[4],d[7]}, {d[5],d[7]}, {d[4],d[7]}, {d[5],d[7]}, {d[6],d[7]}},
    {{d[3],d[5]}, {d[3],d[6]}, {d[3],d[0]}, {d[3],d[6]}, {d[3],d[6]}, {d[3],d[0]}, {d[5],d[6]}, {d[0],d[7]}},
    {{d[2],d[5]}, {d[1],d[6]}, {d[1],d[7]}, {d[1],d[5]}, {d[4],d[5]}, {d[1],d[3]}, {d[2],d[5]}, {d[1],d[6]}},
    {{d[2],d[3]}, {d[1],d[5]}, {d[2],d[5]}, {d[2],d[4]}, {d[6],d[7]}, {d[2],d[4]}, {d[0],d[5]}, {d[1],d[6]}},
    {{d[2],d[5]}, {d[1],d[6]}, {d[3],d[7]}, {d[4],d[5]}, {d[1],d[6]}, {d[0],d[1]}, {d[2],d[5]}, {d[0],d[1]}},
    {{d[3],d[5]}, {d[5],d[6]}, {d[1],d[4]}, {d[1],d[2]}, {d[4],d[5]}, {d[0],d[5]}, {d[2],d[5]}, {d[1],d[6]}},
    {{d[2],d[4]}, {d[1],d[4]}, {d[4],d[7]}, {d[2],d[7]}, {d[0],d[1]}, {d[4],d[7]}, {d[0],d[7]}, {d[1],d[7]}},
    {{d[2],d[3]}, {d[1],d[3]}, {d[0],d[1]}, {d[0],d[3]}, {d[0],d[3]}, {d[1],d[3]}, {d[1],d[2]}, {d[1],d[0]}}
};

static const std::map <Grid, const std::vector <std::vector <std::vector <const Offset *>>> &> m =
{
    {{6,6}, Grid66},
    {{8,8}, Grid88}
};

static Point nextPoint(int n, Point pos, Point lastPos)
{
    std::pair <Grid, Point> ret = localize(n, pos);
    const std::vector <std::vector <std::vector <const Offset *>>> &grid = m.at(ret.first);
    const std::vector <const Offset *> &v = grid[ret.second.second][ret.second.first];
    const Offset *o1 = v[0];
    const Offset *o2 = atEdge(n, pos, ret) ? v[2] : v[1];
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

EMSCRIPTEN_BINDINGS(my_module)
{
    class_ <Point> ("Point");
    function("make_point", make_point);
    function("getFirst", getFirst);
    function("getSecond", getSecond);
    function("nextPoint", nextPoint);
}
