CC = gcc
CFLAGS = -Wall -g
LDFLAGS =

SRCS = cgelf.c decl.c error.c expr.c gen.c main.c misc.c \
       prep.c opt.c scan.c stmt.c sym.c tree.c
OBJS = $(SRCS:.c=.o)
TARGET = elfc

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)

