#include <stdio.h>
#include <math.h>
#include "menger.h"

/**
 * menger - Draws a 2D Menger Sponge
 * @level: The level of the Menger Sponge to draw
 *
 * If level is lower than 0, the function does nothing.
 * A level N sponge is a 3x3 square of level N-1 sponges,
 * except for the center one, which is left empty.
 * A level 0 sponge is represented by the # character.
 */
void menger(int level)
{
    if (level < 0)
        return;

    int size = (int)pow(3, level);

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            int x = i;
            int y = j;
            int should_fill = 1;

            for (int l = level; l > 0; l--)
            {
                int block_size = (int)pow(3, l - 1);
                int x_block = x / block_size;
                int y_block = y / block_size;

                if (x_block == 1 && y_block == 1)
                {
                    should_fill = 0;
                    break;
                }

                x = x % block_size;
                y = y % block_size;
            }

            if (should_fill)
                printf("#");
            else
                printf(" ");
        }
        printf("\n");
    }
}

