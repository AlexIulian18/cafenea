#ifndef Files_H
#define Files_H

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

vector<vector<string>> readCSV(const string& filename);
void writeCSV(const string& filename, const vector<vector<string>>& data, bool append);


vector<string> splitLine(const string& line, char delimiter);
vector<string> splitString(const string& input, char delimiter);
string capitalizeWords(const string& input);
string joinString(const vector<string>& vec, const string& delimiter);


#endif