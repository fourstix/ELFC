CC = elfc
CFLAGS = -L

SRCS = _dow.c _doy.c _asctime.c _asctime2.c _cstime.c _cstime2.c _strftime.c _strftime2.c systime.c timezone.c utctime.c
OBJS = $(SRCS:.c=.prg)
TARGET = time.lib

all: $(TARGET)

$(TARGET): $(OBJS)
	cat $^ > ../lib/$@

%.prg: %.c
	$(CC) $(CFLAGS) $<

clean:
	rm -f *.asm *.lst *.build $(OBJS) $(TARGET)
