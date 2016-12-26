#include <stdio.h>
#include <stdlib.h>

#define NORMAL 0
#define COMMENT 1
#define SINGLEQ 2
#define DOUBLEQ 3
#define PARENTH 4
#define BRACKET 5
#define CURLIES 6

/* parse code until the C99 max nesting limit */
#define MAXNESTED 127

int lines = 0;
int nest_level = 0;
int state[MAXNESTED] = {'\0'};

/* mark the line of every state change */
int enterline[MAXNESTED] = {'\0'};

const char *names[7] = {
    "normal text", "comment", "single quotes",
    "double quotes", "parenthesis", "brackets",
    "curly braces"
};

void set_initial_state()
{
    extern int state[MAXNESTED];
    state[0] = NORMAL;
}

int get_line_of_state(int level)
{
    extern int enterline[MAXNESTED];
    return enterline[level];
}

int get_current_state()
{
    extern int state[MAXNESTED];
    extern int nest_level;
    return state[nest_level];
}

void enter_state(int new_state)
{
    /* Add a new state to the stack */
    extern int state[MAXNESTED];
    extern int enterline[MAXNESTED];
    extern int lines;
    nest_level++;
    if (nest_level >= MAXNESTED) {
        fprintf(
            stderr, 
            "C99 can only nest control up to 127 times. At line %d\n",
            lines
        );
        exit(150);
    }
    state[nest_level] = new_state;
    enterline[nest_level] = lines + 1;
}

void exit_state()
{
    /* Drop a state from the stack */
    extern int state[MAXNESTED];
    extern int nest_level;
    state[nest_level] = '\0';
    nest_level--;
}


int main(void)
{
    /* Simple state machine to check a C program for rudimentary syntax errors */
    extern int nest_level;
    extern int lines;
    extern const char *names[7];
    int c;
    int prevprevchar = '\0';
    int prevchar = '\0';

    set_initial_state();

    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            lines++;
        }
        switch(get_current_state()) {
            case NORMAL:
                /* From the normal state we can enter the comment state, 
                 * the single quote state and the double quote state. */
                if (prevprevchar != '\\' && prevchar == '/' && c == '*') {
                    enter_state(COMMENT);
                } else if (prevchar != '\\' && c == '\'') {
                    enter_state(SINGLEQ);
                } else if (prevchar != '\\' && c == '"') {
                    enter_state(DOUBLEQ);
                }
                break;
            case COMMENT:
                /* From the comment state we can only exit back into the normal 
                 * state. We can not have come from the comment single quote 
                 * state and we could also not have come from the double quote state 
                 * since those both do not allow entering the comment state. */
                if (prevchar == '*' && c == '/') {
                    exit_state();
                    if (get_current_state() != NORMAL) {
                        fprintf(
                            stderr, 
                            "Could not parse comment at line %d\n",
                            lines
                        );
                        exit(150);
                    }
                }
                break;
            case SINGLEQ:
                /* From the single quote state we can exit back into the 
                 * normal state. The previous state should only be the normal 
                 * state since the char constant of double quote should not 
                 * change the state. And because character constants are by 
                 * definition only one char long, we should also never enter 
                 * the comment state.*/
                if (c == '\'') {
                    if (prevchar != '\\' || prevprevchar == '\\') {
                        exit_state();
                        if (get_current_state() != NORMAL) {
                            fprintf(
                                stderr, 
                                "Could not parse single quotes at line %d\n",
                                lines
                            );
                            exit(150);
                        }
                    }
                }
                break;
            case DOUBLEQ:
                /* From the double quote state we can only revert back into the 
                 * normal state since we can't enter a comment state from within
                 * a multi-line comment. Additionally, we can not have come from 
                 * the single quote state. */
                if (c == '"') {
                    if (prevchar != '\\' || prevprevchar == '\\') {
                        exit_state();
                        if (get_current_state() != NORMAL) {
                            fprintf(
                                stderr, 
                                "Could not parse double quotes at %d\n",
                                lines
                            );
                            exit(150);
                        }
                    }
                }
                break;
        }
        prevprevchar = prevchar;
        prevchar = c;
    }
    if (nest_level != 0) {
        fprintf(
            stderr, 
            "Unbalanced %s at line %d\n",
            names[get_current_state()],
            get_line_of_state(nest_level)
        );
    }
    return 0;
}
