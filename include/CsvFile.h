#include<iostream>
#include<bits/stdc++.h>
#include "File.h"
class CsvFile : public File
{
  private:
      std::vector<std::vector<std::string>> matrix;
      
  protected:
      std::string read_file();
      void write_file(std::string data_to_write);

  public :
      CsvFile(std::string file_nm, std::string file_ext);
      void process_file();


};
