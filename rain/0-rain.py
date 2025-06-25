#!/usr/bin/python3
"""
Rain water trapping algorithm.
Given a list of wall heights, calculate how much water can be retained.
"""


def rain(walls):
    """
    Calculate the total amount of rainwater retained between walls.

    Args:
        walls: List of non-negative integers representing wall heights

    Returns:
        Integer indicating total amount of rainwater retained
    """
    if not walls:
        return 0

    n = len(walls)
    if n < 3:
        return 0  # Need at least 3 walls to trap water

    # Arrays to store the maximum height to the left and right of each position
    left_max = [0] * n
    right_max = [0] * n

    # Fill left_max array
    left_max[0] = walls[0]
    for i in range(1, n):
        left_max[i] = max(left_max[i-1], walls[i])

    # Fill right_max array
    right_max[n-1] = walls[n-1]
    for i in range(n-2, -1, -1):
        right_max[i] = max(right_max[i+1], walls[i])

    # Calculate water trapped at each position
    total_water = 0
    for i in range(n):
        # Water trapped at position i is the minimum of left and right max
        # minus the height of the wall at position i
        water_at_position = min(left_max[i], right_max[i]) - walls[i]
        if water_at_position > 0:
            total_water += water_at_position

    return total_water
