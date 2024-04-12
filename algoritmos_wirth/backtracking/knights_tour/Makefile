CFLAGS=-Wall -Wextra -pedantic -std=c99 -g

build:
	cc $(CFLAGS) knights_tour.c -o knights_tour

build/paral:
	cc $(CFLAGS) knights_tour_parallel.c -o knights_tour_parallel

run: build
	./knights_tour

run/paral: build/paral
	./knights_tour_parallel

debug: build
	/home/jonathan/software/gf/gf2 knights_tour  &