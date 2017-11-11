all: bin huffman
test: bin test_main

bin:
	mkdir -p bin

huffman: bin/main.o bin/huffman.o 
	g++ bin/main.o bin/huffman.o -o huffman

bin/main.o: src/main.cpp src/huffman.h
	g++ -c src/main.cpp -o bin/main.o

bin/huffman.o: src/huffman.cpp src/huffman.h
	g++ -c -Isrc src/huffman.cpp -o bin/huffman.o

test_main: bin/test.o bin/autotest.o bin/huffman_test.o bin/huffman.o
	g++ bin/test.o bin/autotest.o bin/huffman_test.o bin/huffman.o -o test

bin/test.o: test/test.cpp
	g++ -c -Isrc test/test.cpp -o bin/test.o

bin/autotest.o: test/autotest.cpp test/autotest.h
	g++ -c test/autotest.cpp -o bin/autotest.o

bin/huffman_test.o: test/huffman_test.cpp test/huffman_test.h
	g++ -c -Isrc test/huffman_test.cpp -o bin/huffman_test.o

clean:
	rm -rf bin main test