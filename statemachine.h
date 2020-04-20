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
