from ctci.q1_2 import is_permutation_of
from ctci.testcase import TestCase


class Test1_2_IsPermutationOf(TestCase):
    def test_is_permutation_of_returns_false_if_not_permutation(self):
        ret = is_permutation_of("abcde", "fghij")

        self.assertFalse(ret)

    def test_is_permutation_of_returns_true_if_the_same(self):
        ret = is_permutation_of("abcde", "abcde")

        self.assertTrue(ret)

    def test_is_permutation_of_returns_true_if_reversed(self):
        ret = is_permutation_of("abcde", "edcba")

        self.assertTrue(ret)

    def test_is_permutation_of_returns_true_if_other_permutation(self):
        ret = is_permutation_of("abcde", "ebcda")

        self.assertTrue(ret)

    def test_is_permutation_of_returns_false_if_too_long(self):
        ret = is_permutation_of("abcdef", "abcde")

        self.assertFalse(ret)

    def test_is_permutation_of_returns_false_if_too_short(self):
        ret = is_permutation_of("abcd", "abcde")

        self.assertFalse(ret)

    def test_is_permutation_of_returns_false_if_other_double_chars(self):
        ret = is_permutation_of("abcdee", "aabcde")

        self.assertFalse(ret)
