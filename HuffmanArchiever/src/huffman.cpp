#include "huffman.h"
#include <fstream>
#include <vector>
#include <set>

TreeNode::TreeNode(int fr, TreeNode *l, TreeNode *r, char s) : freq(fr), left(l), right(r), symb(s) {}


std::string MyException::return_reason() const {
	return reason;
}

HuffmanData::HuffmanData() : root(NULL), num_of_bytes(0) {
	for (int i = 0; i < num_of_symbols; i++) {
		freq[i] = 0;
		codes[i] = "";
	}
}

HuffmanData::~HuffmanData() {
	delete_tree(root);
}                 

void HuffmanData::delete_tree(TreeNode * t) {
	if (t == NULL)
		return;
	delete_tree(t->left_node());
	delete_tree(t->right_node());
	delete t;
}

void HuffmanArchiver::compress(std::ifstream & fin, std::ofstream & fout) {
	read_fin(fin);
	build_tree();
	if (data.root)	
		build_codes(data.root, "");
	print_fout(fin, fout);
}

void HuffmanArchiver::read_fin(std::ifstream & fin) {
	unsigned char c[size_of_buff];
	while (!fin.eof()) {
		fin.read((char *)c, sizeof(c));
		int num_of_read = fin.gcount();		
		for (int i = 0; i < num_of_read; i++)
			data.freq[c[i]]++;	
	}
}

bool comp (TreeNode *a, TreeNode *b) {
	return a->frequency() < b->frequency();
}

void HuffmanArchiver::build_tree() {
	std::multiset <TreeNode*, bool(*)(TreeNode*, TreeNode*)> st(&comp);
	
	for (int i = 0; i < num_of_symbols; i++) {
		if (data.freq[i] == 0)
			continue;

		TreeNode *nd = new TreeNode(data.freq[i], NULL, NULL, i);
		st.insert(nd);
	}

	if (!st.size())
		return;
	
	while (st.size() > 1) {
		TreeNode* p1 = *(st.begin());
		st.erase(st.begin());

		TreeNode* p2 = *(st.begin());
		st.erase(st.begin());

		TreeNode *nw = new TreeNode(p1->frequency() + p2->frequency(), p1, p2, 0);
		st.insert(nw);
	}	

	data.root = *(st.begin());
}

void HuffmanArchiver::build_codes(TreeNode *p, std::string code) {
	if (p->left_node() == NULL) {
		if (!code.size())
			code += "0";
		
		data.codes[p->symbol()] += code;
		return;
	}

	build_codes(p->left_node(), code + "0");
	build_codes(p->right_node(), code + "1");
}

void HuffmanArchiver::print_fout(std::ifstream & fin, std::ofstream & fout) {
	fout.write((const char *)data.freq, sizeof(data.freq));

	fin.clear();
	fin.seekg(0, std::ios::beg);
	
	unsigned char c[size_of_buff];
	BitAccum bit_accum;

	while (!fin.eof()) {
		fin.read((char *)c, sizeof(c));
		int num_of_read = fin.gcount();		
		for (int i = 0; i < num_of_read; i++) {
			for (size_t j = 0; j < data.codes[c[i]].size(); j++)
				bit_accum.push_bit(data.codes[c[i]][j] - '0', fout);
		}
	}
	bit_accum.write_rem(fout);
	data.num_of_bytes = bit_accum.num_of_bytes_in_file();
}

void HuffmanArchiver::compress_print_statistic() const {
	if (!data.root)
		std::cout << 0 << std::endl;
	else
		std::cout << data.root->frequency() << std::endl;
	std::cout << data.num_of_bytes << std::endl;
	std::cout << sizeof(data.freq) << std::endl;	
}

void HuffmanArchiver::decompress(std::ifstream & fin, std::ofstream & fout) {
	read_freq(fin);
	build_tree();
	if (data.root)
		build_codes(data.root, "");
	recover_text(fin, fout);
}

void HuffmanArchiver::read_freq(std::ifstream & fin) {
	fin.read((char *)data.freq, sizeof(data.freq));
}

void HuffmanArchiver::recover_text(std::ifstream & fin, std::ofstream & fout) {
	if (!data.root)
		return;
	size_t len = data.root->frequency();
	size_t i = 0;

	BitAccum bit_accum;
	bit_accum.set_pos_decompress();

	while (i < len) {
		TreeNode *t = data.root;

		while (t->left_node() != NULL) {
			if (bit_accum.next_bit(fin))	
				t = t->right_node();
			else
				t = t->left_node();
		}   
		fout.write((const char *)t->symbol_point(), sizeof(t->symbol()));
		i++;
	}
	data.num_of_bytes = bit_accum.num_of_bytes_in_file();
}

void HuffmanArchiver::decompress_print_statistic() const {
	std::cout << data.num_of_bytes << std::endl;
	if (!data.root)
		std::cout << 0 << std::endl;
	else
		std::cout << data.root->frequency() << std::endl;
	std::cout << sizeof(data.freq) << std::endl;	
}


BitAccum::BitAccum() : accum(0), pos(7), num_of_bytes(0) {}

void BitAccum::push_bit(bool bit, std::ofstream & fout) {
	if (pos < 0) {
		fout.write(&accum, 1);
		num_of_bytes++;
		pos = 7;
		accum = 0;	
	}
	accum |= (bit << pos);
	pos--;
}

void BitAccum::write_rem(std::ofstream & fout) {
	if (pos != 7) {
		fout.write(&accum, 1);
		num_of_bytes++;
	}		
}

void BitAccum::set_pos_decompress() {
	pos = -1;
}

bool BitAccum::next_bit(std::ifstream & fin) {
	if (pos == -1) {
		fin.read(&accum, 1);
		num_of_bytes++;
		pos = 7;
	}
	bool bit = 1 & (accum >> pos);
	pos--;
	return bit;
}

int BitAccum::num_of_bytes_in_file() const {
	return num_of_bytes;
}

