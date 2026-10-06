ASM = asm02
ASMFLAGS = -q -r -L

SRCS = crt0.asm edoscrt0.asm
OBJS = $(SRCS:.asm=.prg)

all: $(OBJS)

%.prg: %.asm
	$(ASM) $(ASMFLAGS) $< && mv $@ ../lib

clean:
	rm -f *.lst *.build $(OBJS)
