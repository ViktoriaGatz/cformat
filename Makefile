all:
	gcc ./src/*.c -O0 -g3
	./a.out -c -o my.lz78 my.txt 65536 > log1.dat
	./a.out -d -o result.txt my.lz78 65536 > log2.dat
	diff result.txt my.txt
