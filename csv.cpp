//Fonction pour lire le fichier

#include "csv.hpp"
using namespace std;          

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
                {num=stod(word);
                //cout << "blah " << num << endl;
                row.push_back(num);}
            content.push_back(row);
        }
    }
      
    else{
        cout<<"Could not open the file\n";
        
        }
    
    return content;
}




void csv_write(vector<double> parcours)
{
      std::ofstream myfile;
      myfile.open ("solution_csv");
      myfile << "Chemin_solution\n";
      int x;
      int n=parcours.size();
      for (int i=0;i<n;i++){
            x=parcours[i];
            myfile << x ;
            myfile << "\n";
      }
      myfile.close();
}