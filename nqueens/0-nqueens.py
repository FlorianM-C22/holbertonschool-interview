#!/usr/bin/python3
"""Solves the N queens puzzle."""

import sys


def is_safe(board, row, col):
    """Return True if placing a queen at (row, col) is safe."""
    for r in range(row):
        c = board[r]
        if c == col or abs(r - row) == abs(c - col):
            return False
    return True


def solve(n, row, board, solutions):
    """Find all solutions using backtracking."""
    if row == n:
        solutions.append([[r, board[r]] for r in range(n)])
        return

    for col in range(n):
        if is_safe(board, row, col):
            board[row] = col
            solve(n, row + 1, board, solutions)


def main():
    """Parse arguments and print all N queens solutions."""
    if len(sys.argv) != 2:
        print("Usage: nqueens N")
        sys.exit(1)

    try:
        n = int(sys.argv[1])
    except ValueError:
        print("N must be a number")
        sys.exit(1)

    if n < 4:
        print("N must be at least 4")
        sys.exit(1)

    board = [-1] * n
    solutions = []
    solve(n, 0, board, solutions)

    for solution in solutions:
        print(solution)


if __name__ == "__main__":
    main()
