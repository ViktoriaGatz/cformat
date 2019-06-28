all:
	gcc ./src/*.c -O0 -g3
	./a.out -c -o my.lz78 my.txt 65536 > log.dat
	gcc ./src/*.c -O0 -g3
	./a.out -d -o result.txt my.lz78 65536 > log.dat
	diff result.txt my.txt
