#include <iostream>
#include "tour.h"

int main()
{
    auto x = nextPoint(6, make_point(2,0), make_point(0,1));
    std::cout << getFirst(x) << ' ' << getSecond(x) << std::endl;
    return 0;
}
