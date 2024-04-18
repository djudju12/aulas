M10K=data/measurements.txt
# M1KKK=data/measurements1kkk.txt

build: out/
	gcc -O3 src/main.c -o out/result

out/:
	mkdir -p out/

run/10K: build
	out/result $(M10K)

# para rodar esse eh necessario criar o arquivo anters
# src/create_measurements.py 1000000000
# run/1KKK: build
# 	./result $(M1KKK)

profile: run/1KKK
	gprof out/result out/gmon.out > out/result-profile.txt
	rm -f out/gmon.out

debug: build
	gf2 src/result &
