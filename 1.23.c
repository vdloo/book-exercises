#include <stdio.h>
#include <assert.h>

#define NORMAL 0
#define COMMENT 1
#define SINGLEQ 2
#define DOUBLEQ 3

int prevstate = NORMAL;
int state = NORMAL;

void change_state(int new_state)
{
    extern int prevstate;
    extern int state;
    prevstate = state;
    state = new_state;
}


int main(void)
{
    /* Simple state machine for parsing multi-line comments from C code */
    extern int prevstate;
    extern int state;
    int c;
    int prevprevchar = '\0';
    int prevchar = '\0';
    while ((c = getchar()) != EOF) {
        switch(state) {
            case NORMAL:
                /* From the normal state we can enter the comment state, 
                 * the single quote state and the double quote state. */
                if (prevprevchar != '\\' && prevchar == '/' && c == '*') {
                    change_state(COMMENT);
                } else if (prevchar != '\\' && c == '\'') {
                    change_state(SINGLEQ);
                } else if (prevchar != '\\' && c == '"') {
                    change_state(DOUBLEQ);
                }
                break;
            case COMMENT:
                /* From the comment state we can only exit back into the normal 
		 * state. We can not have come from the comment single quote 
		 * state and we could also not have come from the double quote state 
		 * since those both do not allow entering the comment state. */
                assert(prevstate == NORMAL);
                if (prevchar == '*' && c == '/') {
                    change_state(prevstate);
		    prevchar = '\0';
		    c = '\0';
                }
                break;
            case SINGLEQ:
                /* From the single quote state we can exit back into the 
                 * normal state. The previous state should only be the normal 
                 * state since the char constant of double quote should not 
                 * change the state. And because character constants are by 
                 * definition only one char long, we should also never enter 
                 * the comment state.*/
                assert(prevstate == NORMAL);
		if (c == '\'') {
		    if (prevchar != '\\' || prevprevchar == '\\') {
                        change_state(NORMAL);
		    }
		}
                break;
            case DOUBLEQ:
                /* From the double quote state we can only revert back into the 
		 * normal state since we can't enter a comment state from within
		 * a multi-line comment. Additionally, we can not have come from 
		 * the single quote state. */
                assert(prevstate != SINGLEQ);
		if (c == '"') {
		    if (prevchar != '\\' || prevprevchar == '\\') {
                        change_state(NORMAL);
		    }
		}
                break;
        }
        /* print the previous character if not in comment */
        if (prevchar != '\0' && state != COMMENT) {
            printf("%c", prevchar);
        }
        prevprevchar = prevchar;
        prevchar = c;
    }
    /* print the last character if we have to */
    if (prevchar != '\0' && state != COMMENT) {
        printf("%c", prevchar);
    }
    return 0;
}
