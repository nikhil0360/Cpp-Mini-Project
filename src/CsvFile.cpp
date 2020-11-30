#include<iostream>
#include<bits/stdc++.h>
#include "../include/CsvFile.h"


CsvFile::CsvFile(std::string file_nm,std::string file_ext) : File(file_nm, file_ext){}

void CsvFile::process_file()
{
  std::string data = this->CsvFile::read_file();
  this->CsvFile::write_file(data);
}

std::string CsvFile::read_file()
{
  std::string str = "";
  std::ifstream fileinp;
  fileinp.open(this->File::get_file_name());

  std::string l,w;

  std::vector<std::string> row;
  int noOfrows =0 ;

  while(!fileinp.eof())
  {
    row.clear();
    getline(fileinp,l);

    // cout<<l<<endl;
    std::stringstream s(l);

    while(getline(s,w,','))
    {
      row.push_back(w);
    }
    if(row.size() != 0)
      matrix.push_back(row);
  }

  return str;
}
void CsvFile::write_file(std::string data_to_write)
{
  int nrows = matrix[0].size(),ncol = matrix.size();
  std::string trans_matrix[nrows][ncol];



  for(int i=0;i<nrows;i++)
  {
    for(int j=0;j<ncol;j++)
    {
      trans_matrix[i][j] = matrix[j][i];
    }

  }

  std::ofstream changed_csv;
  changed_csv.open("out_" + this->File::get_file_name());

  for(int i=0;i<nrows;i++)
  {
    for(int j=0;j<ncol-1;j++)
    {
        changed_csv << trans_matrix[i][j]<<",";
    }
    changed_csv << trans_matrix[i][ncol - 1]<<"\n";
  }
  changed_csv.close();
}
