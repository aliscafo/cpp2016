all: bin main
bin:
	mkdir -p bin
main: bin/clist.o bin/main.o
	gcc bin/clist.o bin/main.o -o main
bin/clist.o: source/clist.c include/clist.h
	gcc -c source/clist.c -o bin/clist.o
bin/main.o: source/main.c include/clist.h
	gcc -c source/main.c -o bin/main.o
clean:
	rm -rf bin main


	