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

log-clean:
	cd src; rm -f AuditFile_*; rm -f InvalidBallotFile_*
	cd testing; rm -f AuditFile_*; rm -f InvalidBallotFile_*; rm -f system_test_report.txt
