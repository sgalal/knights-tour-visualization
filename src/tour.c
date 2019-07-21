#include <assert.h>
#include "tour.h"

#ifdef DEBUG
    #include <stdio.h>
#endif

#ifdef __cplusplus
    extern "C" {
#endif

/* Six pre-defined, closed, structured knight's tours. */

static const unsigned int Grid6_6[6][6][2] =
{
    {{4,5}, {5,6}, {4,7}, {4,7}, {5,7}, {6,7}},
    {{3,4}, {3,6}, {0,3}, {3,5}, {0,6}, {0,7}},
    {{2,5}, {1,4}, {0,1}, {3,4}, {2,5}, {1,6}},
    {{2,5}, {5,6}, {4,7}, {0,2}, {1,5}, {0,6}},
    {{3,4}, {1,4}, {4,7}, {4,7}, {0,2}, {1,7}},
    {{2,3}, {1,3}, {1,0}, {3,0}, {0,2}, {0,1}}
};

static const unsigned int Grid6_8[6][8][2] =
{
    {{4,5}, {4,6}, {4,7}, {4,7}, {4,6}, {4,6}, {5,7}, {6,7}},
    {{3,4}, {3,6}, {6,0}, {0,4}, {0,3}, {0,3}, {0,5}, {0,7}},
    {{2,5}, {1,4}, {0,5}, {2,5}, {2,5}, {0,3}, {2,5}, {1,6}},
    {{2,5}, {2,6}, {6,7}, {0,6}, {6,7}, {5,6}, {5,7}, {1,6}},
    {{3,4}, {1,4}, {3,7}, {1,4}, {1,3}, {1,4}, {2,7}, {1,7}},
    {{2,3}, {1,2}, {0,2}, {0,2}, {2,3}, {0,3}, {1,2}, {0,1}}
};

static const unsigned int Grid8_8[8][8][2] =
{
    {{4,5}, {5,6}, {5,7}, {4,7}, {5,7}, {4,7}, {5,7}, {6,7}},
    {{3,5}, {3,6}, {0,3}, {3,6}, {3,6}, {0,3}, {5,6}, {0,7}},
    {{2,5}, {1,6}, {1,7}, {1,5}, {4,5}, {1,3}, {2,5}, {1,6}},
    {{2,3}, {1,5}, {2,5}, {2,4}, {6,7}, {2,4}, {0,5}, {1,6}},
    {{2,5}, {1,6}, {3,7}, {4,5}, {1,6}, {0,1}, {2,5}, {0,1}},
    {{3,5}, {5,6}, {1,4}, {1,2}, {4,5}, {0,5}, {2,5}, {1,6}},
    {{2,4}, {1,4}, {4,7}, {2,7}, {0,1}, {4,7}, {0,7}, {1,7}},
    {{2,3}, {1,3}, {0,1}, {0,3}, {0,3}, {1,3}, {1,2}, {0,1}}
};

static const unsigned int Grid8_10[8][10][2] =
{
    {{4,5}, {4,6}, {4,7}, {4,7}, {4,7}, {6,7}, {4,7}, {4,7}, {5,7}, {6,7}},
    {{3,4}, {3,6}, {0,3}, {0,3}, {0,3}, {0,3}, {0,3}, {3,4}, {0,5}, {0,6}},
    {{2,4}, {1,6}, {0,6}, {6,7}, {2,4}, {4,6}, {5,7}, {5,6}, {2,5}, {0,1}},
    {{2,5}, {3,5}, {0,5}, {4,6}, {3,5}, {5,7}, {0,4}, {0,7}, {2,5}, {1,7}},
    {{2,5}, {2,6}, {2,7}, {3,5}, {2,4}, {0,3}, {2,7}, {1,3}, {0,1}, {1,6}},
    {{3,5}, {1,6}, {1,2}, {1,6}, {3,5}, {1,7}, {0,1}, {4,5}, {5,7}, {1,6}},
    {{2,4}, {1,4}, {4,7}, {3,7}, {1,4}, {4,7}, {3,7}, {4,7}, {2,7}, {0,7}},
    {{2,3}, {1,3}, {0,2}, {0,3}, {0,3}, {1,3}, {0,3}, {0,3}, {1,2}, {0,1}}
};

static const unsigned int Grid10_10[10][10][2] =
{
    {{4,5}, {4,6}, {5,7}, {4,6}, {4,7}, {6,7}, {5,7}, {4,7}, {5,7}, {6,7}},
    {{3,4}, {4,6}, {0,3}, {0,3}, {3,5}, {0,3}, {0,3}, {3,4}, {5,6}, {6,0}},
    {{2,4}, {1,6}, {0,2}, {0,1}, {2,4}, {6,7}, {5,6}, {1,6}, {2,5}, {0,1}},
    {{2,4}, {5,6}, {0,6}, {3,5}, {4,5}, {1,4}, {0,4}, {2,6}, {2,5}, {1,6}},
    {{2,5}, {4,5}, {0,7}, {4,5}, {2,6}, {2,5}, {0,2}, {0,1}, {0,6}, {1,6}},
    {{2,3}, {2,6}, {1,7}, {0,5}, {1,7}, {0,1}, {2,6}, {6,7}, {2,6}, {1,7}},
    {{3,5}, {1,6}, {1,3}, {2,7}, {1,5}, {3,7}, {1,7}, {2,3}, {2,5}, {6,7}},
    {{2,5}, {3,6}, {5,6}, {3,7}, {1,3}, {2,7}, {2,6}, {2,3}, {5,6}, {6,7}},
    {{2,4}, {1,3}, {4,7}, {3,4}, {4,7}, {1,7}, {4,7}, {3,4}, {2,7}, {1,7}},
    {{2,3}, {1,2}, {0,3}, {1,3}, {0,3}, {0,2}, {0,3}, {2,3}, {0,2}, {0,1}}
};

static const unsigned int Grid10_12[10][12][2] =
{
    {{4,5}, {4,6}, {6,7}, {4,7}, {5,6}, {4,7}, {5,7}, {4,7}, {4,6}, {4,7}, {5,6}, {6,7}},
    {{3,5}, {3,6}, {0,7}, {0,3}, {3,6}, {0,3}, {6,7}, {0,3}, {5,6}, {0,3}, {0,5}, {0,6}},
    {{2,3}, {1,2}, {6,7}, {2,6}, {3,4}, {1,7}, {5,6}, {1,2}, {5,7}, {2,4}, {2,5}, {1,6}},
    {{2,3}, {1,6}, {4,5}, {2,3}, {4,7}, {2,7}, {0,3}, {2,7}, {5,7}, {1,6}, {2,5}, {0,1}},
    {{4,5}, {2,6}, {2,3}, {3,5}, {0,4}, {2,3}, {0,3}, {1,7}, {4,6}, {1,7}, {2,5}, {1,6}},
    {{2,4}, {4,5}, {0,7}, {1,6}, {4,6}, {3,6}, {0,7}, {3,6}, {2,5}, {1,6}, {0,7}, {1,6}},
    {{2,3}, {1,6}, {0,7}, {0,5}, {1,3}, {4,6}, {0,7}, {2,4}, {3,7}, {4,5}, {2,5}, {1,6}},
    {{3,5}, {5,6}, {1,2}, {2,7}, {2,3}, {5,6}, {2,3}, {0,5}, {2,7}, {0,1}, {2,5}, {0,6}},
    {{2,4}, {3,4}, {4,7}, {4,7}, {1,2}, {4,7}, {3,4}, {4,7}, {4,7}, {4,7}, {1,2}, {1,7}},
    {{2,3}, {1,3}, {0,1}, {0,3}, {0,2}, {0,3}, {1,3}, {0,3}, {0,1}, {0,3}, {0,2}, {0,1}}
};

static const unsigned int offsetTypeOriginArr[8] = {3, 7, 6, 2, 7, 3, 2, 6};

static const unsigned int offsetTypeSubstituteArr[8] = {4, 3, 7, 4, 0, 7, 3, 0};

static const int offsetDirArr[8][2] =
    {{-2,-1}, {-1,-2}, {1,-2}, {2,-1}, {2, 1}, {1, 2}, {-1,2}, {-2,1}};

static void getPointGridAttribute
(
    /* input */
    unsigned int n, unsigned int x, unsigned int y,
    /* output */
    unsigned int *pointAttribute_p,
    unsigned int *gridSizeX_p, unsigned int *gridSizeY_p,
    unsigned int *gridLocX_p, unsigned int *gridLocY_p
)
{
    if (n < 12) {
        *pointAttribute_p = 8;  /* Normal point */
        *gridSizeX_p = n;
        *gridSizeY_p = n;
        *gridLocX_p = x;
        *gridLocY_p = y;
    } else {
        unsigned int gridSizeX = n, gridSizeY = n;
        unsigned int gridLocX = x, gridLocY = y;
        unsigned int blkChoiceX, blkChoiceY;

        *pointAttribute_p = 8;

        do {
            /* Process X */ {
                const unsigned int halve = gridSizeX / 2;
                const unsigned int mod_ = halve % 2;
                const unsigned int left = halve - mod_;
                const unsigned int right = halve + mod_;
                if (gridLocX < left) {
                    gridSizeX = left;
                    blkChoiceX = 1;
                } else {
                    gridSizeX = right;
                    gridLocX -= left;
                    blkChoiceX = 2;
                }
            }

            /* Process Y */ {
                const unsigned int halve = gridSizeY / 2;
                const unsigned int mod_ = halve % 2;
                const unsigned int left = halve - mod_;
                const unsigned int right = halve + mod_;
                if (gridLocY < left) {
                    gridSizeY = left;
                    blkChoiceY = 1;
                } else {
                    gridSizeY = right;
                    gridLocY -= left;
                    blkChoiceY = 2;
                }
            }

            *pointAttribute_p =
                blkChoiceX == 1 && blkChoiceY == 1 && gridLocX == gridSizeX - 3 && gridLocY == gridSizeY - 1 ? 0 :
                blkChoiceX == 1 && blkChoiceY == 1 && gridLocX == gridSizeX - 1 && gridLocY == gridSizeY - 2 ? 1 :
                blkChoiceX == 2 && blkChoiceY == 1 && gridLocX == 1             && gridLocY == gridSizeY - 3 ? 2 :
                blkChoiceX == 2 && blkChoiceY == 1 && gridLocX == 0             && gridLocY == gridSizeY - 1 ? 3 :
                blkChoiceX == 2 && blkChoiceY == 2 && gridLocX == 2             && gridLocY == 0             ? 4 :
                blkChoiceX == 2 && blkChoiceY == 2 && gridLocX == 0             && gridLocY == 1             ? 5 :
                blkChoiceX == 1 && blkChoiceY == 2 && gridLocX == gridSizeX - 2 && gridLocY == 2             ? 6 :
                blkChoiceX == 1 && blkChoiceY == 2 && gridLocX == gridSizeX - 1 && gridLocY == 0             ? 7 : *pointAttribute_p;
        } while (!((gridSizeX <= 12 && gridSizeY <= 12) && (gridSizeX < 12 || gridSizeY < 12)));

        *gridSizeX_p = gridSizeX;
        *gridSizeY_p = gridSizeY;
        *gridLocX_p = gridLocX;
        *gridLocY_p = gridLocY;
    }
}

static void getPossibleNextPointOffsetType
(
    /* input */
    unsigned int n, unsigned int x, unsigned int y,
    /* output */
    unsigned int *next_a_offsetType_p, unsigned int *next_b_offsetType_p
)
{
    unsigned int pointAttribute, gridSizeX, gridSizeY, gridLocX, gridLocY;
    getPointGridAttribute(n, x, y, &pointAttribute, &gridSizeX, &gridSizeY, &gridLocX, &gridLocY);

    const int shouldReverse = gridSizeX < gridSizeY;

    if (shouldReverse) {
        /* Swap gridSizeX and gridSizeY */ {
            const unsigned int t = gridSizeX;
            gridSizeX = gridSizeY;
            gridSizeY = t;
        }

        /* Swap gridSizeX and gridSizeY */ {
            const unsigned int t = gridLocX;
            gridLocX = gridLocY;
            gridLocY = t;
        }
    }

    const unsigned int *p;

    if (gridSizeX == 6 && gridSizeY == 6)
        p = Grid6_6[gridLocY][gridLocX];
    else if (gridSizeX == 8 && gridSizeY == 6)
        p = Grid6_8[gridLocY][gridLocX];
    else if (gridSizeX == 8 && gridSizeY == 8)
        p = Grid8_8[gridLocY][gridLocX];
    else if (gridSizeX == 10 && gridSizeY == 8)
        p = Grid8_10[gridLocY][gridLocX];
    else if (gridSizeX == 10 && gridSizeY == 10)
        p = Grid10_10[gridLocY][gridLocX];
    else if (gridSizeX == 12 && gridSizeY == 10)
        p = Grid10_12[gridLocY][gridLocX];
    else {  /* Grid size must always meet one of the designated grid sizes */
        #ifdef DEBUG
            fprintf(stderr, "Error: gridSizeX = %u, gridSizeY = %u\n"
                    "when (n,x,y) = (%u,%u,%u)\n", gridSizeX, gridSizeY, n, x, y);
        #endif
        assert(0);
        p = 0;
    }

    unsigned int next_a_offsetType = p[0];
    unsigned int next_b_offsetType = p[1];

    if (shouldReverse) {
        next_a_offsetType = (9 - next_a_offsetType) % 8;
        next_b_offsetType = (9 - next_b_offsetType) % 8;
    }

    if (pointAttribute != 8) {
        /* The point is not normal point, and the offset type should be substituted */
        unsigned int pathOrigin = offsetTypeOriginArr[pointAttribute];
        unsigned int pathSubstitute = offsetTypeSubstituteArr[pointAttribute];
        if (next_a_offsetType == pathOrigin)
            next_a_offsetType = pathSubstitute;
        else if (next_b_offsetType == pathOrigin)
            next_b_offsetType = pathSubstitute;
        else  /* pathOrigin must always be one of next_a_offsetType and next_b_offsetType */
            assert(0);
    }

    *next_a_offsetType_p = next_a_offsetType;
    *next_b_offsetType_p = next_b_offsetType;
}

static void getPossibleNextPoint
(
    /* input */
    unsigned int n, unsigned int x, unsigned int y,
    /* output */
    unsigned int *next_a_x_p, unsigned int *next_a_y_p,
    unsigned int *next_b_x_p, unsigned int *next_b_y_p
)
{
    unsigned int next_a_offsetType, next_b_offsetType;
    getPossibleNextPointOffsetType(n, x, y, &next_a_offsetType, &next_b_offsetType);

    const int *p_a = offsetDirArr[next_a_offsetType];
    const int *p_b = offsetDirArr[next_b_offsetType];

    *next_a_x_p = (unsigned int) ((int) x + p_a[0]);
    *next_a_y_p = (unsigned int) ((int) y + p_a[1]);
    *next_b_x_p = (unsigned int) ((int) x + p_b[0]);
    *next_b_y_p = (unsigned int) ((int) y + p_b[1]);
}

void getNextPoint
(
    /* input */
    unsigned int n, unsigned int x, unsigned int y,
    unsigned int last_x, unsigned int last_y,
    /* output */
    unsigned int *next_x_p, unsigned int *next_y_p
)
{
    unsigned int next_a_x, next_a_y, next_b_x, next_b_y;
    getPossibleNextPoint(n, x, y, &next_a_x, &next_a_y, &next_b_x, &next_b_y);

    if (next_a_x == last_x && next_a_y == last_y) {
        *next_x_p = next_b_x;
        *next_y_p = next_b_y;
    } else if (next_b_x == last_x && next_b_y == last_y) {
        *next_x_p = next_a_x;
        *next_y_p = next_a_y;
    } else {
        assert(0);
    }
}

static unsigned int pointSerialize(unsigned int n, unsigned int x, unsigned int y)
{
    return x * n + y;
}

unsigned int getNextPointSerialize
(
    unsigned int n, unsigned int x, unsigned int y,
    unsigned int last_x, unsigned int last_y
)
{
    unsigned int next_x, next_y;
    getNextPoint(n, x, y, last_x, last_y, &next_x, &next_y);

    return pointSerialize(n, next_x, next_y);
}

#ifdef __cplusplus
    }
#endif
