#	@(#)slimmsgs:Makefile	1.2

COMPNT = slimmsgs

INSTALL = SDPinstall
#	Both ROOT and SYSTEM must be set
ROOT=

#	Product directories
MSGS=$(ROOT)/slimmer/msgs

DIRS =  $(MSGS)

ALL:	CHECK

CHECK:
	@if test "$(ROOT)" = ""; then echo "*** ERROR: ROOT must be set"; exit 9; fi


install:	ALL
	@echo "Creating System Directories:"
	-@for i in $(DIRS); do \
		if [ $$i = NONE ]; then break; fi; \
		if [ -d $$i ]; then continue; fi; \
		mkdir $$i 2>/dev/null;\
		chmod 775 $$i; \
		ls -ld $$i; done
	@echo "Installing: message files"
	$(INSTALL) -d$(MSGS) -r$(ROOT) -cNONE -sNONE -tdata  *
