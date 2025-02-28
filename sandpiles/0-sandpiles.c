#include <stdlib.h>
#include <stdio.h>

/**
 * print_grid - Print 3x3 grid
 * @grid: 3x3 grid
 */
static void print_grid(int grid[3][3])
{
    int i, j;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (j)
                printf(" ");
            printf("%d", grid[i][j]);
        }
        printf("\n");
    }
}

/**
 * is_stable - Check if grid is stable
 * @grid: 3x3 grid
 * Return: 1 if stable, 0 if not
 */
static int is_stable(int grid[3][3])
{
    int i, j;

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            if (grid[i][j] > 3)
                return (0);
    return (1);
}

/**
 * topple - Perform one round of toppling on unstable cells
 * @grid: 3x3 grid to topple
 */
static void topple(int grid[3][3])
{
    int i, j;
    int tmp[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

    /* Copy current state to tmp */
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            tmp[i][j] = grid[i][j];

    /* Process toppling */
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (tmp[i][j] > 3)
            {
                grid[i][j] -= 4;
                if (i + 1 < 3)
                    grid[i + 1][j] += 1;
                if (i - 1 >= 0)
                    grid[i - 1][j] += 1;
                if (j + 1 < 3)
                    grid[i][j + 1] += 1;
                if (j - 1 >= 0)
                    grid[i][j - 1] += 1;
            }
        }
    }
}

/**
 * sandpiles_sum - Compute the sum of two sandpiles
 * @grid1: First 3x3 grid
 * @grid2: Second 3x3 grid
 */
void sandpiles_sum(int grid1[3][3], int grid2[3][3])
{
    int i, j;

    /* Add grid2 to grid1 */
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            grid1[i][j] += grid2[i][j];

    /* Keep toppling until stable */
    while (!is_stable(grid1))
    {
        printf("=\n");
        print_grid(grid1);
        topple(grid1);
    }
}
