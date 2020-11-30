/*
  Created by : Nikhil Agarwal
  Roll no. : IMT2019060
  Task : 2
  Group no. : 10

  Programs takes a .ppm file, and convert it from RBG to BGR
*/

#include "../include/PpmToPpm.h"
#include <iostream>

void PpmToPpm::process_file() {
    // read in file and store it in string
    string lines = this->read_file() ;

    // storing each line of data string, as a string in vector
    // this will help to process each nice easily
    vector<string> data ;
    istringstream ss(lines);
    string line;
    while (std::getline(ss, line)){
        data.push_back(line);
    }

    // output string, which will be stored as a .ppm file after all the processing
    string output;

    // step count, to look for magic number, width, height and maximum RGB value
    int step = 0 ;

    // variables required for output and processing
    string magicNum, width, height, maxVal ;
    vector<string> pixelVals ;
    string r = "0", g="0" ;

    // for handling missing values in the line
    // if handle is 1, we are missing 2 values g and b
    // if handle is 2, we are missing 1 values b
    int handle ;

    for(int i = 0; i<data.size(); i++){

        // if line starts with #, its a comment and we can ignore it
        if(data[i][0] == '#'){
            // appending commented line in the output without any change
            output += data[i] + "\n" ;
            continue;
        }

        vector<string> arr;

        // this snippet split the data taking space as a delimiter
        // but in the ppm file, it can be more than one space, so we need a more
        // better code

        // string temp;
        // stringstream s(data[i]);

        // while (getline(s,temp,' ')) {
        //     //splitting with spaces
        //     arr.push_back(temp);
        // }


        // handles multiple spaces are delimiter
        // seperate tokens and store them in vector<string> arr
        string word = "";
        for (auto x : data[i]){
          if(x == ' '){

            // if next character is space, and the word is not empty
            // add it to the arr

            // else do add
            if(word.size()!=0){
              arr.push_back(word);
              word = "";
            }
          }

          // add to string character wise, unless we encouter a space character
          else {
            word = word + x;
          }
        }

        // pushing the final word
        arr.push_back(word);

        // step 0 : magic Num
        if(step == 0){
          magicNum = arr[0] ;
          step++ ;
          output += magicNum + "\n" ;
        }

        // step 1 : width and height
        else if(step == 1){
          width = arr[0];
          height = arr[1];
          step++ ;
          output += width + " " + height + "\n" ;
        }

        // step 2 : max val of rgb pixel
        else if(step == 2){
          maxVal = arr[0];
          step++ ;
          output += maxVal + "\n" ;
        }

        // step 3 : individual pixel values
        else if(step == 3){

          // storing pixel values, which we will later manipulate
          for(int i = 0; i < arr.size(); i++){
            pixelVals.push_back(arr[i]);
          }

          // d will store the pixel value line by line to the output string
          string d;

          // when we miss 2 value in the previous line
          // we will take new value from line, and place the value it with
          // previous r

          if(handle == 1){
            d += arr[1] + " " + r + " " + arr[0] + " ";
            arr.erase(arr.begin());
            arr.erase(arr.begin());
            handle = 0 ;
          }

          // when we miss 1 value in the previous line
          // we will take new value from line, and place the value it with
          // previous r and g

          else if(handle == 2){
            d += arr[0] + " " + r + " " + g + " ";
            arr.erase(arr.begin());
            handle = 0 ;
          }

          // manipulating values from RGB to BRG
          while(arr.size() >= 3){
              d += arr[2] + " " + arr[0] + " " + arr[1] + " ";
              arr.erase(arr.begin());
              arr.erase(arr.begin());
              arr.erase(arr.begin());
          }
          output += d + "\n" ;

          // if some values are left, they have missing values on that line
          // so we will store these values and pair them with next line values

          // when g and b are missing
          if(arr.size()>0){
            if(arr.size() == 1){
              r = arr[0];
              arr.erase(arr.begin());
              handle = 1 ;
            }

            // when b is missing
            else if(arr.size() == 2){
              r = arr[0];
              arr.erase(arr.begin());
              g = arr[0];
              arr.erase(arr.begin());
              handle = 2 ;
            }
          } // end-of the if condition

        }

    } // end-of for loop for data

    // now send the output string to store it as a .ppm file
    this->write_file(output);

} // end-of process_file

PpmToPpm::PpmToPpm(string full_file_name, string extension):File(full_file_name, extension) {
    // this will create the File object and then we will call the process function
}

PpmToPpm::PpmToPpm(){
  // default
}

PpmToPpm::~PpmToPpm(){
  // default
}
