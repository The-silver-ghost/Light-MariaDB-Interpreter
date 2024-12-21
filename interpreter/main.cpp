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

		string query = readFile();
		cout << query  << endl;
		return 0;
}

string readFile() {
	string output;
	
	#if defined (__WIN64__) 
		inputFile.open("C:\\mariadb\\*");

	#elif defined (__linux__) 
		inputFile.open("/home/thesilverghost/test/test.mdb");
	#endif

	if (!inputFile) {
	cout << "" << endl;
	}

	while (getline (inputFile,fileContents)) {
		
		output = output + "\n" + fileContents;
	}

	inputFile.close();
	return output;
}
