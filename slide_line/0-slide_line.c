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
    size_t i, pos;

    if (!line || (direction != SLIDE_LEFT && direction != SLIDE_RIGHT))
        return (0);

    if (direction == SLIDE_LEFT)
    {
        /* First merge identical numbers */
        for (i = 0; i < size - 1; i++)
        {
            if (line[i] != 0 && line[i] == line[i + 1])
            {
                line[i] *= 2;
                line[i + 1] = 0;
            }
        }

        /* Then compact non-zero numbers to the left */
        pos = 0;
        for (i = 0; i < size; i++)
        {
            if (line[i] != 0)
            {
                if (i != pos)
                {
                    line[pos] = line[i];
                    line[i] = 0;
                }
                pos++;
            }
        }
    }
    else /* SLIDE_RIGHT */
    {
        /* First merge identical numbers from right to left */
        for (i = size - 1; i > 0; i--)
        {
            if (line[i] != 0 && line[i] == line[i - 1])
            {
                line[i] *= 2;
                line[i - 1] = 0;
            }
        }

        /* Then compact non-zero numbers to the right */
        pos = size - 1;
        for (i = size; i > 0; i--)
        {
            if (line[i - 1] != 0)
            {
                if (i - 1 != pos)
                {
                    line[pos] = line[i - 1];
                    line[i - 1] = 0;
                }
                pos--;
            }
        }
    }

    return (1);
}
