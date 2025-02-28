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
        /* First compact non-zero numbers to the left */
        pos = 0;
        for (i = 0; i < size; i++)
        {
            if (line[i] != 0)
            {
                line[pos] = line[i];
                if (i != pos)
                    line[i] = 0;
                pos++;
            }
        }

        /* Then merge identical numbers */
        for (i = 0; i < size - 1; i++)
        {
            if (line[i] != 0 && line[i] == line[i + 1])
            {
                line[i] *= 2;
                /* Shift the rest of the numbers left */
                for (pos = i + 1; pos < size - 1; pos++)
                    line[pos] = line[pos + 1];
                line[size - 1] = 0;
            }
        }
    }
    else /* SLIDE_RIGHT */
    {
        /* First compact non-zero numbers to the right */
        pos = size - 1;
        for (i = size; i > 0; i--)
        {
            if (line[i - 1] != 0)
            {
                line[pos] = line[i - 1];
                if (i - 1 != pos)
                    line[i - 1] = 0;
                pos--;
            }
        }

        /* Then merge identical numbers */
        for (i = size - 1; i > 0; i--)
        {
            if (line[i] != 0 && line[i] == line[i - 1])
            {
                line[i] *= 2;
                /* Shift the rest of the numbers right */
                for (pos = i - 1; pos > 0; pos--)
                    line[pos] = line[pos - 1];
                line[0] = 0;
            }
        }
    }

    return (1);
}
