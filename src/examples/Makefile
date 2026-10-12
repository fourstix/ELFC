CC := elfc
CFLAGS :=
FILES := $(wildcard *.c)

# The operating system to build for, given on the command line:
#   make                    build for Elf/OS
#   make TARGET_OS=elfdos   build for ELF-DOS
TARGET_OS ?= elfos

ifeq ($(TARGET_OS),elfdos)
CFLAGS += -E
else ifneq ($(TARGET_OS),elfos)
$(error TARGET_OS must be elfos or elfdos, not '$(TARGET_OS)')
endif

# The monitor ROM that the BRKPT macro in a program breaks into, given
# on the command line. Without it BRKPT does nothing:
#   make BRKPT=stgrom       break into the STG ROM
#   make BRKPT=maxmon       break into the MAXMON ROM
BRKPT ?= none

ifeq ($(BRKPT),stgrom)
CFLAGS += -D _STGROM_
else ifeq ($(BRKPT),maxmon)
CFLAGS += -D _MAXMON_
else ifneq ($(BRKPT),none)
$(error BRKPT must be none, stgrom or maxmon, not '$(BRKPT)')
endif

all:
	@for file in $(FILES); do \
		echo "Building: $$file"; \
		$(CC) $(CFLAGS) $$file; \
	done

# A clean target to remove generated files, an ELF-DOS program
# has the name of its source file without an extension
clean:
	rm -f *.prg *.asm *.lst *.build *.lkb *.sym *.elfos
	rm -f $(FILES:.c=)
