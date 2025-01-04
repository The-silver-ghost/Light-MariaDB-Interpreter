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
struct RowType
{
    int userId;
    string userName;
    string userCity;
    string userState;
    string userCountry;
    string userPhone;
    string userEmail;
};
void tableDisplay (vector <RowType>& userDetails,ofstream& outfile );
vector<RowType> intialRows();

vector<string> readFile();

int main() {
    
   vector <RowType> userDetails = intialRows();

   ofstream outfile;

   outfile.open("output1.txt");

   tableDisplay (userDetails,outfile );

   outfile.close();
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
vector<RowType> intialRows()
{
   return
   {
    {1,"name1","city1","state1","country1","phone1","email1"},
    {2,"name2","city2","state2","country2","phone2","email2"},
    {3,"name3","city3","state3","country3","phone3","email3"}

};

}


void tableDisplay (vector <RowType>& userDetails,ofstream& outfile )

{
    for (int i = 0; i < userDetails.size() ; i++)
{

 outfile << userDetails[i].userId<<","
         << userDetails[i].userName<<","
         << userDetails[i].userCity<<","
         << userDetails[i].userState<<","
         << userDetails[i].userCountry<<","
         << userDetails[i].userPhone<<","
         << userDetails[i].userEmail<<endl;

}

}
