include ../common.m4

CFLAGS  = -S -O0

asm: ezasmi.s \
	main.s \
	screens/frm_main.s \
	screens/frm_client_list.s \
	screens/frm_client_new.s \
	screens/frm_client_edit.s

screens:
	./ansi2fss.py smain screens/frm_main.ans
	./ansi2fss.py sclinew screens/frm_client_new.ans
	./ansi2fss.py sclilist screens/frm_client_list.ans
	./ansi2fss.py scliedit screens/frm_client_edit.ans

test:
	./05_test.sh

