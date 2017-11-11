#ifndef __HUFFMAN_TEST_H__
#define __HUFFMAN_TEST_H__     
#include "autotest.h"

class HuffmanTest : public Test {
public:
	void test_read_fin();	
	void test_build_tree();
	void test_build_codes();
	void test_compress();

	void runAllTests();
};

#endif
