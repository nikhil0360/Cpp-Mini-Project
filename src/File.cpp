#include "../include/File.h"

File::File(){}
File::File(std::string file_nm, std::string file_ext) : file_name(file_nm), file_extension(file_ext){}
File::~File(){}

std::string File::get_file_name(){ return this->file_name; }
std::string File::get_file_extension(){ return this->file_extension; }

/* Returns string of the data inside the file. Terminates with error on failure */
std::string File::read_file(){
	std::string data = "";
	std::string temp_line;
	std::ifstream file(this->file_name);
	if(file){
		while(getline(file, temp_line)) data += temp_line + "\n";
	}
	else{
		std::cerr << "Input: No such file" << std::endl;
		exit(1);
	}

	return data;
}

/* Creates a (or writes to an existing) file with the string data */
void File::write_file(std::string data_to_write){
	std::ofstream file("out_" + this->file_name);
	if(file) file << data_to_write;
	else{
		std::cerr << "Output: Error generating output file" << std::endl;
		exit(1);
	}
}