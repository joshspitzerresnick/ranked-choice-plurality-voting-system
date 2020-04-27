SUBDIRS = src testing

all: $(SUBDIRS)

src:
	cd src; make -f Makefile.gui

testing: 
	cd testing; make

.PHONY: $(SUBDIRS)

clean:
	cd src; make -f Makefile.gui clean
	cd testing; make clean
