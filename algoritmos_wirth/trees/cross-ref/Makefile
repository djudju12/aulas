build: main.c
	gcc main.c -ggdb -o cross-ref

run: build
	./cross-ref main.c

debug: build
	gf2 cross-ref
