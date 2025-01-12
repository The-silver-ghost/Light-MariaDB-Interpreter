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

string OutPutFileToUse(vector<string>& query);
void commandCreateOutPutFile(vector<string>& query, ofstream& outfile);
void commandCreateTable(vector<string>& query, ofstream& outfile,string& tableName);
void commandInsertToTable (vector<string>& query, ofstream& outfile,string& headers, int& totalInserts);
void commandSelect (vector<string>& query, ofstream& outfile);
string tableHeaders(string tableName);
void tableDisplay(ofstream& outfile);
vector<string> readFile();
vector<vector<rowType>> customerTable;


int main() {

string tableName;
string headers;
int totalInserts = 0;


    vector<string> query = readFile();


   string outPutName = OutPutFileToUse(query);
   ofstream outfile;
   outfile.open(outPutName, ios::app);



   commandCreateOutPutFile(query, outfile);
   commandCreateTable (query, outfile,tableName);
   headers = tableHeaders(tableName);
   commandInsertToTable (query, outfile, headers, totalInserts);
   commandSelect (query, outfile);
   tableDisplay(outfile);


   outfile.close();

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
            while (getline(inputFile,fileContents)) {
                output.push_back(fileContents);
            }
            fullFilePath = filePath;
            inputFile.close();
        }
    }
    return output;
}


string OutPutFileToUse(vector<string>& query)
{

    for(int i = 0; i < query.size();i++)
 {
     if (query[i].find ("CREATE fileOutput1.txt;")!= -1)
     {

      return "fileOutput1.txt";
     }
    else if (query[i].find ("CREATE fileOutput2.txt;")!= -1)
     {
      return "fileOutput2.txt";

     }
    else if (query[i].find ("CREATE fileOutput3.txt;")!= -1)
     {
      return "fileOutput3.txt";
     }

 }
  return "";
}

void commandCreateOutPutFile(vector<string>& query, ofstream& outfile)
{

    for(int i = 0; i < query.size();i++)
 {
     if (query[i].find ("CREATE fileOutput1.txt;")!= -1)
     {
      cout << query[i]<<endl;
      outfile << query[i]<<endl;
     }
    else if (query[i].find ("CREATE fileOutput2.txt;")!= -1)
     {
      cout << query[i]<<endl;
      outfile << query[i]<<endl;

     }
    else if (query[i].find ("CREATE fileOutput3.txt;")!= -1)
     {
      cout << query[i]<<endl;
      outfile << query[i]<<endl;
     }

 }

}


void commandCreateTable(vector<string>& query, ofstream& outfile,  string& tableName)
{

    for(int i = 0; i < query.size();i++)
   {
        if (query[i].find ("CREATE TABLE")!= -1)
    {
        cout <<query[i]<<endl;
        outfile<<query[i]<<endl;
        tableName = query [i];
        tableName.erase(0, 13);
        tableName.erase(tableName.find('('), 1);



        while (i < query.size() && query[i].find(");") ==-1)
        {
            i++;
            cout<<query[i]<<endl;
            outfile<<query[i]<<endl;
;

        }

        break;
    }

   }
}



string tableHeaders(string tableName)

{
 string headers = tableName + "(customer_id,customer_name,customer_city,customer_state,customer_country,customer_phone,customer_email)";


return headers;

}


void commandInsertToTable (vector<string>& query, ofstream& outfile,string& headers, int& totalInserts)
{
totalInserts = 0;

    for(int i = 0; i < query.size();i++)
   {
        if (query[i].find ("INSERT INTO")!= -1)
    {       totalInserts++;



            rowType row ;

            row.customer_ID = totalInserts;
            row.customer_Name = "name" + to_string(totalInserts) ;
            row.customer_City = "city" + to_string(totalInserts) ;
            row.customer_State = "state" + to_string (totalInserts) ;
            row.customer_Country = "country" + to_string(totalInserts) ;
            row.customer_Phone = "phone" + to_string (totalInserts) ;
            row.customer_Email = "email"+ to_string (totalInserts) ;

        cout  <<query[i]<<endl
              <<headers
              <<" VALUES ("
              <<row.customer_ID<< ",'"
              <<row.customer_Name<<"','"
              <<row.customer_City<<"','"
              <<row.customer_State<<"','"
              <<row.customer_Country<<"','"
              <<row.customer_Phone<<"','"
              <<row.customer_Email<<"');"<<endl;

      outfile <<query[i]<<endl
              <<headers
              <<" VALUES ("
              <<row.customer_ID<< ",'"
              <<row.customer_Name<<"','"
              <<row.customer_City<<"','"
              <<row.customer_State<<"','"
              <<row.customer_Country<<"','"
              <<row.customer_Phone<<"','"
              <<row.customer_Email<<"');"<<endl;



           vector<rowType>values;
           values.push_back(row);
           customerTable.push_back(values);


    }
   }


}

void commandSelect (vector<string>& query, ofstream& outfile)
{

    for(int i = 0; i < query.size();i++)
   {
        if (query[i].find ("SELECT")!= -1)
    {
        cout<<query[i]<<endl;
        outfile<<query[i]<<endl;

   }


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
