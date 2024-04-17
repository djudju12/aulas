M10K=/home/jonathan/programacao/1brc/measurements10k.txt
M1KKK=/home/jonathan/programacao/1brc/measurements1kkk.txt

main:
	gcc -O3 main.c -o result

run/10K: main
	./result $(M10K)

run/1KKK: main
	./result $(M1KKK)

profile: run/1KKK
	gprof result gmon.out > out/result-profile.txt

debug: main
	/home/kopp/software/gf/gf2 result &
