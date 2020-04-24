SUBDIRS = src testing

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: $(SUBDIRS)

clean:
	cd src; make clean
	cd testing; make clean
