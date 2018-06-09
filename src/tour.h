#pragma once

void getNextPoint
(
    /* input */
    unsigned int n, unsigned int x, unsigned int y,
    unsigned int last_x, unsigned int last_y,
    /* output */
    unsigned int *next_x_p, unsigned int *next_y_p
);

unsigned int getNextPointSerialize
(
    unsigned int n, unsigned int x, unsigned int y,
    unsigned int last_x, unsigned int last_y
);
