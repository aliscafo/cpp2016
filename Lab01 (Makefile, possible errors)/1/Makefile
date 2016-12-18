all: bin lab1
bin:
	mkdir -p bin
lab1: bin/main.o bin/algorithm.o bin/util.o bin/io.o 
	gcc bin/main.o bin/algorithm.o bin/util.o bin/io.o -o lab1
bin/main.o: src/main.c include/util.h include/io.h include/algorithm.h
	gcc -c src/main.c -o bin/main.o
bin/algorithm.o: src/algorithm.c include/util.h include/io.h
	gcc -c src/algorithm.c -o bin/algorithm.o
bin/io.o: src/io.c
	gcc -c src/io.c -o bin/io.o
bin/util.o: src/util.c include/io.h
	gcc -c src/util.c -o bin/util.o
clean:
	rm -rf bin lab1
