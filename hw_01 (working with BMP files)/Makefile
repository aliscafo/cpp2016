all: bin main
bin:
	mkdir -p bin
main: bin/main.o bin/bmp.o	
	gcc -std=c99 -Wall -Werror bin/main.o bin/bmp.o -o main
bin/main.o: source/main.c include/bmp.h 
	gcc -std=c99 -Wall -Werror -c source/main.c -o bin/main.o
bin/bmp.o: source/bmp.c include/bmp.h
	gcc -std=c99 -Wall -Werror -c source/bmp.c -o bin/bmp.o
clean:
	rm -rf bin main


	
	