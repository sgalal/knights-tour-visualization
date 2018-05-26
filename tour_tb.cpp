#include <cassert>

#include "tour.h"

int main()
{
    Point x = nextPoint(6, 2, 0, 0, 1);
    assert(getFirst(x) == 4);
    assert(getSecond(x) == 1);
    assert(nextPoint(14, 7 ,3, 5, 4) == std::make_pair(8, 1));
    assert(nextPoint(14, 4, 8, 6, 7) == std::make_pair(3, 10));
    assert(nextPoint(68, 9, 11, 8, 9) == std::make_pair(10, 13));

    {
        int posX = 2;
        int posY = 0;
        int lastPosX = 0;
        int lastPosY = 1;
        for(;;)
        {
            Point p = nextPoint(999, posX, posY, lastPosX, lastPosY);
            if(p == std::make_pair(0, 1)) break;
            lastPosX = posX;
            lastPosY = posY;
            posX = p.first;
            posY = p.second;
        }
    }
    return 0;
}
