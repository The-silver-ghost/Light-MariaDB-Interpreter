// *********************************************************
// Program: main.cpp
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC8L
// Tutorial Class: T16L
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

//global vars
ifstream inputFile;
ofstream outfile;
int totalInserts = 0;

//functions
string OutPutFileToUse(string query);
void commandCreateOutPutFile(string& query);
vector<vector<string>> commandCreateTable(string& query,string& tableName,vector<vector<string>> table);
vector<vector<string>> commandInsertToTable (string& query,vector<vector<string>> table,string tableName);
void commandSelect (string& query);
void tableDisplay(ofstream& outfile,vector<vector<string>>);
vector<string> readFile();
vector<vector<string>> deleteTableRow(string, vector<vector<string>>);
string removeWhitespace(string);
vector<vector<string>> appendToVector(vector<vector<string>> table,string strToBeAppended);
void displayCommands(string,string);
void displayDatabase(int,string);

int main() {
    string tableName;
    vector<vector<string>> customerTable;
    int fileNumber = 1;

    vector<string> query = readFile();
    for (string commands : query){
        if (commands.find("-1") != string::npos){
            totalInserts = 0;
            fileNumber += 1;
            customerTable.clear();
            outfile.close();
        }
        else if (commands.find("CREATE TABLE") != string::npos){
            customerTable = commandCreateTable(commands,tableName,customerTable);
        }
        else if (commands.find("DELETE")!=string::npos) {
            customerTable = deleteTableRow(commands,customerTable);
        }
        else if (commands.find("DATABASE")!= string::npos) {
            displayDatabase(fileNumber,commands);
        }
        else if (commands.find("SELECT COUNT")!= string::npos) {
            displayCommands(commands,"SELECT");
            cout << totalInserts << endl;
            outfile << totalInserts << endl;
        }
        else if (commands.find("SELECT")!= string::npos) {
            commandSelect(commands);
            tableDisplay(outfile,customerTable);
        }
        else if (commands.find("UPDATE")!= string::npos) {
            cout << "UPDATE" << endl;
        }
        else if (commands.find("TABLES")!= string::npos) {
            displayCommands(commands,"TABLES");
            cout << tableName << endl;
            outfile << tableName << endl;
        }
        else if (commands.find("CREATE")!= string::npos) {
            string outPutName = OutPutFileToUse(commands);
            outfile.open(outPutName);
            commandCreateOutPutFile(commands);
        }
        else if (commands.find("INSERT INTO")!= string::npos) {
            customerTable = commandInsertToTable(commands,customerTable,tableName);
        }
        else {
           cout << "";
        }
    }
    return 0;
}

vector <string> readFile() {
    vector<string> output;
    string fileContents;
    string fileName[3] = {"fileInput1.mdb","fileInput2.mdb","fileInput3.mdb"};
    string filePath = "C:\\mariadb\\";

    for (string name: fileName){
        string fullFilePath = filePath+name;
        inputFile.open(fullFilePath);

        if (!inputFile) {
            cout << "File not found in target directory" << endl;
        }
        else {
            while (getline(inputFile,fileContents,';')) {
                output.push_back(fileContents);
            }
            fullFilePath = filePath;
            inputFile.close();
        }
        output.push_back("-1");
    }
    return output;
}

string OutPutFileToUse(string query)
{
    query.erase(0,6);
    query = removeWhitespace(query);
    return query;
}

void commandCreateOutPutFile(string& query)
{
    displayCommands(query,"CREATE");
}

vector<vector<string>> commandCreateTable(string& query,string& tableName,vector<vector<string>> table)
{
        vector<string> headers;
        string tableColumnHeaders = query,tempStr;

        displayCommands(query,"CREATE TABLE");
        //acquire table name
        tableName = query;
        tableName.erase(0, 14);
        tableName.erase(tableName.find('('), -1);
        tableName = removeWhitespace(tableName);
        //acquire table Columns
        tableColumnHeaders.erase(0,tableColumnHeaders.find("("));

        //remove unnecessary info
        for (int count = 0; count < tableColumnHeaders.size(); count++){
            if (tableColumnHeaders.find(" ")!=string::npos)
                tableColumnHeaders.erase(tableColumnHeaders.find(" "),1);
            else if (tableColumnHeaders.find("INT")!=string::npos)
                tableColumnHeaders.erase(tableColumnHeaders.find("INT"),3);
            else if (tableColumnHeaders.find("TEXT")!=string::npos)
                tableColumnHeaders.erase(tableColumnHeaders.find("TEXT"),4);
            else if (tableColumnHeaders.find("\n")!=string::npos)
                tableColumnHeaders.erase(tableColumnHeaders.find("\n"),1);
        }
        table = appendToVector(table, tableColumnHeaders);
        return table;
}

vector<vector<string>> commandInsertToTable (string& query,vector<vector<string>> table, string tableName)
{
    string values = query;

    displayCommands(query,"INSERT INTO");
    values.erase(0,7+values.find("VALUES"));

    table = appendToVector(table,values);
    totalInserts += 1;
    return table;
}

void commandSelect (string& query)
{
    displayCommands(query,"SELECT");
}

void tableDisplay(ofstream& outfile,vector<vector<string>> table)
{
    for (int rows = 0; rows<table.size(); rows++){
        if (rows > 0){
            cout << endl;
            outfile << endl;
        }
        for (int columns = 0; columns<table[rows].size(); columns++){
            cout << table[rows][columns] << ",";
            outfile << table[rows][columns] << ",";
        }
    }
    cout << endl;
    outfile << endl;
}
// to delete rows of the table
vector<vector<string>> deleteTableRow(string query, vector<vector<string>> table)
{
    displayCommands(query,"DELETE");
    string rowToBeDeleted = query;
    int row;

    rowToBeDeleted.erase(0,rowToBeDeleted.find("=")+1);
    row = stoi(rowToBeDeleted);
    table[row].clear();
    totalInserts -= 1;

    return table;
}

string removeWhitespace(string strWithSpaces){
    int stringSize = strWithSpaces.size();
    string newString;

    for (int count = 0; count < stringSize; count ++){
        if (strWithSpaces[count] != ' '){
            newString += strWithSpaces[count];
        }
    }
    return newString;
}

vector<vector<string>> appendToVector(vector<vector<string>> table, string strToBeAppended){
    string tempStr;
    vector<string> row;

    for (int count = 1; count < strToBeAppended.size() - 1; count++){
            if (strToBeAppended[count] != ','){
                tempStr += strToBeAppended[count];
            }
            else{
                row.push_back(tempStr);
                tempStr = "";
            }
    }
    table.push_back(row);
    return table;
}

void displayCommands(string cmd,string beginningWord){
    cmd.erase(0,cmd.find(beginningWord));
    cout << ">" << cmd << ";" << endl;
    outfile << ">" << cmd << ";" << endl;
}

void displayDatabase(int fileNum,string cmd){
    displayCommands(cmd,"DATABASES");

    if (fileNum == 1){
        cout << "C:\\mariadb\\fileInput1.mdb" << endl;
        outfile << "C:\\mariadb\\fileInput1.mdb" << endl;
    }
    else if (fileNum == 2){
        cout << "C:\\mariadb\\fileInput2.mdb" << endl;
        outfile << "C:\\mariadb\\fileInput2.mdb" << endl;
    }
    else if (fileNum == 3){
        cout << "C:\\mariadb\\fileInput3.mdb" << endl;
        outfile << "C:\\mariadb\\fileInput3.mdb" << endl;
    }
}
