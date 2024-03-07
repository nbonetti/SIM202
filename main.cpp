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


int main()

{/*=========================================================================================================
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
    Population paths;//population initaile avec tou sles chemins possibles avec le fichier de départ 
    int nombre_chemins; //choisir le nombre de chemins que l'on veut dans notre porpulation

//faire une fonction qui génère la population totale avec tous les chemins possibles avec le fichier de départ 
//generateur_chemins(nombre_chemins,city,paths);
    paths.print(cout);


    Population enfants; 
    

}



