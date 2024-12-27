// *********************************************************
// Program: YOUR_FILENAME.cpp
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC3L
// Tutorial Class: TT5L
// Trimester: 2430
// Member_1: 243UC245LQ | Sanjeevan A/L Rames | SANJEEVAN.RAMES@student.mmu.edu.my | 0176874937
// Member_2: 243UC241FF | Youssef M.A. Abdul Razek | youssef.m.a1@student.mmu.edu.my | 966 54 935 7758
// Member_3: 243UC2400B | Ousama M.A. Abdul Razek | ousama.m.a2@student.mmu.edu.my | +966 50 703 1726
// Member_4: 243UC246VV | SUHEN KAILASH | suhen.kailash@student.mmu.edu.my | 60 11-1124 0726
// *********************************************************
// Task Distribution
// Member_1:read file, database,update
// Member_2:create, select
// Member_3:table,insert into
// Member_4:select count,delete
// *********************************************************
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

ifstream inputFile;
string filePath = "C:\\mariadb\\";


vector<string> readFile();

int main() {
    vector<string> query = readFile();
    for (string commands:query) {
        cout << commands << endl;
    }
    return 0;
}

vector <string> readFile() {
    vector<string> output;
    string fileName,fileContents;

    cout << "Filename? (Case-sensitive,include extension)" << endl;
    cout << ">";
    cin >> fileName;

    string fullFilePath = filePath+fileName;
    inputFile.open(fullFilePath);

    if (!inputFile) {
        cout << "File not found in target directory" << endl;
    }
    else {
        while (getline(inputFile,fileContents)) {
            output.push_back(fileContents);
        }
        fullFilePath = filePath;
        inputFile.close();
    }
    return output;
}
