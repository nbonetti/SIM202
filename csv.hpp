#ifndef CSVREADER_HPP
#define CSVREADER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>



using namespace std;
//fonction pour lire le fichier 
vector<vector<double>> csv_reader(string fname);

//fonction pour récupérer les données et avoir un nouveau fichier 
void csv_write(vector<double> parcours);
#endif