from subprocess import check_call, check_output
from unittest import TestCase


class TestExercise122(TestCase):
    def setUp(self):
        print("Compiling 1.22")
        check_call(['gcc', '1.22.c'])

    def test_wrap(self):
        print('Testing if "\t\t\t\t\tblabla" becomes "\nblablabla" in case of tabstop 20')
        output = check_output('/bin/echo -e "\t\t\t\t\tblablabla" | ./a.out', shell=True)
        self.assertEqual(output, "\nblablabla\n")

        print('Testing if "abc\tdefg\t\t\t\tblabla" becomes "abcd\tdefg\nblablabla" in case of tabstop 20')
        output = check_output('/bin/echo -e "abc\tdefg\t\t\t\t\tblablabla" | ./a.out', shell=True)
        self.assertEqual(output, "abc\tdefg\nblablabla\n")

        print('Testing if "12345678912345678912345" becomes "1234567891234567891-\n2345" in case of tabstop 20')
        output = check_output('/bin/echo -e "12345678912345678912345" | ./a.out', shell=True)
        self.assertEqual(output, "1234567891234567891-\n2345\n")

        print('Testing if "this is a very long sentence" becomes "this is a very long\nsentence" in case of tabstop 20')
        output = check_output('/bin/echo -e "this is a very long sentence" | ./a.out', shell=True)
        self.assertEqual(output, "this is a very long\nsentence\n")

        print('Testing if "blabla" stays "blablabla" in case of tabstop 20')
        output = check_output('/bin/echo -e "blablabla" | ./a.out', shell=True)
        self.assertEqual(output, "blablabla\n")

