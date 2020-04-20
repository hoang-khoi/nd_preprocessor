#include <stdio.h>
#include "fsm.h"

int main() {
    int ch;
    STATE state = EXPECT_OPEN_P_LESS;

    while ((ch = getchar()) != EOF)
        state = feed(state, ch);

    return 0;
}
