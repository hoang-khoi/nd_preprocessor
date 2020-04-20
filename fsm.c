#include "fsm.h"

#include <ctype.h>
#include <stdio.h>

int isignored(int ch);

STATE feed_expect_open_p_less(int ch);
STATE feed_expect_open_p_char(int ch);
STATE feed_expect_open_p_greater(int ch);

STATE feed_expect_close_p_less(int ch);
STATE feed_expect_close_p_slash(int ch);
STATE feed_expect_close_p_char(int ch);
STATE feed_expect_close_p_greater(int ch);

STATE feed_expect_open_b_less(int ch);
STATE feed_expect_open_b_char(int h);
STATE feed_expect_open_b_greater(int ch);

STATE feed_expect_close_b_less(int ch);
STATE feed_expect_close_b_slash(int ch);
STATE feed_expect_close_b_char(int ch);
STATE feed_expect_close_b_greater(int ch);

STATE feed_expect_open_i_less(int ch);
STATE feed_expect_open_i_char(int ch);
STATE feed_expect_open_i_greater(int ch);

STATE feed_expect_close_i_less(int ch);
STATE feed_expect_close_i_slash(int ch);
STATE feed_expect_close_i_char(int ch);
STATE feed_expect_close_i_greater(int ch);

STATE feed_predef_ignore(int ch);
STATE feed_receiving_word(int ch);
STATE feed_receiving_type(int ch);
STATE feed_receiving_def(int ch);
STATE feed_waiting_for_endline(int ch);

STATE feed_invalid(int ch);

STATE feed(STATE curstate, int ch) {
    switch (curstate) {
        case EXPECT_OPEN_P_LESS:
            return feed_expect_open_p_less(ch);
        case EXPECT_OPEN_P_CHAR:
            return feed_expect_open_p_char(ch);
        case EXPECT_OPEN_P_GREATER:
            return feed_expect_open_p_greater(ch);

        /**************************************/

        case EXPECT_OPEN_B_LESS:
            return feed_expect_open_b_less(ch);
        case EXPECT_OPEN_B_CHAR:
            return feed_expect_open_b_char(ch);
        case EXPECT_OPEN_B_GREATER:
            return feed_expect_open_b_greater(ch);
        case EXPECT_CLOSE_B_SLASH:
            return feed_expect_close_b_slash(ch);
        case EXPECT_CLOSE_B_CHAR:
            return feed_expect_close_b_char(ch);
        case EXPECT_CLOSE_B_GREATER:
            return feed_expect_close_b_greater(ch);

        /**************************************/

        case EXPECT_OPEN_I_LESS:
            return feed_expect_open_i_less(ch);
        case EXPECT_OPEN_I_CHAR:
            return feed_expect_open_i_char(ch);
        case EXPECT_OPEN_I_GREATER:
            return feed_expect_open_i_greater(ch);

        case EXPECT_CLOSE_I_SLASH:
            return feed_expect_close_i_slash(ch);
        case EXPECT_CLOSE_I_CHAR:
            return feed_expect_close_i_char(ch);
        case EXPECT_CLOSE_I_GREATER:
            return feed_expect_close_i_greater(ch);

        /**************************************/

        case PREDEF_IGNORE:
            return feed_predef_ignore(ch);
        case RECEIVING_WORD:
            return feed_receiving_word(ch);
        case RECEIVING_TYPE:
            return feed_receiving_type(ch);
        case RECEIVING_DEF:
            return feed_receiving_def(ch);
        case WAITING_FOR_ENDLINE:
            return feed_waiting_for_endline(ch);
    }

    return 0;
}

STATE feed_expect_open_p_less(int ch) {
    if (isignored(ch))
        return EXPECT_OPEN_P_LESS;

    if (ch == '<')
        return EXPECT_OPEN_P_CHAR;

    return WAITING_FOR_ENDLINE;
}

STATE feed_expect_open_p_char(int ch) {
    if (ch == 'P')
        return EXPECT_OPEN_P_GREATER;

    return WAITING_FOR_ENDLINE;
}

STATE feed_expect_open_p_greater(int ch) {
    if (ch == '>')
        return EXPECT_OPEN_B_LESS;

    return WAITING_FOR_ENDLINE;
}

STATE feed_expect_open_b_less(int ch) {
    if (isignored(ch))
        return EXPECT_OPEN_B_LESS;

    if (ch == '<')
        return EXPECT_OPEN_B_CHAR;

    return WAITING_FOR_ENDLINE;
}

STATE feed_expect_open_b_char(int ch) {
    if (ch == 'B')
        return EXPECT_OPEN_B_GREATER;

    return WAITING_FOR_ENDLINE;
}

STATE feed_expect_open_b_greater(int ch) {
    if (ch == '>')
        return RECEIVING_WORD;

    return WAITING_FOR_ENDLINE;
}

STATE feed_expect_close_b_slash(int ch) {
    if (ch == '/')
        return EXPECT_CLOSE_B_CHAR;

    return WAITING_FOR_ENDLINE;
}

STATE feed_expect_close_b_char(int ch) {
    if (ch == 'B')
        return EXPECT_CLOSE_B_GREATER;

    return WAITING_FOR_ENDLINE;
}

STATE feed_expect_close_b_greater(int ch) {
    if (ch == '>')
        return EXPECT_OPEN_I_LESS;

    return WAITING_FOR_ENDLINE;
}

STATE feed_expect_open_i_less(int ch) {
    if (isignored(ch))
        return EXPECT_OPEN_I_LESS;

    if (ch == '<')
        return EXPECT_OPEN_I_CHAR;

    return WAITING_FOR_ENDLINE;
}

STATE feed_expect_open_i_char(int ch) {
    if (ch == 'I')
        return EXPECT_OPEN_I_GREATER;

    return WAITING_FOR_ENDLINE;
}

STATE feed_expect_open_i_greater(int ch) {
    if (ch == '>')
        return RECEIVING_TYPE;

    return WAITING_FOR_ENDLINE;
}

STATE feed_expect_close_i_slash(int ch) {
    if (ch == '/')
        return EXPECT_CLOSE_I_CHAR;

    return WAITING_FOR_ENDLINE;
}
STATE feed_expect_close_i_char(int ch) {
    if (ch == 'I')
        return EXPECT_CLOSE_I_GREATER;

    return WAITING_FOR_ENDLINE;
}

STATE feed_expect_close_i_greater(int ch) {
    if (ch == '>')
        return PREDEF_IGNORE;

    return WAITING_FOR_ENDLINE;
}

STATE feed_predef_ignore(int ch) {
    if (!isalpha(ch))
        return PREDEF_IGNORE;
    else {
        putchar(ch);
        return RECEIVING_DEF;
    }

    return WAITING_FOR_ENDLINE;
}

STATE feed_receiving_word(int ch) {
    if (isalpha(ch)) {
        putchar(tolower(ch));
        return RECEIVING_WORD;
    }

    if (ch == '<') {
        putchar('\n');
        return EXPECT_CLOSE_B_SLASH;
    }

    return WAITING_FOR_ENDLINE;
}

STATE feed_receiving_type(int ch) {
    /* Not gonna validate this */
    if (ch == '<') {
        putchar('\n');
        return EXPECT_CLOSE_I_SLASH;
    }

    putchar(ch);
    return RECEIVING_TYPE;
}

STATE feed_receiving_def(int ch) {
    if (ch == '<') {
        putchar('\n');
        return WAITING_FOR_ENDLINE;
    }

    putchar(ch);
    return RECEIVING_DEF;
}

STATE feed_waiting_for_endline(int ch) {
    if (ch == '\n')
        return EXPECT_OPEN_P_LESS;

    return WAITING_FOR_ENDLINE;
}

int isignored(int ch) {
    return !(ch == '<' || ch == '>');
}
