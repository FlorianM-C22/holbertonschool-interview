#!/usr/bin/python3
"""
Log parsing script computing cumulative file size and status code counts.
"""
import sys


def print_stats(total_size, status_counts):
    """Print aggregated file size and status code metrics."""
    print("File size: {}".format(total_size))
    for code in sorted(status_counts.keys()):
        if status_counts[code] > 0:
            print("{}: {}".format(code, status_counts[code]))


def main():
    """Read stdin line by line and compute metrics."""
    valid_status_codes = [200, 301, 400, 401, 403, 404, 405, 500]
    status_counts = {code: 0 for code in valid_status_codes}
    total_size = 0
    line_counter = 0

    try:
        for line in sys.stdin:
            parts = line.split()
            if len(parts) < 7:
                continue

            status_str = parts[-2]
            size_str = parts[-1]

            try:
                size = int(size_str)
            except (ValueError, TypeError):
                continue

            total_size += size

            try:
                status = int(status_str)
            except (ValueError, TypeError):
                status = None

            if status in status_counts:
                status_counts[status] += 1

            line_counter += 1
            if line_counter % 10 == 0:
                print_stats(total_size, status_counts)
    except KeyboardInterrupt:
        print_stats(total_size, status_counts)
        raise
    else:
        print_stats(total_size, status_counts)


if __name__ == "__main__":
    main()
