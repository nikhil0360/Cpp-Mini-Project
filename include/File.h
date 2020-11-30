#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED
#include <bits/stdc++.h>
#include <fstream>

class File
{
private:
    std::string file_name;       // full file name
    std::string file_extension;  // file extension
protected:
    /* Reads input file */
    virtual std::string read_file();
    /* Creates output file */
    virtual void write_file(std::string data_to_write);
public:
    File();
    File(std::string file_nm, std::string file_ext);
    ~File();

    std::string get_file_name();
    std::string get_file_extension();

    virtual void process_file() = 0;
};


#endif // FILE_H_INCLUDED
