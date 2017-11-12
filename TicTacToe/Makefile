all: bin main
board_test: bin boardtest

bin:
	mkdir -p bin

main: bin/main.o bin/Board.o bin/BoardView.o
	g++ bin/main.o bin/Board.o bin/BoardView.o -o main

bin/main.o: src/main.cpp
	g++ -c -I include src/main.cpp -o bin/main.o

bin/BoardView.o: src/BoardView.cpp
	g++ -c -I include src/BoardView.cpp -o bin/BoardView.o

boardtest: bin/test_main.o bin/Test.o bin/BoardTest.o bin/Board.o 
	g++ bin/test_main.o bin/Test.o bin/BoardTest.o bin/Board.o -o board_test

bin/test_main.o: test/test_main.cpp
	g++ -c -I include test/test_main.cpp -o bin/test_main.o

bin/Test.o: test/Test.cpp
	g++ -c -I include test/Test.cpp -o bin/Test.o

bin/BoardTest.o: test/BoardTest.cpp
	g++ -c -I include test/BoardTest.cpp -o bin/BoardTest.o

bin/Board.o: src/Board.cpp 
	g++ -c -I include src/Board.cpp -o bin/Board.o

clean:
	rm -rf bin main board_test

