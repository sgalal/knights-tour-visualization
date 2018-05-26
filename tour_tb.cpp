#include <cassert>

#include "tour.h"

int main()
{
    auto x = nextPoint(6, 2, 0, 0, 1);
    assert(getFirst(x) == 4);
    assert(getSecond(x) == 1);
    assert(nextPoint(14, 7 ,3, 5, 4) == std::make_pair(8,1));
    assert(nextPoint(14, 4, 8, 6, 7) == std::make_pair(3,10));
    return 0;
}
