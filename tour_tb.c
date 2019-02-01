#include <assert.h>
#include "tour.h"

#ifdef DEBUG
    #include <stdio.h>
#endif

int main()
{
#ifndef DEBUG
    #error This file should be compiled with DEBUG macro.
#else
    /* Test 1 */
    {
        unsigned int next_x, next_y;
        getNextPoint(6, 2, 0, 0, 1, &next_x, &next_y);
        assert(next_x == 4 && next_y == 1);
    }

    /* Test 2 */
    {
        unsigned int next_x, next_y;
        getNextPoint(14, 7 ,3, 5, 4, &next_x, &next_y);
        assert(next_x == 8 && next_y == 1);
    }

    /* Test 3 */
    {
        unsigned int next_x, next_y;
        getNextPoint(14, 4, 8, 6, 7, &next_x, &next_y);
        assert(next_x == 3 && next_y == 10);
    }

    /* Test 4 */
    {
        unsigned int next_x, next_y;
        getNextPoint(68, 9, 11, 8, 9, &next_x, &next_y);
        assert(next_x == 10 && next_y == 13);
    }

    /* Test 5 */
    {
        const unsigned int n = 42;
        unsigned int pos_x = 2, pos_y = 0;
        unsigned int last_pos_x = 0, last_pos_y = 1;
        unsigned int i = n * n;
        unsigned int next_x, next_y;

        do {
            getNextPoint(n, pos_x, pos_y, last_pos_x, last_pos_y, &next_x, &next_y);
            last_pos_x = pos_x;
            last_pos_y = pos_y;
            pos_x = next_x;
            pos_y = next_y;
        } while (--i);

        if (!(next_x == 2 && next_y == 0)) {
            fprintf(stderr, "Error: next_x = %u, next_y = %u\n", next_x, next_y);
            assert(0);
        }
    }
#endif
    return 0;
}
