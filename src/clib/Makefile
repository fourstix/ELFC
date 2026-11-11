SUBDIRS := crt0 ctype elfc minio edosstd math32 stdio stdlib string time float32 dirent edosdir

.PHONY: all clean $(SUBDIRS)

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done
