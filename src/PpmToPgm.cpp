/*
    Task Number : 07
    Made By: Ankit Agrawal
    Roll No.: IMT2019010
    Group Number: 10

    Short description of program : This program reads in a .ppm file
                                   and converts it to a .pgm file, and
                                   the image that is contained in this
                                   .pgm file is a grayscale image
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

#include "../include/File.h"
#include "../include/PpmToPgm.h"

using namespace std;

PpmToPgm :: PpmToPgm() : File()      //This is the default constructor for class PpmToPgm
{
    image_height = 0;       //Initialize image_height to 0
    image_width = 0;        //Initialize image_width to 0
    maximum_RGB_value = 0;      //Initialize maximum_RGB_value to 0

    total_RGB_count = 0;        //Initialize total_RGB_count to 0

    maxi_val = 0;       //Initialize maxi_val to 0

    conversion_successful = false;      //Initially, the file has not been converted. So we set conversion_successful to false
}

PpmToPgm :: PpmToPgm(string file_name, string file_ex) : File(file_name, file_ex)
{
    image_height = 0;       //Initialize image_height to 0
    image_width = 0;        //Initialize image_width to 0
    maximum_RGB_value = 0;      //Initialize maximum_RGB_value to 0

    total_RGB_count = 0;        //Initialize total_RGB_count to 0

    maxi_val = 0;       //Initialize maxi_val to 0

    conversion_successful = false;      //Initially, the file has not been converted. So we set conversion_successful to false

}

PpmToPgm :: ~PpmToPgm()
{
    //Do nothing, as no dynamic memory has been allocated
}

void PpmToPgm :: process_file()     //This function implements tool for converting .ppm to .pgm
{
    input_file.open(get_file_name(), ios::in);       //We open the input file
    output_file.open("IMT2019010_output.ascii.pgm", ios::out);       //We open the output file

    /*
        We divide the life cycle of program into stages

        Stage 1: Check for presence of "P3"
        Stage 2: Check for width
        Stage 3: Check for height
        Stage 4: Check for maximum R/G/B value
        Stage 5: Input all data and output .pgm file

        In case an error occurs during an stage, the following steps
        are taken to recover correctly:

        1. If error occurs in Stage 1/2/3 or 4, then the output file
           is a .pgm with dimensions 10 * 10, and it is a black image
           which means all the pixel values are 0 in the file. This part
           of error handling is done by the function

           void handle_error();

        2. If error occurs in stage 5, then the output file is a
           .pgm file, whose dimensions depends on the number of values
           that have been already written into the .pgm file. The remaining
           values are filled with 0, indicating a partially black image.
           This part of error handling is done by the function:

           void handle_stage_5_error();
    */


    long int current_stage = 1;      //When we begin reading a file, we set the current_stage to 1

    if(input_file.is_open() && output_file.is_open())       //We check if we were able to open the input and output files successfully or not
    {
        long int current_R = 0;      //This variable is used to keep track of current value of R (Red) read from the .ppm file
        long int current_G = 0;      //This variable is used to keep track of current value of G (Red) read from the .ppm file
        long int current_B = 0;      //This variable is used to keep track of current value of B (Red) read from the .ppm file

        bool more_data_needed = false;      //This variable stores True if we need to read more R/G/B values from the file, otherwise file. Initially it is false, as we have not yet read values

        while(!input_file.eof())        //Now that the files have been opened successfully, we start reading the input file, until we reach its end
        {
            string current_line = read_file();        //This variable stores the line being read from the input file

            if((long int)(current_line.size()) == 0)     //If a line size is 0, then we ignore it
            {
                continue;       //We move forward to read the next line
            }
            else if(current_line[0] == '#')     //If the current line starts with a '#', then it is a comment, and can be ignored
            {
                continue;       //We move forward to read the next line
            }
            else        //Otherwise, the lines contains some un-commented data, we now parse that data
            {
                vector <string> valid_data = parse_line(current_line);      //We now store values separated by space from the current line (comments are ignored)
                bool flag_invalid_input = false;        //This flag stores true if the file becomes invalid due to current line being read from the file

                for(long int j = 0 ; j < (long int) (valid_data.size()); j++)     //Now, for each value read on the line, we parse those values
                {
                    if(current_stage == 1)      //If we had to execute the first stage
                    {
                        bool stage_success = execute_stage_1(valid_data[j]);        //We execute the first stage
                        if(stage_success == true)       //If the first stage executes successfully...
                        {
                            current_stage += 1;     //We increment the value of current_stage, so that we can move to next stage
                            continue;       //We continue the execution of program
                        }
                        else        //If the first stage execution failed for some reason...
                        {
                            handle_error();      //We handle error for this stage
                            flag_invalid_input = true;      //We set the flag_invalid_input to true, indicating that the file is invalid
                            break;      //We break out of the loop
                        }
                    }

                    if(current_stage == 2)      //If we had to execute the second stage
                    {
                        bool stage_success = execute_stage_2(valid_data[j]);        //We execute the second stage
                        if(stage_success == true)       //If the second stage executed successfully...
                        {
                            current_stage += 1;     //We increment the value of current_stage, so that we can move to next stage
                            continue;       //We continue the execution of program
                        }
                        else        //If the second stage execution failed for some reason...
                        {
                            handle_error();      //We handle error for this stage
                            flag_invalid_input = true;      //We set the flag_invalid_input to true, indicating that the file is invalid
                            break;      //We break out of the loop
                        }
                    }

                    if(current_stage == 3)      //If we had to execute the third stage
                    {
                        bool stage_success = execute_stage_3(valid_data[j]);        //We execute the third stage
                        if(stage_success == true)       //If the third stage executed successfully...
                        {
                            current_stage += 1;     //We increment the value of current_stage, so that we can move to next stage
                            continue;       //We continue the execution of program
                        }
                        else        //If the third stage execution failed for some reason...
                        {
                            handle_error();      //We handle error for this stage
                            flag_invalid_input = true;      //We set the flag_invalid_input to true, indicating that the file is invalid
                            break;      //We break out of the loop
                        }
                    }

                    if(current_stage == 4)      //If we had to execute the fourth stage
                    {
                        bool stage_success = execute_stage_4(valid_data[j]);        //We execute the fourth stage
                        if(stage_success == true)       //If the fourth stage executed successfully...
                        {
                            //We print a series of newlines to the output file, because we will write the header information ("P2", width, height, and maximum value) at the end
                            write_file("\n");
                            write_file("\n");
                            write_file("\n");
                            write_file("\n");
                            write_file("\n");
                            write_file("\n");
                            write_file("\n");
                            write_file("\n");
                            write_file("\n");
                            current_stage += 1;     //We increment the value of current_stage, so that we can move to next stage
                            more_data_needed = true;
                            continue;       //We continue the execution of program
                        }
                        else        //If the fourth stage execution failed for some reason
                        {
                            handle_error();      //We handle error for this stage
                            flag_invalid_input = true;      //We set the flag_invalid_input to true, indicating that the file is invalid
                            break;      //We break out of loop
                        }
                    }

                    if(current_stage == 5)      //If we had to execute the fifth stage...
                    {
                        long int stage_success = execute_stage_5(valid_data[j], current_R, current_G, current_B);        //We execute the fifth stage
                        if(stage_success == -1)     //If the fifth stage returns -1, then the stage has failed to executed due to error in the file
                        {
                            more_data_needed = false;
                            handle_stage_5_error();      //So we handle the error for this stage
                            flag_invalid_input = true;      //We set flag_invalid_input to true, indicating that the file is invalid
                            break;      //We break out of loop
                        }
                        else if(stage_success == 0)     //If the fifth stage returns -1, then it means that we have to read more R/G/B values
                        {
                            continue;       //So we continue the execution of the loop
                        }
                        else        //If the fifth stage returns 1, then the stage 5 execute successfully
                        {
                            current_stage += 1;     //We increment the current stage, to move to the next stage
                            more_data_needed = false;
                        }
                    }

                    if(current_stage == 6)      //If we enter the sixth stage, then it means that the program has processed the input file fully
                    {
                        conversion_successful = true;       //So we set conversion_successful to true
                        break;      //We break out of the loop
                    }
                }

                if(flag_invalid_input == true)      //Now, if we fail to convert the program successfully...
                {
                    conversion_successful = false;      //We set conversion_succesful to false, indicating that the input file couldn't be converted successfully
                    break;      //We break out of loop
                }
                else if(conversion_successful == true)      //If the file conversion was successful, we write the header information into the file
                {
                    output_file.seekp(0, ios::beg);     //We move to the beginning of the file
                    write_file("P2");       //We write "P2"
                    write_file("\n");
                    write_file(to_string(image_width));     //We write the image width
                    write_file(" ");
                    write_file(to_string(image_height));        //We write the image height
                    write_file("\n");
                    write_file(to_string(maxi_val));        //We write the maximum value which is has been written into the output file
                    write_file("\n");
                    break;      //We break out of the loop
                }
            }
        }

        if(more_data_needed == true)        //We check if we reached the end of while, while needing more data to write
        {
            handle_stage_5_error();     //If so, then we handle the error
        }

        input_file.close();     //We close the input file
        output_file.close();        //We close the output file
    }
}

vector <string> PpmToPgm :: parse_line(string next_line)      //This function parses the line given to it, extracting values separated by a space ' ', and ignoring comments
{
    long int index = 0;      //This variable stores the position at which we are at the current line

    vector <string> to_return;      //This vector stores the individual values of the strings

    while(index < static_cast <long int> (next_line.size()))     //We now starting parsing the input
    {
        string current_input = "";      //This will store the current segment of the input (Which could be either to Add a number, create a new DataSequence object, store delimiters, or
        while((index < (long int)(next_line.size())) && (next_line[index] != ' '))      //As segments are separated by space (' '), we will use space to separate segments
        {
            current_input.push_back(next_line[index]);      //We copy the current character in the current segment
            index += 1;     //We increment index
        }

        if((long int)(current_input.size()) != 0 && current_input[0] == '#')     //If we encounter a '#', then we stop extracting more values, as the remaining values need not be readed
        {
            break;      //So we break out of loop
        }
        else if((long int)(current_input.size()) != 0)       //If the value is not a comment and not a space ' '
        {
            bool is_comment_present = false;

            string final_string_to_push = "";
            for(long int j = 0 ; j < (long int) current_input.size(); j++)
            {
                if(current_input[j] != '#')
                {
                    final_string_to_push.push_back(current_input[j]);
                }
                else
                {
                    is_comment_present = true;
                    break;
                }
            }

            if(final_string_to_push.size() != 0)
            {
                to_return.push_back(final_string_to_push);     //We push the value in the vector to_return

                if(is_comment_present == true)
                {
                    break;
                }
            }
        }

        index += 1;     //We now increment index, as we might have broken out of above loop because of encountering a space
    }

    return to_return;       //We return the vector of values
}

long int PpmToPgm :: string_to_int(string to_convert)        //this function returns -1 if the quantity to_convert is floating or negative, or to_convert contains characters other than 0-9
{
    bool is_valid = true;       //This variable stores true if the string to_convert is a valid integer, otherwise it is false
    for(long int j = 0 ; j < (long int) (to_convert.size()); j++)     //We now start converting the string to integer
    {
        if(to_convert[j] < 48 || to_convert[j] > 57)        //If we find a character which is outside of the numbers 0 - 9
        {
            is_valid = false;       //Then the string is invalid, as it contains some other characters which are not needed
            break;      //So we break out of the loop
        }
    }
    if(is_valid == false)       //If the string is invalid...
    {
        return -1;      //Then we return -1
    }
    else        //Otherwise the string is valid, and now we convert it
    {
        reverse(to_convert.begin(), to_convert.end());      //To convert it, firstly we reverse the string
        long int converted_value = 0;        //This variable stores the integer value of the string to_convert
        for(long int j = (long int) (to_convert.size()) - 1; j >= 0; j--)     //We now start converting the given string to integer
        {
            converted_value += (to_convert[j] - 48);        //We convert each number in string to an int, and add it to converted_value
            converted_value *= 10;      //We multiple converted_value by 10, to make place for next number to be added
        }
        converted_value /= 10;      //Finally, we would have multiplied 10 one extra time, so we divide converted_value by 10, to get the correct answer
        return converted_value;     //We return the converted value
    }
}

bool PpmToPgm :: execute_stage_1(string data)     //This function checks for "P3". It returns true if found, otherwise false
{
    if(((long int) (data.size()) == 2) && data[0] == 'P' && data[1] == '3')      //We check if the string passed is indeed P3 or not
    {
        //Great! P3 has been found!
        return true;        //So we return true
    }
    return false;       //Otherwise we return false, indicating that the stage could not be completed successfully
}

bool PpmToPgm :: execute_stage_2(string data)     //This functions checks if width is present or not. It returns false if not present, otherwise true
{
    long int data_get = string_to_int(data);     //We try to convert the data to integer
    if(data_get <= 0)       //If the width we get is <= 0, then it is invalid, as width can't be 0
    {
        return false;       //So we return false
    }
    else        //Otherwise, the width is correct
    {
        image_width = data_get;     //We set the width of the image
        return true;        //We return true, indicating that the stage execution completed successfully
    }
}

bool PpmToPgm :: execute_stage_3(string data)     //This function checks if height is present or not. It returns false if not present
{
    long int data_get = string_to_int(data);     //We try to convert the data to integer
    if(data_get <= 0)       //If the height we get is <= 0, then it is invalid, as height can't be 0
    {
        return false;       //So we return false
    }
    else        //Otherwise the height is correct
    {
        image_height = data_get;        //We set the height of the image
        return true;        //We return true, indicating that the stage execution completed successfully
    }
}

bool PpmToPgm :: execute_stage_4(string data)     //This function finds the maximum R/G/B value present in the .ppm file
{
    long int data_get = string_to_int(data);     //We try to convert the maximum R/G/B value in the .ppm file to integer
    if(data_get <= 0 || data_get >= 65536)      //The value of maximum must be > 0 and < 65536, if not, then the file is invalid
    {
        return false;       //So we return false
    }
    else        //Otherwise, the maximum value is correct...
    {
        maximum_RGB_value = data_get;       //So we set the value of the variable maximum_RGB_value
        return true;        //We return true, indicating that the stage 4 executed successfully
    }
}

long int PpmToPgm :: execute_stage_5(string data, long int &current_R, long int &current_G, long int &current_B)     //This function write data to the output_stream
{
    /*
        This function returns the following values:

        1. Return value 1: A total of (width * height * 3) values have been read from the .ppm file, and conversion is successful
        2. Return value 0: We have not read (width * height * 3) values from the .ppm file, and require more values to make conversion successful
        3. Return value -1: We have detected the presence of invalid data in the file, and return -1 to indicate that the .ppm file is invalid
    */

    long int total_pixels = image_width * image_height * 3;      //We calculate the total R/G/B values that must be there in the .ppm file
    long int data_int = string_to_int(data);         //We try to convert the data passed into an integer
    if(data_int == -1)      //If the conversion is unsuccessful...
    {
        return -1;      //We return -1, indicating that the .ppm file is invalid
    }
    else if(data_int > maximum_RGB_value)       //If the data is more than maximum_RGB_value, then also the .ppm file is invalid
    {
        return -1;      //We return -1, indicating that the .ppm file is invalid
    }
    else if(total_RGB_count < total_pixels)     //Otherwise, the data is valid. We check if we have more value required before conversion is successful
    {
        if(total_RGB_count % 3 == 0)        //If the modulus of total RGB count is 0, then it means we have just read a R (Red) value
        {
            current_R = data_int;       //We update current_R
            total_RGB_count += 1;       //We increase total_RGB_count by 1
        }
        else if(total_RGB_count % 3 == 1)       //if the modulus of total_RGB_count is 1, then it means we have just read a G (Green) value
        {
            current_G = data_int;       //We update current_G
            total_RGB_count += 1;       //We increase total_RGB_count by 1
        }
        else        //If the modulus of total_RGB_count is 2, then it means that we have just read a B (Blue) value
        {
            current_B = data_int;       //We update the value of current_B
            total_RGB_count += 1;       //we increase total_RGB_count by 1

            float value_1 = (current_R * 0.3) + (current_G * 0.59) + (current_B * 0.11);        //Since now we have read R,G,B value, we convert it to grayscale
            long int value_to_enter = static_cast <long int> (value_1);       //We convert it to integer
            if(value_to_enter > maxi_val)       //If the current value to be written to the .pgm file is greater than the current maximum of all values in the .pgm file...
            {
                maxi_val = value_to_enter;      //We update the value of maxi_val
            }
            write_file(to_string(value_to_enter));        //We print the variable value_to_enter in the output .pgm file
            write_file("\n");
        }

        if(total_RGB_count == total_pixels)     //Now, if the total_RGB_count equals total_pixels, then it means that we have read and converted the file correctly
        {
            return 1;       //So we return 1
        }
        else        //Otherwise, we need to read more values
        {
            return 0;       //So we return 0
        }

    }
    else        //If none of the conditions above is satisfied, then also we can say that the file conversion is successful
    {
        return 1;       //So we return 1
    }
}

void PpmToPgm :: handle_error()        //Used for handling errors in Stages 1-4
{
    //We will simply print a 10 x 10 matrix black image
    write_file("P2");       //Output P2 on the file
    write_file("\n");
    write_file("10 10");        //Output width and height on the page
    write_file("\n");
    write_file("10");       //Output Maximum pixel value in the program
    write_file("\n");
    for(long int j = 0 ; j < 10; j++)        //Print the 10 x 10 matrix of 0
    {
        for(long int k = 0 ; k < 10; k++)
        {
            write_file("0");
            write_file(" ");
        }
        write_file("\n");        //Print the end of program
    }
}

void PpmToPgm :: handle_stage_5_error()  //Used for handling errors in Stage 5
{
    long int written_pixels = total_RGB_count/3;     //We find the number of pixels that have been written in the file
    long int expected_pixels = (image_height * image_width);     //We find the number of pixels that should've been written
    long int difference = (expected_pixels - written_pixels);        //We find the difference, and we will have to write these many pixels extra

    for(long int j = 0 ; j < difference ; j++)       //We write these many pixels...
    {
        write_file("0");
        write_file("\n");
    }

    output_file.seekp(0, ios::beg);       //Now we move to beginning of the file
    write_file("P2");       //We print P2 -- the magic number of the file
    write_file("\n");
    write_file(to_string(image_width));     //We print the image width in the output file
    write_file(" ");
    write_file(to_string(image_height));        //We print the image height in the output file
    write_file("\n");
    write_file(to_string(maxi_val + 1));        //We print the maximum value present in the file
}

string PpmToPgm :: read_file()
{
    if(input_file.is_open() == true && input_file.eof() == false)       //If check the file if its open, and if we have not reached its end
    {
        string read_line;       //Stores line read
        getline(input_file, read_line);     //We read the line
        return read_line;       //We return the read line
    }
    else        //Otherwise...
    {
        return "";      //We return empty string
    }
}

void PpmToPgm :: write_file(string data_to_write)       //Used for writing data
{
    if(output_file.is_open() == true)       //We check if the file is open or not
    {
        output_file<<data_to_write;     //If open, we write to the output file
    }
}
