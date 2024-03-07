#include <cmath>
#include <cstdlib>
#include <vector>
#include <random>
#include <ctime>
#include <list>
#include <iostream>
#include <fstream>
#include <string>

#include "algogenetique.hpp"
#include "voyage.hpp"
#include "Factory.hpp"
#include "csv_reader.hpp"
using namespace std;



/*=========================================================================================================
//                                             LECTURE DU FICHIER 
//==========================================================================================================
*/
vector<vector<double>> content= csv_reader("Villes_csv");//on récupère le fichier 


vector<int> citynumber;
vector<Point> coord;
vector<double> vmin;
int i = 0;
int k = 0;

Ville city(citynumber,coord);



