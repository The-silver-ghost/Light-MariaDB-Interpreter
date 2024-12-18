#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> //for os commands
using namespace std;

ifstream inputFile; //mdb
ofstream outputFile; // txt
string inputFilePath,fileContents;

string readFile();

int main() {

		string output = readFile();
		cout << output  << endl;
		return 0;
}

string readFile() {
	string output;

	cout << "Enter path to input file:" << endl;
	getline(cin, inputFilePath);
	inputFile.open(inputFilePath);
	if (!inputFile) {
		cout << "File path error." << endl;
	}

	while (getline (inputFile,fileContents)) {
		
		output = output + "\n" + fileContents;
	}

	inputFile.close();
	return output;
}

