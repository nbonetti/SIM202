#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "csv.hpp"
using namespace std;          //allow to use cin/cout instead of std::cin

//fonction pour lire le fichier
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
                cout << "blah " << num << endl;
                row.push_back(num);
            content.push_back(row);
        }
    }
      
    else{
        cout<<"Could not open the file\n";
        
        }
    
    return content;
}



//fonction pour récupérer les données et avoir un nouveau fichier 
void csv_write(int* parcours, int n_index)
{
      std::ofstream myfile;
      myfile.open ("solution.csv");
      myfile << "index\n";
      int x;
      for (int i=0;i<n_index;i++){
            x=parcours[i];
            myfile << x ;
            myfile << "\n";
      }
      myfile.close();
}