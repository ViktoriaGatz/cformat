all:
	gcc -Wall -Wextra src/*.c -o main -g3 -O0
	./main -c -o my.lzw my.txt
	./main -d -o result.txt my.lzw
	diff my.txt result.txt
