#include <cassert>

#include "tour.h"

int main()
{
    auto x = nextPoint(6, make_point(2,0), make_point(0,1));
    assert(getFirst(x) == 4);
    assert(getSecond(x) == 1);
    assert(nextPoint(14, make_point(7,3), make_point(5,4)) == std::make_pair(8,1));
    assert(nextPoint(14, make_point(4,8), make_point(6,7)) == std::make_pair(3,10));
    return 0;
}
