ASM = asm02
ASMFLAGS = -q -L
CC = elfc
CFLAGS = -L


ASM_SRCS = $(wildcard *.asm)
C_SRCS = $(wildcard *.c)
OBJS = $(ASM_SRCS:.asm=.prg) $(C_SRCS:.c=.prg)
TARGET = float32.lib

all: $(TARGET)

$(TARGET): $(OBJS)
	cat $^ > ../lib/$@

%.prg: %.asm
	$(ASM) $(ASMFLAGS) $<
%.prg: %.c
	$(CC) $(CFLAGS) $<

clean:
	rm -f *.lst *.build $(OBJS) $(TARGET)
	rm -f abs.asm acos.asm addf.asm areducef.asm asinf.asm atanf.asm atanf2.asm
	rm -f ceilf.asm cosf.asm coshf.asm deg2radf.asm divf.asm eqf.asm expf.asm
	rm -f floorf.asm fmodf.asm fracf.asm frexpf.asm fstrf.asm ftoa.asm ftoi.asm
	rm -f ftoi32.asm ftos.asm gtef.asm gtf.asm hypotf.asm i32tof.asm invf.asm
	rm -f itof.asm ldexpf.asm log2f.asm log10f.asm logf.asm ltef.asm lte.asm
	rm -f modf.asm multf.asm nef.asm negf.asm powf.asm rad2degf.asm roundf.asm
	rm -f samef.asm sgnf.asm sinf.asm sinhf.asm sqrtf.asm subf.asm tanf.asm
	rm -f tanhf.asm truncf.asm zflushf.asm
