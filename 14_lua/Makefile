include ../common.m4
CFLAGS += -DLUA_USE_C89
#-v

asm: main.s

lua: clean compile_lua install_lua

compile_lua: lapi.s lauxlib.s lbaselib.s lcode.s lcorolib.s lctype.s ldblib.s \
   ldebug.s ldo.s ldump.s lfunc.s lgc.s linit.s liolib.s llex.s lmathlib.s \
	 lmem.s loadlib.s lobject.s lopcodes.s loslib.s lparser.s lstate.s \
	 lstring.s lstrlib.s ltable.s ltablib.s ltm.s lundump.s lutf8lib.s lvm.s lzio.s 

install_lua:
	./compile_all.sh

compile_module:
	@echo "Preparing EBCDIC..."
	@$(RDRPREP) jcl/$(ID).jcl tmp.jcl_E
	@echo "Installing $(ID)..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E
