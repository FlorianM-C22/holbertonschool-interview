#include "slide_line.h"

/**
 * slide_line - Slides and merges an array of integers
 * @line: Points to an array of integers
 * @size: Number of elements in @line
 * @direction: SLIDE_LEFT or SLIDE_RIGHT
 * Return: 1 upon success, 0 upon failure
 */
int slide_line(int *line, size_t size, int direction)
{
    size_t i, j, write_idx;

    /* Check if direction is valid */
    if (direction != SLIDE_LEFT && direction != SLIDE_RIGHT)
        return (0);

    /* Handle sliding left */
    if (direction == SLIDE_LEFT)
    {
        /* First pass: compress numbers to the left */
        write_idx = 0;
        for (i = 0; i < size; i++)
        {
            if (line[i] != 0)
                line[write_idx++] = line[i];
        }
        /* Fill remaining positions with zeros */
        for (i = write_idx; i < size; i++)
            line[i] = 0;

        /* Second pass: merge identical numbers */
        for (i = 0; i < size - 1; i++)
        {
            if (line[i] != 0 && line[i] == line[i + 1])
            {
                line[i] *= 2;
                line[i + 1] = 0;
                /* Shift remaining numbers left */
                for (j = i + 2; j < size; j++)
                {
                    line[j - 1] = line[j];
                }
                line[size - 1] = 0;
            }
        }
    }
    /* Handle sliding right */
    else
    {
        /* First pass: compress numbers to the right */
        write_idx = size - 1;
        for (i = size; i > 0; i--)
        {
            if (line[i - 1] != 0)
                line[write_idx--] = line[i - 1];
        }
        /* Fill remaining positions with zeros */
        for (i = 0; i <= write_idx; i++)
            line[i] = 0;

        /* Second pass: merge identical numbers */
        for (i = size - 1; i > 0; i--)
        {
            if (line[i] != 0 && line[i] == line[i - 1])
            {
                line[i] *= 2;
                line[i - 1] = 0;
                /* Shift remaining numbers right */
                for (j = i - 1; j > 0; j--)
                {
                    line[j] = line[j - 1];
                }
                line[0] = 0;
            }
        }
    }

    return (1);
}
