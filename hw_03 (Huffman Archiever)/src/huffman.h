#include <iostream>
#include <fstream>
#include <vector>
#include <exception>

const int num_of_symbols = 256, size_of_buff = 512;

class MyException : public std::exception {
private:
	std::string reason;
public:
	MyException(const std::string & r) : reason(r) {};
	std::string return_reason() const;
	virtual ~MyException() throw() {}
};

class TreeNode {
private:
	int freq;
	TreeNode *left, *right;
	unsigned char symb;
public:
	TreeNode(int, TreeNode *, TreeNode *, char);

	int frequency() const { return freq; }
	TreeNode* left_node() const {	return left; }	               
	TreeNode* right_node() const { return right; }
	unsigned char symbol() const { return symb; }
	unsigned char * symbol_point() const { return (unsigned char *)&symb; }		            
};


class HuffmanData {
private:
	int freq[num_of_symbols];
	TreeNode *root;
	std::string codes[num_of_symbols];
	std::vector <bool> coded_text;
	int num_of_bytes;
	void delete_tree(TreeNode * t);
public:
	HuffmanData();
	~HuffmanData();

	friend class HuffmanArchiver;
	friend class HuffmanTest;
};

class HuffmanArchiver {
private:
	HuffmanData data;
	void read_fin(std::ifstream &);
	void build_tree();
	void build_codes(TreeNode *, std::string);
	void print_fout(std::ifstream &, std::ofstream &);

	void read_freq(std::ifstream &);
	void recover_text(std::ifstream &, std::ofstream &);
	void read_coded_text(std::ifstream &);
public:                                    
	void compress(std::ifstream &, std::ofstream &);		
	void compress_print_statistic() const;

	void decompress(std::ifstream &, std::ofstream &);
	void decompress_print_statistic() const;

	friend class HuffmanTest;
};


class BitAccum {
private:
	char accum;
	int pos, num_of_bytes;
public:
	BitAccum();
	void push_bit(bool, std::ofstream &);
	void write_rem(std::ofstream &);
	bool next_bit(std::ifstream &);
	void set_pos_decompress();
	int num_of_bytes_in_file() const;
};


