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
	rm -f absf.asm acosf.asm addf.asm areducef.asm asinf.asm atanf.asm atan2f.asm
	rm -f atof.asm ceilf.asm cosf.asm coshf.asm deg2radf.asm divf.asm eqf.asm
	rm -f expf.asm floorf.asm fmodf.asm fracf.asm frexpf.asm fstrf.asm ftoa.asm
	rm -f ftoi.asmftoi32.asm ftos.asm gtef.asm gtf.asm hypotf.asm i32tof.asm
	rm -f invf.asm itof.asm ldexpf.asm log2f.asm log10f.asm logf.asm ltef.asm
	rm -f ltf.asm makef.asm modf.asm mulf.asm nef.asm negf.asm powf.asm
	rm -f rad2degf.asm roundf.asm samef.asm sgnf.asm sinf.asm sinhf.asm sqrtf.asm
	rm -f subf.asm tanf.asm tanhf.asm truncf.asm zflushf.asm _fp_const.asm
