#pragma once

/// Determine the next point by current point and last point.
/// @param n (Input) Size of the board, which must satisfy n ≥ 6 and n is even.
/// @param x (Input) x-coordinate of current point.
/// @param y (Input) y-coordinate of current point.
/// @param last_x (Input) x-coordinate of last point.
/// @param last_y (Input) y-coordinate of last point.
/// @param next_x_p (Output) Pointer to x-coordinate of next point.
/// @param next_y_p (Output) Pointer to y-coordinate of next point.
void getNextPoint
(
    /* input */
    unsigned int n, unsigned int x, unsigned int y,
    unsigned int last_x, unsigned int last_y,
    /* output */
    unsigned int *next_x_p, unsigned int *next_y_p
);

/// Determine the next point by current point and last point. This function gives a
/// serialized output.
/// @param n Size of the board, which must satisfy n ≥ 6 and n is even.
/// @param x x-coordinate of current point.
/// @param y y-coordinate of current point.
/// @param last_x x-coordinate of last point.
/// @param last_y y-coordinate of last point.
/// @return Next point in a serialized form. Serialize(x, y) = x * n + y, where x and y
/// stand for the x-coordinate and y-coordinate of next point respectively.
unsigned int getNextPointSerialize
(
    unsigned int n, unsigned int x, unsigned int y,
    unsigned int last_x, unsigned int last_y
);
