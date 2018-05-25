#include <cassert>

#include "tour.h"

int main()
{
    auto x = nextPoint(6, make_point(2,0), make_point(0,1));
    assert(getFirst(x) == 4);
    assert(getSecond(x) == 1);
    assert(std::get <2> (localize(10, std::make_pair(0,1))) == 0);
    assert(std::get <2> (localize(14, std::make_pair(3,5))) == 1);
    assert(std::get <2> (localize(22, std::make_pair(9,10))) == 8);
    assert(std::get <2> (localize(14, std::make_pair(7,3))) == 3);
    assert(std::get <0> (localize(14, std::make_pair(7,3))) == std::make_pair(8,6));
    assert(std::get <1> (localize(14, std::make_pair(7,3))) == std::make_pair(1,3));
    assert(nextPoint(14, make_point(7,3), make_point(5,4)) == std::make_pair(8,1));
    assert(nextPoint(14, make_point(4,8), make_point(6,7)) == std::make_pair(3,10));
    return 0;
}
