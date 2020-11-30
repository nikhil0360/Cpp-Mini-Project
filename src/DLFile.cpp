#include "../include/DLFile.h"
#include <bits/stdc++.h>
#include <string.h>
using namespace std;
DLFile::DLFile(string file_nm, string file_ext) : File(file_nm, file_ext)
{
}
void DLFile::convertStringToCharArray(char *str, string text) //function to convert strin to char array
{
    for (int i = 0; i < text.length(); i++)
        str[i] = text[i];
}
void DLFile::splitByCommas(char *str, vector<string> &labels)
{
    char *duplicate = new char[strlen(str)];
    //Creating a duplicate of the sequence seperated by commas so as to split it using commas without affecting the original split
    for (int i = 0; i < (int)strlen(str); i++)
    {
        duplicate[i] = str[i];
    }
    char *vector_token;
    char *vector_ref = duplicate; //required for strtok_r to keep a reference

    int vector_index = 0;
    int vec_count = 0;

    while ((vector_token = strtok_r(vector_ref, ",", &vector_ref))) // Splitting using commas
    {
        string label = "";
        for (int i = 0; i < strlen(vector_token); i++)
        {
            if (vector_token[i] != ' ')
                label += vector_token[i];
        }
        labels.push_back(label); //adding the label to the vector
    }
    delete[] duplicate;
}
void DLFile::process_file()
{
    string fileContent = read_file();
    stringstream reader(fileContent);

    string line;
    int count = 0;
    string line1, line2, line3, line5;
    vector<string> labels;
    int numNodes;
    vector<pair<int, string>> *nodes;

    while (getline(reader, line, '\n')) //splitting the string by newline character
    {
        if (count == 0)
        { //extracting number of nodes;
            stringstream sn(line);
            string val;
            getline(sn, val, '=');
            getline(sn, val, '='); //the value in string
            numNodes = stoi(val);  //storing the number of nodes by converting from string to integer
            line1 = line;          //"DL n=" line
            while (line1[line1.length() - 1] != '=')
                line1.pop_back();
        }
        if (count == 1)
            line2 = line; //"format = edgelist" line
        if (count == 2)
            line3 = line; // "labels:" line
        if (count == 3)
        {
            char *str1 = new char[line.length()];
            convertStringToCharArray(str1, line);
            //converting string to char array, passing it to split by commas method where the labels are extracted and added to a array
            splitByCommas(str1, labels);
            delete[] str1;
        }
        if (count == 4)
        {
            line5 = line; // "data:" line
            nodes = new vector<pair<int, string>>[numNodes + 1];
            while (getline(reader, line, '\n')) // finally taking input of all the edges
            {
                stringstream s(line);
                int u, v; //nodes
                string w; //the weight is maintained as string for display purposes to retain the original value with precision given in input
                s >> u;
                s >> v;
                s >> w;
                nodes[u].push_back(make_pair(v, w)); //adding the edge to the graph
            }
        }
        count += 1;
    }

    vector<pair<double, int>> degrees;                               //maintains the degrees of the nodes
    pair<bool, int> *topDegrees = new pair<bool, int>[numNodes + 1]; //an  array to check if a node is in top 50% or nor in O(1), and also get it's rank for reindexing

    double weights[numNodes + 1];
    for (int i = 1; i < numNodes + 1; i++)
    {
        weights[i] = 0;                      //initializing the weights array with 0's
        topDegrees[i] = make_pair(false, 0); //initializing the topDegrees array
    }
    for (int i = 1; i < numNodes + 1; i++)
    {
        vector<pair<int, string>> v = nodes[i];
        for (int j = 0; j < v.size(); j++)
        {
            weights[i] += stod(v[j].second);
            //converting string to double and adding the weight to the respective nodes
            weights[v[j].first] += stod(v[j].second);
        }
    }
    for (int i = 1; i < numNodes + 1; i++)
    {
        degrees.push_back(make_pair(weights[i], i)); //finally adding the weights to degrees vector
    }
    sort(degrees.rbegin(), degrees.rend()); //sorting the degrees vector in descending order based on weights

    for (int i = 0; i < degrees.size() / 2; i++)
    {
        topDegrees[degrees[i].second].first = true;   //marking true for top 50% nodes
        topDegrees[degrees[i].second].second = i + 1; // noting down the rank too
    }

    //Writing to stringstream
    //Writing header lines
    stringstream finalOutput;
    line1 = line1 + to_string(degrees.size() / 2);
    finalOutput << line1 << endl
                << line2 << endl
                << line3 << endl;

    //writing labels
    for (int i = 0; i < degrees.size() / 2; i++)
    {
        if (i != degrees.size() / 2 - 1)
            finalOutput << labels[degrees[i].second - 1] << ", ";
        else
            finalOutput << labels[degrees[i].second - 1] << endl;
    }

    //Writing data:
    finalOutput << line5 << endl;
    for (int i = 0; i < degrees.size() / 2; i++)
    {
        int u = degrees[i].second;

        for (int j = 0; j < nodes[u].size(); j++)
        {
            if (topDegrees[nodes[u][j].first].first == true)
            {
                finalOutput << i + 1 << " " << topDegrees[nodes[u][j].first].second << " " << nodes[u][j].second; //writing the edges to the string after re indexing
                if (i != degrees.size() / 2 - 1)
                    finalOutput << endl;
            }
        }
    }
    string dataToWrite = finalOutput.str();
    //sending the string to be written into output file
    write_file(dataToWrite);
    delete[] topDegrees;
    delete[] nodes; //deleting dynamically allocated memeory
}