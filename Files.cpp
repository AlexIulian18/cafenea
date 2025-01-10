#include "Files.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

vector<string> splitLine(const string& line, char delimiter) {
    vector<string> result;
    stringstream ss(line);
    string field;

    while (getline(ss, field, delimiter)) {
        result.push_back(field);
    }

    return result;
}

// Funcție generală pentru a împărți orice șir de caractere
vector<string> splitString(const string& input, char delimiter) {
    vector<string> result;
    stringstream ss(input);
    string token;

    while (getline(ss, token, delimiter)) {
        result.push_back(token);
    }

    return result;
}

vector<vector<string>> readCSV(const string& filename){
    ifstream file(filename);
    if(!file.is_open()){
        cerr << "Eroare: Nu s-a putut deschide fisierul " << filename << endl;
        throw runtime_error("Eroare: Nu s-a putut deschide fisierul " + filename);
    }

    vector<vector<string>> allLines;
    string line;

    while(getline(file,line)){

        allLines.push_back(splitLine(line, ','));
    }

    file.close();
    return allLines;
}

void writeCSV(const string& filename, const vector<vector<string>>& data, bool append){
    ofstream file;
    if (append) {
        file.open(filename, ios::app); // Deschide fișierul în modul append
    } else {
        file.open(filename); // Suprascrie fișierul
    }

    if(!file.is_open()){
        throw runtime_error("Eroare: Nu s-a putut deschide fisierul " + filename);
    }

    // Dacă adaugi într-un fișier existent, trebuie să te asiguri că fișierul se termină cu newline
    if (append) {
        // Deschidem fișierul pentru citire pentru a verifica ultimul caracter
        ifstream readFile(filename);
        if (readFile.is_open()) {
            // Mergem la sfârșitul fișierului
            readFile.seekg(-1, ios::end);
            char lastChar;
            readFile.get(lastChar); // Citim ultimul caracter

            // Dacă ultimul caracter nu este un newline, adăugăm unul
            if (lastChar != '\n') {
                file.put('\n'); // Scriem newline înainte de a adăuga noile date
            }

            readFile.close();
        }
    }

    for(const auto& line : data){
        for(size_t i = 0; i < line.size(); ++i){
            file << line[i];
            if(i != line.size() - 1) file << ",";
        }
        file << endl;
    }
    file.close();
}

string capitalizeWords(const string& input) {
    stringstream ss(input);
    string word, result;
    bool firstWord = true;

    while (ss >> word) {
        // Transformă prima literă în majusculă, restul în minusculă
        word[0] = toupper(word[0]);

        if (!firstWord) {
            result += " ";
        }
        result += word;
        firstWord = false;
    }

    return result;
}

string joinString(const vector<string>& vec, const string& delimiter) {
    string result;
    for (size_t i = 0; i < vec.size(); ++i) {
        result += vec[i];
        if (i < vec.size() - 1) {
            result += delimiter;
        }
    }
    return result;
}

string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}