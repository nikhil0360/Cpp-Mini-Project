#ifndef DLFile_H
#define DLFile_H
#include <string>
#include <vector>
#include "File.h"
using namespace std;
class DLFile : public File
{

public:
    DLFile(string file_nm, string file_ext);
    ~DLFile(){};
    void convertStringToCharArray(char *str, string text);
    void splitByCommas(char *str, vector<string> &labels);
    void process_file();
};
#endif

/*
Use a file with “Edge list”, labels, and weighted edges.
◦ Read the file.
◦ Sort the vertices/nodes based on its degree, and rank it based on the descending order of degree. 
◦ Degree of a node is computed as the sum of the weights of all the edges sharing the node.
◦ Re-index the nodes based on its rank.
◦ Filter the graph nodes to contain only the top 50% of the nodes in the descending order, and the edges which are between the filtered nodes. 
◦ Output the filtered graph in the UCINET DL format.
*/