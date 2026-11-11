SHELL := /bin/bash
ASM = asm02
ASMFLAGS = -q -r -L -I ..
CC = elfc
CFLAGS = -L


# the compiler leaves a .asm file for each .c file, which is not a source
C_SRCS = $(wildcard *.c)
ASM_SRCS = $(filter-out $(C_SRCS:.c=.asm),$(wildcard *.asm))
OBJS = $(ASM_SRCS:.asm=.prg) $(C_SRCS:.c=.prg)
TARGET = float32.lib

all: $(TARGET)

$(TARGET): $(OBJS)
	cat $^ > ../lib/$@

# the C rule is first, so a .c file is compiled even when its .asm is left over
%.prg: %.c
	$(CC) $(CFLAGS) $<
%.prg: %.asm
	$(ASM) $(ASMFLAGS) $<

clean:
	rm -f *.lst *.build $(OBJS) $(TARGET)
	rm -f $(C_SRCS:.c=.asm)
