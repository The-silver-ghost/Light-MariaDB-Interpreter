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
	for (const auto entry: recursive_directory_iterator(inputFilePath)) {
	
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
