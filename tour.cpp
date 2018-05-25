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

bool atEdge(int n, Point pos, std::pair <Grid, Point> grid)
{
    return (pos.first != 0 && pos.first != n-1 && pos.second != 0 && pos.second != n-1) &&
            (((grid.second.first == 0 || grid.second.first == grid.first.first-1) &&
              (grid.second.second < 3 || grid.second.second >= grid.first.second-3)) ||
             ((grid.second.second == 0 || grid.second.second == grid.first.second-1) &&
              (grid.second.first < 3 || grid.second.first >= grid.first.first-3)));
}

static const std::vector <std::vector <std::vector <Offset>>> Grid66 =
{
    {{{2,1},{1,2}}, {{-1,2},{1,2}}, {{-2,1},{2,1}}, {{-2,1},{2,1}}, {{-2,1},{1,2}}, {{-2,1},{-1,2}}},
    {{{2,-1},{2,1}}, {{2,-1},{-1,2}}, {{-2,-1},{2,-1}}, {{2,-1},{1,2}}, {{-2,-1},{-1,2}}, {{-2,-1},{-2,1}}},
    {{{1,-2},{1,2}}, {{-1,-2},{2,1}}, {{-2,-1},{-1,-2}}, {{2,-1},{2,1}}, {{1,-2},{1,2}}, {{-1,-2},{-1,2}}},
    {{{1,-2},{1,2}}, {{-1,2},{1,2}}, {{-2,1},{2,1}}, {{-2,-1},{1,-2}}, {{-1,-2},{1,2}}, {{-2,-1},{-1,2}}},
    {{{2,-1},{2,1}}, {{-1,-2},{2,1}}, {{-2,1},{2,1}}, {{-2,1},{2,1}}, {{-2,-1},{1,-2}}, {{-1,-2}, {-2,1}}},
    {{{1,-2},{2,-1}}, {{-1,-2},{2,-1}}, {{-1,-2},{-2,-1}}, {{-2,-1},{2,-1}}, {{-2,-1},{1,-2}}, {{-1,-2},{-2,-1}}}
};

static const std::map <Grid, const std::vector <std::vector <std::vector <Offset>>> &> m =
{
    {{6,6}, Grid66}
};

static Point nextPoint(int n, Point pos, Point lastPos)
{
    std::pair <Grid, Point> ret = localize(n, pos);
    const std::vector <std::vector <std::vector <Offset>>> &grid = m.at(ret.first);
    const std::vector <Offset> &v = grid[ret.second.second][ret.second.first];
    const Offset &o1 = v[0];
    const Offset &o2 = atEdge(n, pos, ret) ? v[2] : v[1];
    Point newpoint1 = std::make_pair(pos.first+o1.first, pos.second+o1.second);
    Point newpoint2 = std::make_pair(pos.first+o2.first, pos.second+o2.second);
    return lastPos == newpoint1 ? newpoint2 : newpoint1;
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
