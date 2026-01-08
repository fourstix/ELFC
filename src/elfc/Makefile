CC = gcc
CFLAGS = -Wall -g
LDFLAGS =
DEPFLAGS = -MMD -MP

SRCS = cgelf.c decl.c error.c expr.c gen.c main.c misc.c \
       modpath.c prep.c opt.c scan.c stmt.c sym.c tree.c
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)
TARGET = elfc

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c Makefile
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

-include $(DEPS)
