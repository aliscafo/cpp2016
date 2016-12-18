all: bin main

bin:
	mkdir -p bin

main:bin/main.o bin/phonebook.o
	gcc bin/main.o bin/phonebook.o -lexpat -o main

bin/main.o:src/main.c include/names.h include/phonebook.h
	gcc -c -I include src/main.c -o bin/main.o

bin/phonebook.o:src/phonebook.c
	gcc -c -I include src/phonebook.c -o bin/phonebook.o

clean:
	rm -rf bin main
