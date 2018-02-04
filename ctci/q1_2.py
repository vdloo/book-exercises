"""
A function that checks if a string is a permutation of another.
"""
from collections import defaultdict


def is_permutation_of(string1, string2):
    character_count = defaultdict(lambda: 0)
    for c in string2:
        character_count[c] += 1

    if len(string1) != len(string2):
        return False
    else:
        for c in string1:
            if character_count[c] == 0:
                return False
            character_count[c] -= 1
        return True
