#define DO_CHECK(EXPR) check((EXPR), __FUNCTION__, __FILE__, __LINE__) 
#include <iostream>
#include "huffman_test.h"
#include "huffman.h"

void HuffmanTest::test_read_fin() {
	std::ifstream fin("input_testing_file.txt", std::ifstream::binary);

	HuffmanArchiver huff;
	huff.read_fin(fin);
	DO_CHECK(huff.data.freq[(int)'A'] == 4);
	DO_CHECK(huff.data.freq[(int)'1'] == 5);
	DO_CHECK(huff.data.freq[(int)'z'] == 7);
	DO_CHECK(huff.data.freq[(int)'p'] == 0);
	DO_CHECK(huff.data.freq[(int)'T'] == 17);
} 

void HuffmanTest::test_build_tree() {
	std::ifstream fin("input_testing_file.txt", std::ifstream::binary);
	HuffmanArchiver huff;
	huff.read_fin(fin);
	huff.build_tree();

	int sum_freq = 0;

	for (int i = 0; i < num_of_symbols; i++)
		sum_freq += huff.data.freq[i];
	
	DO_CHECK(huff.data.root != NULL);
	DO_CHECK(huff.data.root->frequency() == sum_freq);
}

void HuffmanTest::test_build_codes() {
	std::ifstream fin("input_testing_file.txt", std::ifstream::binary);
	HuffmanArchiver huff;
	
	huff.read_fin(fin);
	huff.build_tree();
	huff.build_codes(huff.data.root, "");	

	for (int i = 0; i < num_of_symbols; i++)
		for (int j = i + 1; j < num_of_symbols; j++)
			if (huff.data.freq[i] != 0 && huff.data.freq[j] != 0 && huff.data.freq[i] <= huff.data.freq[j]) 
				DO_CHECK(huff.data.codes[i].size() >= huff.data.codes[j].size());
			else if (huff.data.freq[i] != 0 && huff.data.freq[j] != 0)
				DO_CHECK(huff.data.codes[i].size() <= huff.data.codes[j].size());
}

void HuffmanTest::test_compress() {
	HuffmanArchiver huff1, huff2;
	
	std::ifstream fin("input_testing_file.txt", std::ifstream::binary);
	std::ofstream fout("output_testing_file.txt", std::ofstream::binary);
	
	huff1.compress(fin, fout);

	fout.close();

	std::ifstream fin2("output_testing_file.txt", std::ifstream::binary);
	std::ofstream fout2("check_testing_file.txt", std::ofstream::binary);
	
	huff2.decompress(fin2, fout2);
	
	fout2.close();

	fin.clear();
	fin.seekg(0, std::ios::beg);

	std::ifstream fcheck("check_testing_file.txt", std::ifstream::binary);

	char buff1[64], buff2[64];

	while (!fin.eof() && !fcheck.eof()) {
		fin.read(buff1, sizeof(buff1));
		fcheck.read(buff2, sizeof(buff2));

		for (int i = 0; i < sizeof(buff1); i++) {
			DO_CHECK(buff1[i] == buff2[i]);
		}
	}
}

void HuffmanTest::runAllTests() {
	test_read_fin();
	test_build_tree();
	test_build_codes();
	test_compress();
}

