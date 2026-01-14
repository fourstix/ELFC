CC = elfc
CFLAGS = -L

SRCS = _dow.c _doy.c asctime.c cstime.c strftime.c systime.c timezone.c utctime.c
OBJS = $(SRCS:.c=.prg)
TARGET = time.lib

all: $(TARGET)

$(TARGET): $(OBJS)
	cat $^ > ../lib/$@

%.prg: %.c
	$(CC) $(CFLAGS) $<

clean:
	rm -f *.asm *.lst *.build $(OBJS) $(TARGET)

