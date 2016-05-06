all:
	gcc -fPIC -shared -g -o mylib.so mylib.c
run:
	LD_PRELOAD=./mylib.so wget google.com
