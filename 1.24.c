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

int c;
int prevprevchar = '\0';
int prevchar = '\0';

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

int state_in_stack(int state_to_check)
{
    extern int state[MAXNESTED];
	int i;
	for (i = 0; i < MAXNESTED; i++) {
		if (state[i] == state_to_check) {
			return 1;
		}
	}
	return 0;
}

void exit_state(int state_to_exit)
{
    /* Drop a state from the stack */
    extern int state[MAXNESTED];
    extern int nest_level;
	if (get_current_state() != state_to_exit) {
		fprintf(
			stderr, 
			"Expected to be exiting state %s but was actually exiting %s at line %d\n",
            names[state_to_exit],
            names[get_current_state()],
			lines + 1
		);
		exit(151);
	}
	if (!state_in_stack(state_to_exit)) {
		fprintf(
			stderr, 
			"Closing unstarted %s at line %d\n",
            names[state_to_exit],
			lines + 1
		);
		exit(152);
	}
    state[nest_level] = '\0';
    nest_level--;
}

int detect_entering_comment()
{
    extern int c;
    extern int prevprevchar;
    extern int prevchar;
    return (prevprevchar != '\\' && prevchar == '/' && c == '*');
}

int detect_leaving_comment()
{
    return (prevchar == '*' && c == '/');
}

int detect_state_change(char delimiter)
{
    extern int c;
    extern int prevprevchar;
    extern int prevchar;
    if (c == delimiter) {
        if (prevchar != '\\' || prevprevchar == '\\') {
            return 1;
        }
    }
    return 0;
}

void shift_read_character()
{
    extern int c;
    extern int prevprevchar;
    extern int prevchar;
    prevprevchar = prevchar;
    prevchar = c;
}

void handle_re_entrant_state()
{
	/* From the a re-entrant state we can enter the comment state, 
	 * the single quote state and the double quote state. We can also
	 * enter the parenthesis, brackets and braces states. Those last 
	 * three can be nested */
	if (detect_entering_comment()) {
		enter_state(COMMENT);
	} else if (detect_state_change('\'')) {
		enter_state(SINGLEQ);
	} else if (detect_state_change('"')) {
		enter_state(DOUBLEQ);
	} else if (detect_state_change('(')) {
		enter_state(PARENTH);
	} else if (detect_state_change(')')) {
		exit_state(PARENTH);
	} else if (detect_state_change('[')) {
		enter_state(BRACKET);
	} else if (detect_state_change(']')) {
		exit_state(BRACKET);
	} else if (detect_state_change('{')) {
		enter_state(CURLIES);
	} else if (detect_state_change('}')) {
		exit_state(CURLIES);
	}
}

void handle_comment()
{
	/* From the comment state we can only exit back into the normal 
	 * state. We can not have come from the comment single quote 
	 * state and we could also not have come from the double quote state 
	 * since those both do not allow entering the comment state. */
	if (detect_leaving_comment()) {
		exit_state(COMMENT);
		if (get_current_state() == SINGLEQ || get_current_state() == DOUBLEQ) {
			fprintf(
				stderr, 
				"Could not parse comment at line %d\n",
				lines
			);
			exit(153);
		}
	}
}

void handle_q(char delimiter, int state, int check, char msg[], int code)
{
	if (detect_state_change(delimiter)) {
		exit_state(state);
		if (get_current_state() == check) {
			fprintf(
					stderr, 
					"%s at line %d\n",
					msg, lines
				   );
			exit(code);
		}
	}
}

void handle_singleq()
{
	/* From the single quote state we can exit back into the 
	 * normal state. The previous state should only be the normal 
	 * state since the char constant of double quote should not 
	 * change the state. And because character constants are by 
	 * definition only one char long, we should also never enter 
	 * the comment state.*/
	handle_q('\'', SINGLEQ, DOUBLEQ, "Could not parse single quotes", 151);
}

void handle_doubleq()
{
	/* From the double quote state we can only revert back into the 
	 * normal state since we can't enter a comment state from within
	 * a multi-line comment. Additionally, we can not have come from 
	 * the single quote state. */
	handle_q('"', DOUBLEQ, SINGLEQ, "Could not parse double quotes", 152);
}

void initialize_state_machine()
{
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            lines++;
        }
        switch(get_current_state()) {
            case NORMAL: case PARENTH: case BRACKET: case CURLIES:
				handle_re_entrant_state();
                break;
            case COMMENT:
				handle_comment();
                break;
            case SINGLEQ:
				handle_singleq();
                break;
            case DOUBLEQ:
				handle_doubleq();
                break;
        }
        shift_read_character();
    }
}

void trace_unbalanced()
{
    extern int nest_level;
    extern int lines;
    extern const char *names[7];
    if (nest_level != 0) {
        fprintf(
            stderr, 
            "Unbalanced %s at line %d\n",
            names[get_current_state()],
            get_line_of_state(nest_level)
        );
        exit(154);
    } else {
		printf("It all looks ok!\n");
	}
}

int main(void)
{
    /* Simple state machine to check a C program for rudimentary syntax errors */
    set_initial_state();
    initialize_state_machine();
    trace_unbalanced();
    return 0;
}
