
SHELL := /bin/bash
CC = elfc
CFLAGS = -L -i ../include

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.prg)
TARGET = dirent.lib

all: $(TARGET)

$(TARGET): $(OBJS)
	cat $^ > ../lib/$@

%.prg: %.c odir.h ../include/dirent.h
	$(CC) $(CFLAGS) $<

clean:
	rm -f *.asm *.lst *.build $(OBJS) $(TARGET)
