#ifndef FSM_H
#define FSM_H

typedef enum _state {
    /* <P> */
    EXPECT_OPEN_P_LESS,
    EXPECT_OPEN_P_CHAR,
    EXPECT_OPEN_P_GREATER,

    /* <B> */
    EXPECT_OPEN_B_LESS,
    EXPECT_OPEN_B_CHAR,
    EXPECT_OPEN_B_GREATER,

    /* </B> */
    EXPECT_CLOSE_B_SLASH,
    EXPECT_CLOSE_B_CHAR,
    EXPECT_CLOSE_B_GREATER,

    /* <I> */
    EXPECT_OPEN_I_LESS,
    EXPECT_OPEN_I_CHAR,
    EXPECT_OPEN_I_GREATER,

    /* </I> */
    EXPECT_CLOSE_I_SLASH,
    EXPECT_CLOSE_I_CHAR,
    EXPECT_CLOSE_I_GREATER,

    PREDEF_IGNORE,
    RECEIVING_WORD,
    RECEIVING_TYPE,
    RECEIVING_DEF,

    WAITING_FOR_ENDLINE
} STATE;

/* Feed a byte into the machine, peform some action accordingly and returns the
   next state */
STATE feed(STATE curstate, int ch);

#endif
