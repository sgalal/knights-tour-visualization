#include <cassert>
#include <array>
#include <vector>
#include <map>
#include <utility>
#include <tuple>
#include <algorithm>

using Grid = std::pair <int, int>;
using Point = std::pair <int, int>;
using Offset = std::pair <int, int>;
using JunctionalAngleType = unsigned int;

static std::tuple <Grid, Point, JunctionalAngleType> localize(int n, Point pos)
{
    int gridx = n;
    int gridy = n;
    int x = pos.first;
    int y = pos.second;

    int blockChoiceX = 0;
    int blockChoiceY = 0;

    JunctionalAngleType jat = 0;

    auto process = [](int &grid, int &z, int &blockChoiceZ)
    {
        int halve = grid/2;
        int mod = halve%2;
        int left = halve-mod;
        int right = halve+mod;
        if(z < left)
        {
            grid = left;
            blockChoiceZ = 1;
        }
        else
        {
            grid = right;
            z -= left;
            blockChoiceZ = 2;
        }
    };

    while(std::min(gridx, gridy) > 10 ||
          std::max(gridx, gridy) > 12)
    {
        process(gridx, x, blockChoiceX);
        process(gridy, y, blockChoiceY);
        
        assert(!((!blockChoiceX)^(!blockChoiceY)));
        jat =
            blockChoiceX == 1 && blockChoiceY == 1 && (x == gridx-3 && y == gridy-1) ? 1 :
            blockChoiceX == 1 && blockChoiceY == 1 && (x == gridx-1 && y == gridy-2) ? 2 :
            blockChoiceX == 2 && blockChoiceY == 1 && (x == 1       && y == gridy-3) ? 3 :
            blockChoiceX == 2 && blockChoiceY == 1 && (x == 0       && y == gridy-1) ? 4 :
            blockChoiceX == 2 && blockChoiceY == 2 && (x == 2       && y == 0      ) ? 5 :
            blockChoiceX == 2 && blockChoiceY == 2 && (x == 0       && y == 1      ) ? 6 :
            blockChoiceX == 1 && blockChoiceY == 2 && (x == gridx-2 && y == 2      ) ? 7 :
            blockChoiceX == 1 && blockChoiceY == 2 && (x == gridx-1 && y == 0      ) ? 8 : jat;
    }

    return std::make_tuple(std::make_pair(gridx, gridy), std::make_pair(x, y), jat);
}

static const std::array <const Offset, 8> d =
{
    Offset(-2,-1), Offset(-1,-2),
    Offset( 1,-2), Offset( 2,-1),
    Offset( 2, 1), Offset( 1, 2),
    Offset(-1, 2), Offset(-2, 1)
};

static const std::vector <std::vector <std::vector <unsigned int>>> Grid66 =
{
    {{4,5}, {5,6}, {7,4}/* 5 */, {4,7}, {5,7}, {6,7}/* 8 */},
    {{3,4}/* 6 */, {3,6}, {0,3}, {3,5}, {0,6}, {0,7}},
    {{2,5}, {1,4}, {0,1}, {3,4}, {2,5}/* 7 */, {1,6}},
    {{2,5}, {6,5}/* 3 */, {4,7}, {0,2}, {1,5}, {0,6}},
    {{3,4}, {1,4}, {4,7}, {4,7}, {0,2}, {7,1}/* 2 */},
    {{2,3}/* 4 */, {1,3}, {1,0}, {3,0}/* 1 */, {0,2}, {0,1}}
};

static const std::vector <std::vector <std::vector <unsigned int>>> Grid86 =
{
    {{4,5}, {4,6}, {7,4}/* 5 */, {4,7}, {4,6}, {4,6}, {5,7}, {6,7}/* 8 */},
    {{3,4}/* 6 */, {3,6}, {6,0}, {0,4}, {0,3}, {0,3}, {0,5}, {0,7}},
    {{2,5}, {1,4}, {0,5}, {2,5}, {2,5}, {0,3}, {2,5}/* 7 */, {1,6}},
    {{2,5}, {6,2}/* 3 */, {6,7}, {0,6}, {6,7}, {5,6}, {5,7}, {1,6}},
    {{3,4}, {1,4}, {3,7}, {1,4}, {1,3}, {1,4}, {2,7}, {7,1}/* 2 */},
    {{2,3}/* 4 */, {1,2}, {0,2}, {0,2}, {2,3}, {3,0}/* 1 */, {1,2}, {0,1}}
};

static const std::vector <std::vector <std::vector <unsigned int>>> Grid88 =
{
    {{4,5}, {5,6}, {7,5}/* 5 */, {4,7}, {5,7}, {4,7}, {5,7}, {6,7}/* 8 */},
    {{3,5}/* 6 */, {3,6}, {0,3}, {3,6}, {3,6}, {0,3}, {5,6}, {0,7}},
    {{2,5}, {1,6}, {1,7}, {1,5}, {4,5}, {1,3}, {2,5}/* 7 */, {1,6}},
    {{2,3}, {1,5}, {2,5}, {2,4}, {6,7}, {2,4}, {0,5}, {1,6}},
    {{2,5}, {1,6}, {3,7}, {4,5}, {1,6}, {0,1}, {2,5}, {0,1}},
    {{3,5}, {6,5}/* 3 */, {1,4}, {1,2}, {4,5}, {0,5}, {2,5}, {1,6}},
    {{2,4}, {1,4}, {4,7}, {2,7}, {0,1}, {4,7}, {0,7}, {7,1}/* 2 */},
    {{2,3}/* 4 */, {1,3}, {0,1}, {0,3}, {0,3}, {3,1}/* 1 */, {1,2}, {0,1}}
};

static const std::vector <std::vector <std::vector <unsigned int>>> Grid10_8 =
{
    {{4,5}, {4,6}, {7,4}/* 5 */, {4,7}, {4,7}, {6,7}, {4,7}, {4,7}, {5,7}, {6,7}/* 8 */},
    {{3,4}/* 6 */, {3,6}, {0,3}, {0,3}, {0,3}, {0,3}, {0,3}, {3,4}, {0,5}, {0,6}},
    {{2,4}, {1,6}, {0,6}, {6,7}, {2,4}, {4,6}, {5,7}, {5,6}, {2,5}/* 7 */, {0,1}},
    {{2,5}, {3,5}, {0,5}, {4,6}, {3,5}, {5,7}, {0,4}, {0,7}, {2,5}, {1,7}},
    {{2,5}, {2,6}, {2,7}, {3,5}, {2,4}, {0,3}, {2,7}, {1,3}, {0,1}, {1,6}},
    {{3,6}, {6,1}/* 3 */, {1,2}, {1,6}, {3,5}, {1,7}, {0,1}, {4,5}, {5,7}, {1,6}},
    {{2,4}, {1,4}, {4,7}, {3,7}, {1,4}, {4,7}, {3,7}, {4,7}, {2,7}, {7,0}/* 2 */},
    {{2,3}/* 4 */, {1,3}, {0,2}, {0,3}, {0,3}, {1,3}, {0,3}, {3,0}/* 1 */, {1,2}, {0,1}}
};

static const std::vector <std::vector <std::vector <unsigned int>>> Grid10_10 =
{
    {{4,5}, {4,6}, {7,5}/* 5 */, {4,6}, {4,7}, {6,7}, {5,7}, {4,7}, {5,7}, {6,7}/* 8 */},
    {{3,4}/* 6 */, {4,6}, {0,3}, {0,3}, {3,5}, {0,3}, {0,3}, {3,4}, {5,6}, {6,0}},
    {{2,4}, {1,6}, {0,2}, {0,1}, {2,4}, {6,7}, {5,6}, {1,6}, {2,5}/* 7 */, {0,1}},
    {{2,4}, {5,6}, {0,6}, {3,5}, {4,5}, {1,4}, {0,4}, {2,6}, {2,5}, {1,6}},
    {{2,5}, {4,5}, {0,7}, {4,5}, {2,6}, {2,5}, {0,2}, {0,1}, {0,6}, {1,6}},
    {{2,3}, {2,6}, {1,7}, {0,5}, {1,7}, {0,1}, {2,6}, {6,7}, {2,6}, {1,7}},
    {{3,5}, {1,6}, {1,3}, {2,7}, {1,5}, {3,7}, {1,7}, {2,3}, {2,5}, {6,7}},
    {{2,5}, {6,3}/* 3 */, {5,6}, {3,7}, {1,3}, {2,7}, {2,6}, {2,3}, {5,6}, {6,7}},
    {{2,4}, {1,3}, {4,7}, {3,4}, {4,7}, {1,7}, {4,7}, {3,4}, {2,7}, {7,1}/* 2 */},
    {{2,3}/* 4 */, {1,2}, {0,3}, {1,3}, {0,3}, {0,2}, {0,3}, {3,2}/* 1 */, {0,2}, {0,1}}
};

static const std::vector <std::vector <std::vector <unsigned int>>> Grid12_10 =
{
    {{4,5}, {4,6}, {7,6}/* 5 */, {4,7}, {5,6}, {4,7}, {5,7}, {4,7}, {4,6}, {4,7}, {5,6}, {6,7}/* 8 */},
    {{3,5}/* 6 */, {3,6}, {0,7}, {0,3}, {3,6}, {0,3}, {6,7}, {0,3}, {5,6}, {0,3}, {0,5}, {0,6}},
    {{2,3}, {1,2}, {6,7}, {2,6}, {3,4}, {1,7}, {5,6}, {1,2}, {5,7}, {2,4}, {2,5}/* 7 */, {1,6}},
    {{2,3}, {1,6}, {4,5}, {2,3}, {4,7}, {2,7}, {0,3}, {2,7}, {5,7}, {1,6}, {2,5}, {0,1}},
    {{4,5}, {2,6}, {2,3}, {3,5}, {0,4}, {2,3}, {0,3}, {1,7}, {4,6}, {1,7}, {2,5}, {1,6}},
    {{2,4}, {4,5}, {0,7}, {1,6}, {4,6}, {3,6}, {0,7}, {3,6}, {2,5}, {1,6}, {0,7}, {1,6}},
    {{2,3}, {1,6}, {0,7}, {0,5}, {1,3}, {4,6}, {0,7}, {2,4}, {3,7}, {4,5}, {2,5}, {1,6}},
    {{3,5}, {6,5}/* 3 */, {1,2}, {2,7}, {2,3}, {5,6}, {2,3}, {0,5}, {2,7}, {0,1}, {2,5}, {0,6}},
    {{2,4}, {3,4}, {4,7}, {4,7}, {1,2}, {4,7}, {3,4}, {4,7}, {4,7}, {4,7}, {1,2}, {7,1}/* 2 */},
    {{2,3}/* 4 */, {1,3}, {0,1}, {0,3}, {0,2}, {0,3}, {1,3}, {0,3}, {0,1}, {3,0}/* 1 */, {0,2}, {0,1}}
};

static const std::map <Grid, const std::vector <std::vector <std::vector <unsigned int>>> &> m =
{
    {{6,6}, Grid66},
    {{8,6}, Grid86},
    {{8,8}, Grid88},
    {{10,8}, Grid10_8},
    {{10,10}, Grid10_10},
    {{12,10}, Grid12_10}
};

static Point nextPoint(int n, Point pos, Point lastPos)
{
    Grid grid;
    Point point;
    JunctionalAngleType jat;
    std::tie(grid, point, jat) = localize(n, pos);

    bool flag = false;

    if(grid.first < grid.second)
    {
        int t = grid.first;
        grid.first = grid.second;
        grid.second = t;

        t = point.first;
        point.first = point.second;
        point.second = t;

        flag = true;
    }

    const std::vector <unsigned int> &v = m.at(grid)[point.second][point.first];

    unsigned int h0 = v[0];
    unsigned int h1 = v[1];

    if(flag)
    {
        h0 = (9-h0)%8;
        h1 = (9-h1)%8;
    }

    switch(jat)
    {
        case 0: break;
        case 1:
        {
            if(h0 == 3) h0 = 4;
            else if(h1 == 3) h1 = 4;
            else assert(0);
            break;
        }
        case 2:
        {
            if(h0 == 7) h0 = 3;
            else if(h1 == 7) h1 = 3;
            else assert(0);
            break;
        }
        case 3:
        {
            if(h0 == 6) h0 = 7;
            else if(h1 == 6) h1 = 7;
            else assert(0);
            break;
        }
        case 4:
        {
            if(h0 == 2) h0 = 4;
            else if(h1 == 2) h1 = 4;
            else assert(0);
            break;
        }
        case 5:
        {
            if(h0 == 7) h0 = 0;
            else if(h1 == 7) h1 = 0;
            else assert(0);
            break;
        }
        case 6:
        {
            if(h0 == 3) h0 = 7;
            else if(h1 == 3) h1 = 7;
            else assert(0);
            break;
        }
        case 7:
        {
            if(h0 == 2) h0 = 3;
            else if(h1 == 2) h1 = 3;
            else assert(0);
            break;
        }
        case 8:
        {
            if(h0 == 6) h0 = 0;
            else if(h1 == 6) h1 = 0;
            else assert(0);
            break;
        }
        default: assert(0);
    }

    Offset o0 = d[h0];
    Offset o1 = d[h1];

    Point newpoint0 = std::make_pair(pos.first+o0.first, pos.second+o0.second);
    Point newpoint1 = std::make_pair(pos.first+o1.first, pos.second+o1.second);

    if(lastPos == newpoint0) return newpoint1;
    else if(lastPos == newpoint1) return newpoint0;
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
