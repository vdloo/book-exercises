from tempfile import NamedTemporaryFile
from subprocess import Popen, check_call, PIPE
from unittest import TestCase


class TestExercise124(TestCase):
    @staticmethod
    def run_against_text(text):
        with NamedTemporaryFile() as fh:
            fh.write(text)
            fh.flush()
            command = 'cat {} | ./a.out'.format(fh.name)
            process = Popen(command, shell=True, stdout=PIPE, stderr=PIPE)
            standard_out, standard_error = process.communicate()
            exit_code = process.returncode
        return standard_out, standard_error, exit_code

    def setUp(self):
        print("Compiling 1.24")
        check_call(['gcc', '1.24.c'])

    def test_detect_syntax_errors(self):
        print('Testing if valid C file returns OK')
        code = """
#include <stdio.h>
int main(void)
{
    /* Simple state machine for parsing multi-line comments from C code */
    return 0;
}
        """
        standard_out_output, standard_error_output, exit_code = self.run_against_text(code)

        expected_output = 'It all looks ok!\n'
        self.assertEqual(standard_out_output, expected_output)

        print('Testing if a missing closing parenthesis is detected')
        code = """
#include <stdio.h>
int main(void)
{
    /* Simple state machine for parsing multi-line comments from C code */
    int a = (a +;
    return 0;
}
        """
        standard_out_output, standard_error_output, exit_code = self.run_against_text(code)

        expected_output = 'Expected to be exiting state curly braces but was actually exiting parenthesis at line 8\n'
        self.assertEqual(standard_error_output, expected_output)

        print('Testing if a missing closing bracket is detected')
        code = """
#include <stdio.h>
int main(void)
{
    /* Simple state machine for parsing multi-line comments from C code */
    int a[0 = 2;
    return 0;
}
        """
        standard_out_output, standard_error_output, exit_code = self.run_against_text(code)

        expected_output = 'Expected to be exiting state curly braces but was actually exiting brackets at line 8\n'
        self.assertEqual(standard_error_output, expected_output)

        print('Testing if a missing closing curly is detected')
        code = """
#include <stdio.h>
int main(void)
{
    /* Simple state machine for parsing multi-line comments from C code */
    int a;
    if (1 == 1) {
        a = 2;
}
        """
        standard_out_output, standard_error_output, exit_code = self.run_against_text(code)

        expected_output = 'Unbalanced curly braces at line 4\n'
        self.assertEqual(standard_error_output, expected_output)

        print('Testing if a missing opening parenthesis is detected')
        code = """
#include <stdio.h>
int main(void)
{
    /* Simple state machine for parsing multi-line comments from C code */
    int a = a + 2);
    return 0;
}
        """
        standard_out_output, standard_error_output, exit_code = self.run_against_text(code)

        expected_output = 'Expected to be exiting state parenthesis but was actually exiting curly braces at line 6\n'
        self.assertEqual(standard_error_output, expected_output)

        print('Testing if a missing opening bracket is detected')
        code = """
#include <stdio.h>
int main(void)
{
    /* Simple state machine for parsing multi-line comments from C code */
    int a2] = 2;
    return 0;
}
        """
        standard_out_output, standard_error_output, exit_code = self.run_against_text(code)

        expected_output = 'Expected to be exiting state brackets but was actually exiting curly braces at line 6\n'
        self.assertEqual(standard_error_output, expected_output)

        print('Testing if a missing opening curly is detected')
        code = """
#include <stdio.h>
int main(void)
{
    /* Simple state machine for parsing multi-line comments from C code */
    int a;
    if (1 == 1)
        a = 2;
    }
    return 0;
}
        """
        standard_out_output, standard_error_output, exit_code = self.run_against_text(code)

        expected_output = 'Expected to be exiting state curly braces but was actually exiting normal text at line 11\n'
        self.assertEqual(standard_error_output, expected_output)

        print('Testing if an unclosed comment is detected')
        code = """
#include <stdio.h>
int main(void)
{
    /* Simple state machine for parsing multi-line comments from C code
    return 0;
}
        """
        standard_out_output, standard_error_output, exit_code = self.run_against_text(code)

        expected_output = 'Unbalanced comment at line 5\n'
        self.assertEqual(standard_error_output, expected_output)

        print('Testing if unopened single quotes are detected')
        code = """
#include <stdio.h>
int main(void)
{
    /* Simple state machine for parsing multi-line comments from C code */
    char a = a';
    return 0;
}
        """
        standard_out_output, standard_error_output, exit_code = self.run_against_text(code)

        expected_output = 'Unbalanced single quotes at line 6\n'
        self.assertEqual(standard_error_output, expected_output)

        print('Testing if unclosed double quotes are detected')
        code = """
#include <stdio.h>
int main(void)
{
    /* Simple state machine for parsing multi-line comments from C code */
    char *a = "abc;
    return 0;
}
        """
        standard_out_output, standard_error_output, exit_code = self.run_against_text(code)

        expected_output = 'Unbalanced double quotes at line 6\n'
        self.assertEqual(standard_error_output, expected_output)

        print('Testing if unopened double quotes are detected')
        code = """
#include <stdio.h>
int main(void)
{
    /* Simple state machine for parsing multi-line comments from C code */
    char *a = abc";
    return 0;
}
        """
        standard_out_output, standard_error_output, exit_code = self.run_against_text(code)

        expected_output = 'Unbalanced double quotes at line 6\n'
        self.assertEqual(standard_error_output, expected_output)
