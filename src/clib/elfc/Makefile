ASM = asm02
ASMFLAGS = -L

SRCS = $(wildcard *.asm)
OBJS = $(SRCS:.asm=.prg)
TARGET = elfc.lib

all: $(TARGET)

$(TARGET): $(OBJS)
	cat $^ > ../lib/$@

%.prg: %.asm
	$(ASM) $(ASMFLAGS) $<

clean:
	rm -f *.lst *.build $(OBJS) $(TARGET)

