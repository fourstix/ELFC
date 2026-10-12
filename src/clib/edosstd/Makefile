SHELL := /bin/bash
CC = elfc
CFLAGS = -L

# modules from the ELF-DOS SDK that are part of this library
ASM = asm02
ASMFLAGS = -q -r -L -C -I ..
SDK = ../elfdos-sdk
SDKOBJS = $(SDK)/lib/heap_malloc.prg $(SDK)/lib/env.prg $(SDK)/lib/drives.prg

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.prg)
TARGET = edosstd.lib

all: $(TARGET)

$(TARGET): $(OBJS) $(SDKOBJS)
	cat $^ > ../lib/$@

%.prg: %.c edos.h $(SDK)/include/kernel_api.inc
	$(CC) $(CFLAGS) $<

# the SDK modules include their files as include/..., so assemble
# them from the lib folder with the SDK folder as the include path
$(SDK)/lib/%.prg: $(SDK)/lib/%.asm
	cd $(SDK)/lib && $(ASM) $(ASMFLAGS) $*.asm

clean:
	rm -f *.asm *.lst *.build $(OBJS) $(TARGET)
	rm -f $(SDK)/lib/*.prg $(SDK)/lib/*.lst $(SDK)/lib/*.build
