M10K=/home/kopp/fontes/pessoal/1brc/measurements10k.txt
M1KKK=/home/kopp/fontes/pessoal/1brc/measurements1kkk.txt

CFLAGS+= -std=c11 -O3 -march=native -mtune=native -flto -Wall -Wextra -Wpedantic \
		-Wformat=2 -Wconversion -Wundef -Winline -Wimplicit-fallthrough

main:
	gcc $(CFLAGS) main.c -o result -g -pg

run/10K: main
	./result $(M10K)

run/1KKK: main
	./result $(M1KKK)

profile: run/1KKK
	gprof result gmon.out > out/result-profile.txt

debug: main
	/home/kopp/software/gf/gf2 result &
