
CC=clang
CFLAGS=-Wall -Wextra -Wstrict-prototypes -Werror -pedantic -g -gdwarf-4 
LDFLAGS=-lm

EXEC1=tsp
OBJ1=\
	graph.o \
	stack.o \
	path.o \
	tsp.o

EXEC2 = stack_test
OBJ2 = stack.o stack_test.o

.PHONY: all  clean

all: $(EXEC1) $(EXEC2)

$(EXEC1): $(OBJ1)
	$(CC) -o $@ $^

$(EXEC2): $(OBJ2)
	$(CC) -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(EXEC1) $(OBJ1) $(EXEC2) $(OBJ2)

format:
	clang-format -i --style=file *.[ch]
