CC = elfc
CFLAGS = -L

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.prg)
TARGET = string.lib

all: $(TARGET)

$(TARGET): $(OBJS)
	cat $^ > ../lib/$@

%.prg: %.c
	$(CC) $(CFLAGS) $<

clean:
	rm -f *.asm *.lst *.build $(OBJS) $(TARGET)

