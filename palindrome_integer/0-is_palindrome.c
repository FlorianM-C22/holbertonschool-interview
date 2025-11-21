#include "palindrome.h"

/**
 * is_palindrome - Checks if an unsigned long integer is a palindrome.
 * @n: Number to check.
 *
 * Return: 1 if @n is a palindrome, otherwise 0.
 */
int is_palindrome(unsigned long n)
{
    unsigned long divisor = 1;
    unsigned long left_digit;
    unsigned long right_digit;

    while (n / divisor >= 10)
        divisor *= 10;

    while (n > 0)
    {
        left_digit = n / divisor;
        right_digit = n % 10;

        if (left_digit != right_digit)
            return (0);

        n = (n % divisor) / 10;
        divisor /= 100;
    }

    return (1);
}
