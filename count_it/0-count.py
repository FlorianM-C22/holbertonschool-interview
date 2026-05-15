#!/usr/bin/python3
"""Counts keyword occurrences in Reddit hot post titles."""

import requests


def count_words(subreddit, word_list, after=None, counts=None):
    """
    Query Reddit hot posts and print keyword counts.

    Args:
        subreddit: Name of the subreddit to query.
        word_list: List of keywords to count.
        after: Pagination token for recursive calls.
        counts: Running keyword counts for recursive calls.
    """
    if counts is None:
        counts = {}
        init_counts(word_list, counts, 0)

    headers = {"User-Agent": "0-count/1.0"}
    params = {"limit": 100}
    if after:
        params["after"] = after

    response = requests.get(
        "https://www.reddit.com/r/{}/hot.json".format(subreddit),
        headers=headers,
        params=params,
        allow_redirects=False,
    )
    if response.status_code != 200:
        return

    data = response.json()["data"]
    process_posts(data["children"], word_list, counts, 0)

    next_after = data["after"]
    if next_after:
        count_words(subreddit, word_list, next_after, counts)

    if after is None:
        print_results(counts)


def init_counts(word_list, counts, idx):
    """Initialize counts for each unique keyword."""
    if idx >= len(word_list):
        return

    word = word_list[idx].lower()
    if word not in counts:
        counts[word] = 0
    init_counts(word_list, counts, idx + 1)


def process_posts(children, word_list, counts, idx):
    """Process hot posts recursively."""
    if idx >= len(children):
        return

    count_title(children[idx]["data"]["title"], word_list, counts, 0)
    process_posts(children, word_list, counts, idx + 1)


def count_title(title, word_list, counts, idx):
    """Count keywords in a title recursively."""
    tokens = title.split()
    if idx >= len(tokens):
        return

    token = tokens[idx].lower()
    if token in counts:
        counts[token] += keyword_multiplier(word_list, token, 0)
    count_title(title, word_list, counts, idx + 1)


def keyword_multiplier(word_list, target, idx, total=0):
    """Return occurrences of target in word_list."""
    if idx >= len(word_list):
        return total

    if word_list[idx].lower() == target:
        total += 1
    return keyword_multiplier(word_list, target, idx + 1, total)


def print_results(counts):
    """Print keyword counts sorted by count then word."""
    words = sorted(
        counts.keys(),
        key=lambda word: (-counts[word], word),
    )
    print_words(words, counts, 0)


def print_words(words, counts, idx):
    """Print non-zero counts recursively."""
    if idx >= len(words):
        return

    word = words[idx]
    if counts[word] > 0:
        print("{}: {}".format(word, counts[word]))
    print_words(words, counts, idx + 1)
