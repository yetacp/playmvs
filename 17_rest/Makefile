include ../common.m4

CFLAGS  = -S -O0

asm: main.s \
	screens/frm_main.s \
	screens/frm_client_list.s \
	screens/frm_client_new.s \
	screens/frm_client_edit.s

screens:
	./ansi2fss.py smain screens/frm_main.ans
	./ansi2fss.py scnew screens/frm_client_new.ans
	./ansi2fss.py sclist screens/frm_client_list.ans
	./ansi2fss.py scedit screens/frm_client_edit.ans

test:
	./05_test.sh

deps:
	cd ../08_fss && make
	cd ../15_tcpip && make
