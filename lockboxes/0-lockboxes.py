#!/usr/bin/python3
"""
Lockboxes Module

This module provides a function to determine if all boxes in a sequence
can be opened, given that each box may contain keys to other boxes.
"""


def canUnlockAll(boxes):
    """
    Determines if all boxes can be opened.

    Args:
        boxes: A list of lists where each inner list contains
              keys to other boxes

    Returns:
        True if all boxes can be opened, False otherwise
    """
    if not boxes:
        return False

    n = len(boxes)
    visited = [False] * n
    visited[0] = True  # First box is unlocked
    queue = [0]  # Start with the first box

    while queue:
        current_box = queue.pop(0)
        # Check all keys in the current box
        for key in boxes[current_box]:
            # If the key is valid and the box hasn't been visited
            if 0 <= key < n and not visited[key]:
                visited[key] = True
                queue.append(key)

    # Check if all boxes were visited
    return all(visited)
