#!/usr/bin/python3
"""
This module provides a function to calculate the minimum number of operations
needed to get exactly n H characters in a text file using only Copy All and
Paste operations.
"""


def minOperations(n):
    """
    Calculates the minimum number of operations needed to get exactly n H
    characters.

    Args:
        n (int): The target number of H characters

    Returns:
        int: The minimum number of operations needed, or 0 if n is impossible
        to achieve
    """
    if n <= 1:
        return 0

    operations = 0
    divisor = 2

    while n > 1:
        while n % divisor == 0:
            operations += divisor
            n = n // divisor
        divisor += 1

    return operations
