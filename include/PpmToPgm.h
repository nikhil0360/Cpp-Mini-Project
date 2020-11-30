#ifndef PPM_TO_PGM_H_INCLUDED
#define PPM_TO_PGM_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "File.h"

using namespace std;

class PpmToPgm : public File
{
private:
    ifstream input_file;        //Used as a stream object for input file
    ofstream output_file;       //Used as a stream object for output file

    long int image_width;        //Stores the width of the images
    long int image_height;       //Stores the height of the image
    long int maximum_RGB_value;      //Stores the maximum R/G/B value present in .ppm file
    bool conversion_successful;     //It is true if the conversion is successful, otherwise false

    long int total_RGB_count;        //This variable keeps count of the total R/G/B values in the .ppm file
    long int maxi_val;       //This variable stores the maximum value of the values obtained after converting RGB value to single value using formula given in problem statement

public:
    PpmToPgm();       //Default constructor for the class PpmToPgm
    PpmToPgm(string file_name, string file_ex);      //Overloaded constructor for class PpmToPgm
    ~PpmToPgm();
    void process_file();

    /*
        We divide the life cycle of program into stages

        Stage 1: Check for presence of "P3"
        Stage 2: Check for width
        Stage 3: Check for height
        Stage 4: Check for maximum R/G/B value
        Stage 5: Input all data and output .pgm file
    */

    bool execute_stage_1(string data);      //This function executes the First Stage of conversion
    bool execute_stage_2(string data);      //This function executes the Second Stage of conversion
    bool execute_stage_3(string data);      //This function executes the Third Stage of conversion
    bool execute_stage_4(string data);      //This function executes the Fourth Stage of conversion
    long int execute_stage_5(string data, long int &current_R, long int &current_G, long int &current_B);      //This function executes the Fifth (and final) Stage of converison

    void handle_error();     //This function handles the error that might occur during Stages 1,2,3 and 4
    void handle_stage_5_error();     //This function handles the error that might occur during Stage 5

    string read_file();     //We override the base virtual function, reads from file
    void write_file(string data_to_write);      //We override the base virtual function, writes to file

    vector <string> parse_line(string next_line);       //This function breaks a line of text separated by spaces, and remove comments (if present) in the .ppm file

    long int string_to_int(string to_convert);       //This function converts integer (in string) to integer (in int)
};

#endif // PPM_TO_PGM_H_INCLUDED
