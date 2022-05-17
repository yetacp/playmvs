include ../common.m4
CFLAGS  = -S -O0 -DLUA_USE_C89
#-v

include ./jcldep.m4

asm: lapi.s lauxlib.s lbaselib.s lcode.s lcorolib.s lctype.s \
   ldebug.s ldo.s ldump.s lfunc.s lgc.s linit.s liolib.s llex.s lmathlib.s \
	 lmem.s loadlib.s lobject.s lopcodes.s loslib.s lparser.s lstate.s \
	 lstring.s lstrlib.s ltable.s ltablib.s ltm.s lundump.s lutf8lib.s \
	 lvm.s lzio.s lua.s \
	 jcl/01.done jcl/02.done jcl/03.done jcl/04.done jcl/05.done \
	 jcl/06.done jcl/07.done jcl/08.done jcl/09.done jcl/10.done \
	 jcl/11.done jcl/12.done jcl/13.done jcl/14.done jcl/15.done \
	 jcl/16.done jcl/17.done jcl/18.done jcl/19.done jcl/20.done \
	 jcl/21.done jcl/22.done jcl/23.done jcl/24.done jcl/25.done \
	 jcl/26.done jcl/27.done jcl/28.done jcl/29.done jcl/30.done \
	 jcl/31.done

create_jcls:
	rm -f jcl/*.done jcl/*.jcl
	./create_jcls.py
