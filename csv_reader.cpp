#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
 
using namespace std;          //allow to use cin/cout instead of std::cin


void csv_reader(string fname){
    
    vector<vector<string>> content;
    vector<string> row;
    string line, word;         //store the line and then the word in the line
 
    fstream file (fname, ios::in);
    if(file.is_open())
    {
        while(getline(file, line))
        {
            row.clear();
 
            stringstream str(line);
 
            while(getline(str, word, ','))  //Le fichier csv est séparé par des virgules
                row.push_back(word);
            content.push_back(row);
        }
    }
      
    else{
        cout<<"Could not open the file\n";
        return -1;
        }
    
    return content;
}




int main()
{
    string fname;              //store the file name
    cout<<"Enter the file name: ";
    cin>>fname;

vector<vector<string>> content;
    vector<string> row;
    string line, word;         //store the line and then the word in the line
 
    fstream file (fname, ios::in);
    if(file.is_open())
    {
        while(getline(file, line))
        {
            row.clear();
 
            stringstream str(line);
 
            while(getline(str, word, ','))  //Le fichier csv est séparé par des virgules
                row.push_back(word);
            content.push_back(row);
        }
    }
      
    else{
        cout<<"Could not open the file\n";
        }


    for(int i=0;i<content.size();i++)
    {
        for(int j=0;j<content[i].size();j++)
        {
            cout<<content[i][j]<<" ";
        }
        cout<<"\n";
    }
    return 0;
}
