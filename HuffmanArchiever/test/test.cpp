#include <stdio.h>
#include "huffman_test.h"

int main() {
	HuffmanTest ht;
	ht.runAllTests();
	HuffmanTest::showFinalResults();
	return 0;
}
