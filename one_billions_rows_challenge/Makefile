main:
	gcc -O3 main.c -o result -g -pg

run: main
	./result

profile: run
	gprof result gmon.out > result-profile.txt

debug: main
	/home/jonathan/software/gf/gf2 result &