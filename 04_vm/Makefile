include ../common.m4

asm: vm.s vmcode.s

linux: 
	gcc -o vm vm.c vmcode.c
	./vm