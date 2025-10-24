#ifndef REGEX_H
#define REGEX_H

/**
 * regex_match - Checks whether a given pattern matches a given string
 * @str: The string to scan
 * @pattern: The regular expression
 *
 * Return: 1 if the pattern matches the string, 0 if it doesn't
 */
int regex_match(char const *str, char const *pattern);

#endif /* REGEX_H */
