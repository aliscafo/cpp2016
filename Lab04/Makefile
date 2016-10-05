all: bin ms_cli
bin:
	mkdir -p bin
ms_cli: bin/main.o bin/ms_cli.o bin/merge_sort.o
	gcc bin/main.o bin/ms_cli.o bin/merge_sort.o -o ms_cli
bin/main.o: source/main.c include/ms_cli.h include/merge_sort.h 
	gcc -c source/main.c -o bin/main.o
bin/ms_cli.o: source/ms_cli.c 
	gcc -c source/ms_cli.c -o bin/ms_cli.o
bin/merge_sort.o: source/merge_sort.c 
	gcc -c source/merge_sort.c -o bin/merge_sort.o
clean:
	rm -rf bin ms_cli


	
	