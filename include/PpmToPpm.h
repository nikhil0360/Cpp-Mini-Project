//
// Created by Nikhil Agarwal
//
#ifndef MINIPROJECT_PPMTOPPM_H
#define MINIPROJECT_PPMTOPPM_H
#include "File.h"
using namespace std;
class PpmToPpm: public File{
private:

public:
    ~PpmToPpm();
    PpmToPpm();
    PpmToPpm(string full_file_name, string extension);
    void process_file();
};


#endif //MINIPROJECT_PPMTOPPM_H
