## Requirements

### General

- Allowed editors: `vi`, `vim`, `emacs`
- All your files will be compiled on Ubuntu 14.04 LTS
- Your programs and functions will be compiled with `gcc 4.8.4` using the flags `-Wall` `-Werror` `-Wextra` `and -pedantic`
- All your files should end with a new line
- Your code should use the `Betty` style. It will be checked using [betty-style.pl](https://github.com/hs-hq/Betty/blob/master/betty-style.pl 'betty-style.pl') and [betty-doc.pl](https://github.com/hs-hq/Betty/blob/master/betty-doc.pl 'betty-doc.pl')
- You are not allowed to use global variables
- No more than 5 functions per file
- In the following examples, the `main.c` files are shown as examples. You can use them to test your functions, but you don’t have to push them to your repo (if you do we won’t take them into account). We will use our own `main.c` files at compilation. Our `main.c` files might be different from the one shown in the examples
- The prototypes of all your functions should be included in your header file called `slide_line.h`
- Don’t forget to push your header file
- All your header files should be include guarded

## Tasks

### 1.

The goal of this task is to reproduce the [2048 game](/rltoken/i7Nqad-fVtT6e4qtMUtArw '2048 game')(NSFW !!) mechanics on a single horizontal line.

Given an array of integers, we want to be able to slide & merge it to the left or to the right. Identical numbers, if they are contiguous or separated by zeros, should be merged (See example)

- Write a function that slides and merges an array of integers
- Prototype: `int slide_line(int *line, size_t size, int direction);`
- Where `line` points to an array of integers containing `size` elements, that must be slided & merged to the direction represented by `direction`. `direction` can be either:
  - `SLIDE_LEFT`
  - `SLIDE_RIGHT`
  - If it is something else, the function must fail
  - Both macros `SLIDE_LEFT` and `SLIDE_RIGHT` must be defined in `slide_line.h`
- Your function must return `1` upon success, or `0` upon failure
- You are **not allowed** to allocate memory dynamically (malloc, calloc, …)

```
alex@~/slide\_line$ cat 0-main.c
#include <stdlib.h>
#include <stdio.h>

#include "slide\_line.h"

#define LINE\_SIZE   32

/\*\*
 \* print\_array - Prints out an array of integer, followed by a new line
 \*
 \* @array: Pointer to the array of integer to be printed
 \* @size: Number of elements in @array
 \*/
static void print\_array(int const \*array, size\_t size)
{
    size\_t i;

    printf("Line: ");
    for (i = 0; i < size; i++)
        printf("%s%d", i > 0 ? ", " : "", array\[i\]);
    printf("\\n");
}

/\*\*
 \* main - Entry point
 \*
 \* @ac: Arguments counter
 \* @av: Arguments vector
 \*
 \* Return: EXIT\_SUCCESS or EXIT\_FAILURE
 \*/
int main(int ac, char \*\*av)
{
    int line\[LINE\_SIZE\];
    int direction;
    size\_t i, size;

    if (ac < 3)
    {
        fprintf(stderr, "Usage: %s <R/L> <n1> \[n2...\]\\n", av\[0\]);
        return (EXIT\_FAILURE);
    }

    /\* Command line arguments to array of int \*/
    size = ac - 2;
    if (size > LINE\_SIZE)
        size = LINE\_SIZE;
    for (i = 0; i < size; i++)
        line\[i\] = atoi(av\[i + 2\]);

    /\* Print the array \*/
    print\_array(line, size);

    /\* Parse direction \*/
    switch (\*(av\[1\]))
    {
    case 'L':
        direction = SLIDE\_LEFT;
        printf("Slide to the left\\n");
        break;
    case 'R':
        direction = SLIDE\_RIGHT;
        printf("Slide to the right\\n");
        break;
    default:
        fprintf(stderr, "Unknown direction '%c'. Please use 'L' or 'R'", \*(av\[1\]));
        return (EXIT\_FAILURE);
    }

    /\* Slide and merge \*/
    if (!slide\_line(line, size, direction))
    {
        fprintf(stderr, "Failed to slide and merge line\\n");
        return (EXIT\_FAILURE);
    }

    /\* Print the array \*/
    print\_array(line, size);

    return (EXIT\_SUCCESS);
}
alex@~/slide\_line$ gcc -Wall -Wextra -Werror -pedantic -o 0-slide\_line 0-main.c 0-slide\_line.c
alex@~/slide\_line$ ./0-slide\_line L 2 2 0 0
Line: 2, 2, 0, 0
Slide to the left
Line: 4, 0, 0, 0
alex@~/slide\_line$ ./0-slide\_line L 2 2 0 0 0 0 0 2 0 0 0 2 0 4
Line: 2, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 4
Slide to the left
Line: 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
alex@~/slide\_line$ ./0-slide\_line R 2 2 2 2
Line: 2, 2, 2, 2
Slide to the right
Line: 0, 0, 4, 4
alex@~/slide\_line$ ./0-slide\_line R 2 2 2 2 2
Line: 2, 2, 2, 2, 2
Slide to the right
Line: 0, 0, 2, 4, 4
alex@~/slide\_line$ ./0-slide\_line L 2 4 8 16
Line: 2, 4, 8, 16
Slide to the left
Line: 2, 4, 8, 16
alex@~/slide\_line$ ./0-slide\_line R 2 4 8 16
Line: 2, 4, 8, 16
Slide to the right
Line: 2, 4, 8, 16
alex@~/slide\_line$ ./0-slide\_line R 4 4 8 16
Line: 4, 4, 8, 16
Slide to the right
Line: 0, 8, 8, 16
alex@~/slide\_line$
```
