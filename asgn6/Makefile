CC=clang
CFLAGS=-Wall -Wextra -Wstrict-prototypes -Werror -pedantic -g -gdwarf-4

LFLAGS = -lm

EXEC1=huff
OBJS1=huff.o bitwriter.o node.o pq.o
LIBS1=io-$(shell uname -m).a

EXEC2 = bwtest
OBJS2 = bitwriter.o bwtest.o

EXEC3 = pqtest
OBJS3 = pq.o pqtest.o node.o

EXEC4 = nodetest
OBJS4 = node.o nodetest.o

.PHONY: all  clean

all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4)

$(EXEC1): $(OBJS1) $(LIBS1)
	$(CC) -o $@ $^

$(EXEC2): $(OBJS2) $(LIBS1)
	$(CC)  -o $@ $^

$(EXEC3): $(OBJS3)
	$(CC)  -o $@ $^

$(EXEC4): $(OBJS4)
	$(CC)  -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(EXEC1) $(OBJS1) $(EXEC2) $(OBJS2)

format:
	clang-format -i --style=file *.[ch]


