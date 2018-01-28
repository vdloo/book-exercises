from ctci.q1_1 import all_unique_characters
from ctci.testcase import TestCase


class Test1_1_AllUniqueCharacters(TestCase):
    def test_all_unique_characters_returns_false_if_not_all_unique(self):
        ret = all_unique_characters("abcdeefghij")

        self.assertFalse(ret)

    def test_all_unique_characters_returns_true_if_all_unique(self):
        ret = all_unique_characters("abcdefghij")

        self.assertTrue(ret)
