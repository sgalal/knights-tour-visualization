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
    return 0;
}
