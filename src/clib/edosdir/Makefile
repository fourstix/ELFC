
SHELL := /bin/bash
CC = elfc
CFLAGS = -L -i ../include

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.prg)
TARGET = edosdir.lib

all: $(TARGET)

$(TARGET): $(OBJS)
	cat $^ > ../lib/$@

%.prg: %.c kdir.h ../include/dirent.h ../edosstd/edos.h
	$(CC) $(CFLAGS) $<

clean:
	rm -f *.asm *.lst *.build $(OBJS) $(TARGET)
