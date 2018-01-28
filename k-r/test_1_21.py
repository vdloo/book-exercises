from subprocess import check_call, check_output
from unittest import TestCase


class TestExercise121(TestCase):
    def setUp(self):
        print("Compiling 1.21")
        check_call(['gcc', '1.21.c'])

    def test_entab(self):
        print('Testing if "abc\td" stays "abc\td" in case of tabstop 4')
        output = check_output('/bin/echo -e "abc\td" | ./a.out', shell=True)
        self.assertEqual(output, "abc\td\n")

        print('Testing if "ab.\td" expands to "ab\td" in case of tabstop 4')
        output = check_output('/bin/echo -e "ab \td" | ./a.out', shell=True)
        self.assertEqual(output, "ab\td\n")

        print('Testing if "a..\td" expands to "a\td" in case of tabstop 4')
        output = check_output('/bin/echo -e "a  \td" | ./a.out', shell=True)
        self.assertEqual(output, "a\td\n")

        print('Testing if "abcd..ef" stays "abcd..ef" in case of tabstop 4')
        output = check_output('/bin/echo -e "abcd  ef" | ./a.out', shell=True)
        self.assertEqual(output, "abcd  ef\n")

        print('Testing if "abcd....ef" expands to "abcd\tef" in case of tabstop 4')
        output = check_output('/bin/echo -e "abcd    ef" | ./a.out', shell=True)
        self.assertEqual(output, "abcd\tef\n")

