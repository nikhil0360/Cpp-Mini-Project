#ifndef TXTFILE_H
#define TXTFILE_H
#include <bits/stdc++.h>
#include "File.h"

class TxtFile: public File {
private:
	std::unordered_map<std::string, size_t> stats;

public:
	TxtFile();
	TxtFile(std::string filename, std::string ext);
	~TxtFile();

	void generate_stats();
	std::unordered_map<std::string, size_t> get_stats();
	void process_file();

};

#endif