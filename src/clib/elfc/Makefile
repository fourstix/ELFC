SHELL := /bin/bash
ASM = asm02
ASMFLAGS = -q -r -L

SRCS = $(wildcard *.asm)
OBJS = $(SRCS:.asm=.prg)
TARGET = elfc.lib

# The same routines built for ELF-DOS, where the subroutine table is on
# a different page (see RSUB in ../include/ops_c.inc). They are assembled
# in a folder of their own so the object files do not get mixed up.
EDOSDIR = edos
EDOSOBJS = $(SRCS:%.asm=$(EDOSDIR)/%.prg)
EDOSTARGET = edosc.lib

all: $(TARGET) $(EDOSTARGET)

$(TARGET): $(OBJS)
	cat $^ > ../lib/$@

%.prg: %.asm ../include/ops_c.inc
	$(ASM) $(ASMFLAGS) $<

$(EDOSTARGET): $(EDOSOBJS)
	cat $^ > ../lib/$@

$(EDOSDIR)/%.prg: %.asm ../include/ops_c.inc
	mkdir -p $(EDOSDIR) && cp $< $(EDOSDIR)/
	cd $(EDOSDIR) && $(ASM) $(ASMFLAGS) -D _EDOS_ -I .. $<

clean:
	rm -f *.lst *.build $(OBJS) $(TARGET) $(EDOSTARGET)
	rm -rf $(EDOSDIR)
