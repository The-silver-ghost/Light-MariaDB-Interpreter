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
void commandCreateOutPutFile(string& query, ofstream& outfile);
void commandCreateTable(string& query, ofstream& outfile,string& tableName);
void commandInsertToTable (string& query, ofstream& outfile,string& headers, int& totalInserts);
void commandSelect (string& query, ofstream& outfile);
string tableHeaders(string tableName);
void tableDisplay(ofstream& outfile);
vector<string> readFile();
void deleteTableRow(int);
void countTableRows();
string removeWhitespace(string);

vector<vector<rowType>> customerTable;


int main() {

    string tableName;
    string headers;
    int totalInserts = 0;
    ofstream outfile;



    vector<string> query = readFile();
    for (string commands : query){
        if (commands.find("-1") != string::npos){
            totalInserts = 0;
            customerTable.clear();
            outfile.close();
        }
        else if (commands.find("CREATE TABLE") != string::npos){
            headers = tableHeaders(tableName);
            commandCreateTable(commands, outfile,tableName);
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
            commandSelect(commands, outfile);
            tableDisplay(outfile);
        }
        else if (commands.find("UPDATE")!= string::npos) {
            cout << "UPDATE" << endl;
        }
        else if (commands.find("TABLES")!= string::npos) {
            cout << "TABLES"<< endl;
        }
        else if (commands.find("CREATE")!= string::npos) {
            string outPutName = OutPutFileToUse(commands);
            outfile.open(outPutName);
            commandCreateOutPutFile(commands, outfile);
        }
        else if (commands.find("INSERT INTO")!= string::npos) {
            commandInsertToTable(commands, outfile, headers, totalInserts);
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

void commandCreateOutPutFile(string& query, ofstream& outfile)
{
    cout << query<<endl;
    outfile << query<<endl;
}

void commandCreateTable(string& query, ofstream& outfile,  string& tableName)
{
        if (query.find ("CREATE TABLE")!= string::npos)
        {
            cout <<query<<endl;
            outfile<<query<<endl;
            tableName = query;
            tableName.erase(0, 14);
            tableName.erase(tableName.find('('), -1);
            tableName = removeWhitespace(tableName);
        }
}

string tableHeaders(string tableName)
{
    string headers = tableName + "(customer_id,customer_name,customer_city,customer_state,customer_country,customer_phone,customer_email)";
    return headers;
}

void commandInsertToTable (string& query, ofstream& outfile,string& headers, int& totalInserts)
{
        if (query.find ("INSERT INTO")!= string::npos)
        {
            totalInserts++;
            rowType row ;

            row.customer_ID = totalInserts;
            row.customer_Name = "name" + to_string(totalInserts) ;
            row.customer_City = "city" + to_string(totalInserts) ;
            row.customer_State = "state" + to_string (totalInserts) ;
            row.customer_Country = "country" + to_string(totalInserts) ;
            row.customer_Phone = "phone" + to_string (totalInserts) ;
            row.customer_Email = "email"+ to_string (totalInserts) ;

            cout  <<query<<endl;
            outfile <<query<<endl;

            vector<rowType>values;
            values.push_back(row);
            customerTable.push_back(values);
    }
}

void commandSelect (string& query, ofstream& outfile)
{
    if (query.find ("SELECT")!= string::npos)
    {
        cout<<query<<endl;
        outfile<<query<<endl;
    }
}

void tableDisplay(ofstream& outfile)
{
    for (int i = 0; i < customerTable.size();i++)
    {
        for(int j = 0; j < customerTable[i].size();j++)
        {
            cout << customerTable[i][j].customer_ID<<","
            << customerTable[i][j].customer_Name<<","
            <<customerTable[i][j].customer_City<<","
            <<customerTable[i][j].customer_State<<","
            <<customerTable[i][j].customer_Country<<","
            <<customerTable[i][j].customer_Phone<<","
            <<customerTable[i][j].customer_Email<<endl;

            outfile << customerTable[i][j].customer_ID<<","
            << customerTable[i][j].customer_Name<<","
            <<customerTable[i][j].customer_City<<","
            <<customerTable[i][j].customer_State<<","
            <<customerTable[i][j].customer_Country<<","
            <<customerTable[i][j].customer_Phone<<","
            <<customerTable[i][j].customer_Email<<endl;
            }
    }
}
// to delete rows of the table
void deleteTableRow(int customerID)
{
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
}
// view table content
void viewTableContent()
{
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
}
    // count the table rows
    void countTableRows() {
    int rowCount = 0;

    for (const auto& rowGroup : customerTable) {
        rowCount += rowGroup.size(); // Add the size of each row group
    }

    // Output the row count
    cout << "Number of rows in the table: " << rowCount << endl;
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
