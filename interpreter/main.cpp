#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>

using namespace std;
using namespace std::filesystem;

ifstream inputFile; //mdb
ofstream outputFile; // txt
string inputFilePath,fileContents;

vector<string> readFile();

int main() {

		vector<string> query = readFile();
		
		for (string commands : query) {
			cout << commands << endl;
		}
		return 0;
}

vector<string> readFile() {
	
	string fileName;
	vector<string> output;


	#if defined (__WIN64__)
		inputFilePath = "C:\\mariadb\\";
	#elif defined (__linux__)
		inputFilePath = "/home/thesilverghost/test/";
	#endif
	//object from preprocessor
	recursive_directory_iterator end_itr;
	for (const auto& entry: recursive_directory_iterator(inputFilePath)) {
	
		if (is_regular_file(entry.path())) {

			if (entry.path().extension() == ".mdb"){
		
				fileName = entry.path().filename();
				string newInputFilePath = inputFilePath + fileName;
				inputFile.open(newInputFilePath);

				while (getline(inputFile,fileContents)) {
				
					output.push_back(fileContents);
				}
				newInputFilePath = inputFilePath;
				inputFile.close();
			}
			else {
				cout << "Invalid input file. Perhaps the extension is wrong?" << endl;
			}
		}



		else {
		
			cout << "Object that isn't file detected in directory.\nPlease only keep files in directory" << endl;
		
		}

	}

	return output;
}
