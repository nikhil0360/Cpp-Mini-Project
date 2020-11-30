#include "../include/TxtFile.h"
#include <bits/stdc++.h>

TxtFile::TxtFile(){}
TxtFile::TxtFile(std::string filename, std::string ext) : File(filename, ext){
	this->TxtFile::generate_stats();
}
TxtFile::~TxtFile(){};

void TxtFile::generate_stats(){
	std::unordered_map<std::string, size_t> stats;
	std::string data = this->File::read_file();
	stats["lines"] = 0; stats["words"] = 0, stats["chars"] = 0, stats["chars_ns"] = 0, stats["bytes"] = 0;
	if(data.compare("")) stats["lines"] = 0;
	for(int i = 0; i < data.size(); i++){
		stats["bytes"]++;
		switch(data[i]){
			case '\n': stats["lines"]++; stats["words"]++; stats["chars"]++; break;
			case ' ':{
				stats["chars"]++;
				if(i + 1 < data.size() && (data[i+1] != ' ' && data[i+1] != '\n' && data[i+1] != '	')) stats["words"]++;
				break;
			}
			case '	':{
				stats["chars"]++;
				if(i + 1 < data.size() && (data[i+1] != ' ' && data[i+1] != '\n' && data[i+1] != '	')) stats["words"]++;
				break;
			}
			case '\0': break;
			default: stats["chars"]++; stats["chars_ns"]++; break;
		}

	}

	this->stats = stats;
}

std::unordered_map<std::string, size_t> TxtFile::get_stats(){ return this->stats; }

void TxtFile::process_file(){
	std::string header = "";

	std::string lines = "Lines: ";
	std::string words = "Words: ";
	std::string chars = "Characters (with spaces): ";
	std::string chars_ns = "Characters (no spaces): ";
	std::string bytes = "Bytes: ";

	header += lines + std::to_string(this->stats["lines"]); header.push_back('\n');
	header += words + std::to_string(this->stats["words"]); header.push_back('\n');
	header += chars + std::to_string(this->stats["chars"]); header.push_back('\n');
	header += chars_ns + std::to_string(this->stats["chars_ns"]); header.push_back('\n');
	header += bytes + std::to_string(this->stats["bytes"]); header.push_back('\n');
	header.push_back('\n'); // padding between header and data

	this->File::write_file(header + this->read_file());
}