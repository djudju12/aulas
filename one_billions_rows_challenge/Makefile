M10K=/home/kopp/fontes/pessoal/1brc/measurements10k.txt
M1KKK=/home/kopp/fontes/pessoal/1brc/measurements1kkk.txt

main:
	gcc main.c -o result -g -pg

run/10K: main
	./result $(M10K)

run/1KKK: main
	./result $(M1KKK)

profile: run/1KKK
	gprof result gmon.out > out/result-profile.txt

debug: main
	/home/kopp/software/gf/gf2 result &
