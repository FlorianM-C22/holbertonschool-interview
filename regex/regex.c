#include "regex.h"

/**
 * regex_match - Checks whether a given pattern matches a given string
 * @str: The string to scan
 * @pattern: The regular expression
 *
 * Return: 1 if the pattern matches the string, 0 if it doesn't
 */
int regex_match(char const *str, char const *pattern)
{
    /* Base cases */
    if (!pattern || !*pattern)
        return (!str || !*str);

    if (!str)
        return 0;

    /* Check if next character is '*' */
    if (*(pattern + 1) == '*')
    {
        /* Try matching zero occurrences of the current character */
        if (regex_match(str, pattern + 2))
            return (1);

        /* Try matching one or more occurrences */
        if (*str && (*pattern == '.' || *str == *pattern))
            return (regex_match(str + 1, pattern));

        return (0);
    }

    /* Current character must match */
    if (*pattern == '.' || *str == *pattern)
        return (regex_match(str + 1, pattern + 1));

    return (0);
}
