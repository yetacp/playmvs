# System dependent

# PATH TO GCCMVS FOLDER
GCCMVS = ../../gccmvs
RDRPREP = ../rdrprep/rdrprep

HERCHOST = 127.0.0.1
HERCPORT = 3505

CC      = $(GCCMVS)/gccmvs
CFLAGS  = -S -O3
# -fverbose-asm

INCLUDES = -I $(GCCMVS)/mvsclib/common/include

all: asm install

%.s: %.c
	@echo "Compiling $(notdir $<)"
	$(CC) $(CFLAGS) $(INCLUDES) $<

install:
	@echo "Installing application..."
	@$(RDRPREP) 01_install.jcl tmp.jcl_E
	@echo "Installing files..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E

execute:
	@echo "Executing application..."
	@$(RDRPREP) 02_execute.jcl tmp.jcl_E
	@echo "execute..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E

clean:
	rm -f *.jcl_E *.s

.PHONY: clean install test screens