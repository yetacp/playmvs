# System dependent

HERCHOST = 127.0.0.1
HERCPORT = 3505

RDRPREP = ../../rdrprep/rdrprep
CC      = ../../gccmvs/gccmvs
CFLAGS  = -S -O3
#         -fverbose-asm
INCLUDES = -I ../../gccmvs/pdpclib

all: clean asm install

%.s: %.c
	@echo "Compiling $(notdir $<)"
	$(CC) $(CFLAGS) $(INCLUDES) $<

install:
	@echo "Preparing EBCDIC..."
	@$(RDRPREP) 01_install.jcl tmp.jcl_E
	@echo "Installing files..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E

execute:
	@echo "Preparing EBCDIC..."
	@$(RDRPREP) 02_execute.jcl tmp.jcl_E
	@echo "execute..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E

.PHONY: clean install
clean:
	rm -f *.jcl_E *.s
