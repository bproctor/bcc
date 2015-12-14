CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SRC=$(wildcard src/*.c)
OBJS=$(SRC:.c=.o)
EXEC=bcc

all: $(SRC) $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f bcc *.o
