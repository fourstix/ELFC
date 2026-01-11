ASM = asm02
ASMFLAGS = -q -L

SRCS = crt0.asm
TARGET = crt0.prg

all: $(TARGET)

$(TARGET): $(SRCS)
	$(ASM) $(ASMFLAGS) $^ && mv $(TARGET) ../lib

clean:
	rm -f *.lst *.build

