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

ifstream inputFile;
ofstream outfile;
string filePath = "C:\\mariadb\\";

struct rowType
{
    int customer_ID;
    string customer_Name;
    string customer_City;
    string customer_State;
    string customer_Country;
    string customer_Phone;
    string customer_Email;
};

string OutPutFileToUse(string query);
void commandCreateOutPutFile(string& query);
vector<vector<string>> commandCreateTable(string& query,string& tableName);
vector<vector<string>> commandInsertToTable (string& query,vector<vector<string>> table,string tableName);
void commandSelect (string& query);
string tableHeaders(string tableName);
void tableDisplay(ofstream& outfile,vector<vector<string>>);
vector<string> readFile();
void deleteTableRow(int);
void countTableRows();
string removeWhitespace(string);
vector<vector<string>> appendToVector(vector<vector<string>> table,string strToBeAppended);
void displayCommands(string);

//vector<vector<rowType>> customerTable;


int main() {

    string tableName;
    string headers;
    int totalInserts = 0;

    vector<vector<string>> customerTable;

    vector<string> query = readFile();
    for (string commands : query){
        if (commands.find("-1") != string::npos){
            totalInserts = 0;
            customerTable.clear();
            outfile.close();
        }
        else if (commands.find("CREATE TABLE") != string::npos){
            headers = tableHeaders(tableName);
            customerTable = commandCreateTable(commands,tableName);
        }
        else if (commands.find("DELETE")!=string::npos) {
            cout << "delete" << endl;
        }
        else if (commands.find("DATABASE")!= string::npos) {
            cout << "DATABASE" << endl;
        }
        else if (commands.find("SELECT COUNT")!= string::npos) {
            cout << "SELECT COUNT" << endl;
        }
        else if (commands.find("SELECT")!= string::npos) {
            commandSelect(commands);
            tableDisplay(outfile,customerTable);
        }
        else if (commands.find("UPDATE")!= string::npos) {
            cout << "UPDATE" << endl;
        }
        else if (commands.find("TABLES")!= string::npos) {
            displayCommands(commands);
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
           cout << "Invalid commands" << endl;
        }
    }
    return 0;
}

vector <string> readFile() {
    vector<string> output;
    string fileContents;
    string fileName[3] = {"fileInput1.mdb","fileInput2.mdb","fileInput3.mdb"};

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
    cout << ">" << query << ";" << endl;
    outfile << ">" << query << ";" << endl;
}

vector<vector<string>> commandCreateTable(string& query,string& tableName)
{
        vector<vector<string>> table;
        vector<string> headers;
        string tableColumnHeaders = query,tempStr;

        displayCommands(query);
        //acquire table name
        tableName = query;
        tableName.erase(0, 14);
        tableName.erase(tableName.find('('), -1);
        tableName = removeWhitespace(tableName);

        return table;
}

string tableHeaders(string tableName)
{
    string headers = tableName + "(customer_id,customer_name,customer_city,customer_state,customer_country,customer_phone,customer_email)";
    return headers;
}
vector<vector<string>> commandInsertToTable (string& query,vector<vector<string>> table, string tableName)
{
    string values = query;

    displayCommands(query);
    values.erase(0,7+values.find("VALUES"));

    table = appendToVector(table,values);
    return table;
}

void commandSelect (string& query)
{
    displayCommands(query);
}

void tableDisplay(ofstream& outfile,vector<vector<string>> table)
{
    for (int rows = 0; rows<table.size(); rows++){
        cout << endl;
        outfile << endl;
        for (int columns = 0; columns<table[rows].size(); columns++){
            cout << table[rows][columns] << ",";
            outfile << table[rows][columns] << ",";
        }
    }
    cout << endl;
    outfile << endl;
}
// to delete rows of the table
void deleteTableRow(int customerID)
{/*
    bool found = false;
    for (auto it = customerTable.begin(); it != customerTable.end(); ++it)
    {
        if (!it->empty() && it->front().customer_ID == customerID)
        {
            customerTable.erase(it);
            found = true;
            cout << "Deleted row with ID: " << customerID << endl;
            break;
        }
    }
    if (!found)
    {
        cout << "Row with ID: " << customerID << " not found." << endl;
    }
*/}
// view table content
void viewTableContent()
{/*
    cout << "Table Content:" << endl;
    for (const auto &rowGroup : customerTable)
    {
        for (const auto &row : rowGroup)
        {
            cout << row.customer_ID << ", " << row.customer_Name << ", "
            << row.customer_City << ", " << row.customer_State << ", "
            << row.customer_Country << ", " << row.customer_Phone << ", "
            << row.customer_Email << endl;
        }
    }
*/}
    // count the table rows
    void countTableRows() {/*
    int rowCount = 0;

    for (const auto& rowGroup : customerTable) {
        rowCount += rowGroup.size(); // Add the size of each row group
    }

    // Output the row count
    cout << "Number of rows in the table: " << rowCount << endl;
*/}

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

void displayCommands(string cmd){
    cout << ">" << cmd.erase(0,1) << ";" << endl;
    outfile << ">" << cmd << ";" << endl;
}
