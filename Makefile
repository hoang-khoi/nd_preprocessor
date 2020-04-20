CFLAGS= -c -ansi -pedantic -Wall -Werror -Wfatal-errors -O3
TARGETS = main.o fsm.o

preprocessor: all
	$(CC) -o $@ $(TARGETS)

all: $(TARGETS)

run: preprocessor
	time cat wb1913/wb1913_* | ./preprocessor > wb1913.txt

%.o: %.c
	$(CC) $(CFLAGS) $<

clean:
	rm -f *.o preprocessor
