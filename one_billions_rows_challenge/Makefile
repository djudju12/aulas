main:
	gcc main.c -o result -g -pg

run: main
	./result

profile: run
	gprof result gmon.out > out/result-profile.txt

debug: main
	/home/kopp/software/gf/gf2 result &