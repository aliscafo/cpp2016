all: bin lab2
bin:
	mkdir -p bin
lab2: bin/test.o bin/str.o bin/test_str.o 
	gcc bin/test.o bin/str.o bin/test_str.o -o lab2
bin/str.o: src/str.c
	gcc -c src/str.c -o bin/str.o
bin/test_str.o: src/test_str.c include/str.h
	gcc -c src/test_str.c -o bin/test_str.o
bin/test.o: include/test_str.h src/test.c 
	gcc -c src/test.c -o bin/test.o
clean:
	rm -rf bin lab2
