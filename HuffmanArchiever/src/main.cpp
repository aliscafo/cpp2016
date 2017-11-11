#include <stdio.h>
#include <iostream>
#include <fstream>
#include "huffman.h"

class ReadKeys {
private:	
	std::string fin, fout;
	char type;
	size_t i;
	bool is_fin, is_fout;

public:
	ReadKeys();
	void read(size_t argc, char ** argv);
	bool is_archiving();
	std::string fin_name();
	std::string fout_name();
	void reset();
};

ReadKeys::ReadKeys() : fin(""), fout(""), type(0), i(1), is_fin(0), is_fout(0) {}

void ReadKeys::reset() {
	fin = "";
	fout = "";
	type = 0;
	i = 1;
	is_fin = 0;
	is_fout = 0;	
}

std::string ReadKeys::fin_name() {
	return fin;
}

std::string ReadKeys::fout_name() {
	return fout;
}

void ReadKeys::read(size_t argc, char ** argv) {
	if (argc != 6) 
		throw MyException("Incorrect parameters!");

	while (i < argc) {
		std::string t(argv[i]);

		if (t == "-f" || t == "--file") {
			fin += (std::string)argv[i + 1];
			is_fin = 1;
			i += 2;
		}
		else if (t == "-o" || t == "--output") {
			fout += (std::string)argv[i + 1];
			is_fout = 1;
			i += 2;
		}
		else if (t == "-c" || t == "-u") {
			type = argv[i][1];
			i++;
		}
		else 
			throw MyException("Unknown parameter!");
	}

	if (!is_fin || !is_fout || !type)
		throw MyException("Wrong key(s)! Try again.");
}

bool ReadKeys::is_archiving() {
	return (type == 'c');
}


int main (int argc, char **argv) {
	ReadKeys rf;
	
	try {
		rf.read(argc, argv);
	}
	catch(MyException & e) {
		std::cout << e.return_reason() << std::endl;  
		return 0;
	} 

	
	std::ifstream fin(rf.fin_name().c_str(), std::ifstream::binary);
	std::ofstream fout(rf.fout_name().c_str(), std::ofstream::binary);

	if (!fin.is_open()) {
		std::cout << "Input file couldn't be open!\n";
		return 0;
	}
	if (!fout.is_open()) {
		std::cout << "Output file couldn't be open!\n";
		return 0;
	}
    
    HuffmanArchiver huff;

	if (rf.is_archiving()) {		
		huff.compress(fin, fout);	
		huff.compress_print_statistic();
	}   
	else {
		huff.decompress(fin, fout);
		huff.decompress_print_statistic();						
	}	
	
	return 0;
}

