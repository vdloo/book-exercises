"""
An algorithm that determines if a string has all unique characters
and you can not use an additional data structure
"""
from functools import reduce


def all_unique_characters(string):
    return reduce(
        lambda p, n: p if n in p else p + n, string
    ) == string

