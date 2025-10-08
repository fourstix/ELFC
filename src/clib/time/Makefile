CC = elfc
CFLAGS = -L

SRCS = _dow.c _doy.c systime.c asctime.c cstime.c timezone.c utctime.c strftime.c
OBJS = $(SRCS:.c=.prg)
TARGET = time.lib

all: $(TARGET)

$(TARGET): $(OBJS)
	cat $^ > ../lib/$@

%.prg: %.c
	$(CC) $(CFLAGS) $<

clean:
	rm -f *.asm *.lst *.build $(OBJS) $(TARGET)

