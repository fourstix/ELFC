CC := elfc
FILES := $(wildcard *.c)

all:
	@for file in $(FILES); do \
		echo "Building: $$file"; \
		$(CC) $$file; \
	done

# A clean target to remove generated files
clean:
	rm -f *.prg *.asm *.lst *.build *.sym *.elfos
