#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
 
using namespace std;          //allow to use cin/cout instead of std::cin


vector<vector<double>> csv_reader(string fname){
    
    vector<vector<double>> content;
    vector<double> row;
    string line, word;         //store the line and then the word in the line
    double num;
 
    fstream file (fname, ios::in);
    if(file.is_open())
    {
        while(getline(file, line))
        {
            row.clear();
 
            stringstream str(line);
 
            while(getline(str, word, ','))  //Le fichier csv est séparé par des virgules
                num=stod(word);
                row.push_back(num);
            content.push_back(row);
        }
    }
      
    else{
        cout<<"Could not open the file\n";
        
        }
    
    return content;
}
