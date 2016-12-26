from tempfile import NamedTemporaryFile
from subprocess import check_call, check_output
from unittest import TestCase


class TestExercise123(TestCase):
    @staticmethod
    def run_against_text(text):
        with NamedTemporaryFile() as fh:
            fh.write(text)
            fh.flush()
            output = check_output(
                'cat {} | ./a.out'.format(fh.name), shell=True
            )
        return output

    def setUp(self):
        print("Compiling 1.23")
        check_call(['gcc', '1.23.c'])

    def test_remove_comments(self):
        print('Testing if single-line comment is removed')
        code = """
#include <stdio.h>
int main(void)
{
    /* Simple state machine for parsing multi-line comments from C code */
    return 0;
}
        """
        expected_code = """
#include <stdio.h>
int main(void)
{
    
    return 0;
}
        """
        output = self.run_against_text(code)
        self.assertEqual(output, expected_code)

        print('Testing if multi-line comment is removed')
        code = """
#include <stdio.h>
int main(void)
{
    /* Simple state machine for parsing 
    * multi-line comments from C code */
    return 0;
}
        """
        expected_code = """
#include <stdio.h>
int main(void)
{
    
    return 0;
}
        """
        output = self.run_against_text(code)
        self.assertEqual(output, expected_code)

        print('Testing if comments in char arrays are not removed')
        code = """
#include <stdio.h>
int main(void)
{
    char *a = "text /* with a fake comment * / and more text";
    return 0;
}
        """
        output = self.run_against_text(code)
        self.assertEqual(output, code)

        print('Testing the double quote state is not entered from a comment')
        code = """
#include <stdio.h>
int main(void)
{
    /* Simple "state machine for parsing multi-line comments from C code */
    return 0;
}
        """
        expected_code = """
#include <stdio.h>
int main(void)
{
    
    return 0;
}
        """
        output = self.run_against_text(code)
        self.assertEqual(output, expected_code)

        print('Testing the single quote state is not entered from a comment')
        code = """
#include <stdio.h>
int main(void)
{
    /* Simple 'state machine for parsing multi-line comments from C code */
    return 0;
}
        """
        expected_code = """
#include <stdio.h>
int main(void)
{
    
    return 0;
}
        """
        output = self.run_against_text(code)
        self.assertEqual(output, expected_code)

        print('Testing the single quote state is not entered from a double')
        code = """
#include <stdio.h>
int main(void)
{
    char *a = "this' is a char array";
    /* Simple state machine for parsing multi-line comments from C code */
    return 0;
}
        """
        expected_code = """
#include <stdio.h>
int main(void)
{
    char *a = "this' is a char array";
    
    return 0;
}
        """
        output = self.run_against_text(code)
        self.assertEqual(output, expected_code)

        print('Testing the double quote state persists after escaped double')
        code = """
#include <stdio.h>
int main(void)
{
    char *a = "this\\" is a char array";
    /* Simple state machine for parsing multi-line comments from C code */
    return 0;
}
        """
        expected_code = """
#include <stdio.h>
int main(void)
{
    char *a = "this\\" is a char array";
    
    return 0;
}
        """
        output = self.run_against_text(code)
        self.assertEqual(output, expected_code)

        print('Testing the double quote state is not entered from a char constant')
        code = """
#include <stdio.h>
int main(void)
{
    /* this is a char constant double quote */
    char a = '"';
    /* Simple state machine for parsing multi-line comments from C code */
    return 0;
}
        """
        expected_code = """
#include <stdio.h>
int main(void)
{
    
    char a = '"';
    
    return 0;
}
        """
        output = self.run_against_text(code)
        self.assertEqual(output, expected_code)

        print('Testing the single quote state persists after escaped single')
        code = """
#include <stdio.h>
int main(void)
{
    /* this is a char constant single quote */
    char a = '\\'';
    /* Simple state machine for parsing multi-line comments from C code */
    return 0;
}
        """
        expected_code = """
#include <stdio.h>
int main(void)
{
    
    char a = '\\'';
    
    return 0;
}
        """
        output = self.run_against_text(code)
        self.assertEqual(output, expected_code)
