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
#include "selection.hpp"
#include "csv_reader.hpp"
using namespace std;


int main()

{/*=========================================================================================================
//                                             LECTURE DU FICHIER 
//==========================================================================================================
*/
    vector<vector<double>> content= csv_reader("Villes_csv");//on récupère le fichier 

//========================================================================================
//                                      DEBUT 
//========================================================================================
    vector<int> citynumber;
    vector<Point> coord;
    vector<double> vmin;
    int i = 0;
    int k = 0;

    Ville city(citynumber,coord);
    Population paths;//population initaile avec tou sles chemins possibles avec le fichier de départ 
    int nombre_chemins; //choisir le nombre de chemins que l'on veut dans notre porpulation

//faire une fonction qui génère la population totale avec tous les chemins possibles avec le fichier de départ 
    generateur_chemins(nombre_chemins,city,paths);
    paths.print(cout);


    Population enfants; 
    int p; //choisir nous mêmes 
    //test d'arrêt 
    while (k<=5 && i<=100)
    {
        //SELECTION DE LA POPULATION  
        Population selection=selection_rang(paths);
        //Population selection=select_roulette(paths,p);
        //Population selection=select_eugenisme(paths,p);

        paths.trierPopulation(&Individu::poids);
        Individu* I=paths.getIndividu(0);
        double minimum= I->poids();

        //HYBRIDATION 
        //il me faut deux parents que je sélectionne dans la population selection 
        //pour choisir ces parents, on le fait de manière aléatoire
        int i_1=rand() % (nombre_chemins/2);
        int i_2=rand() % (nombre_chemins/2);

        Individu* individu_1=selection.getIndividu(i_1);
        Individu* individu_2=selection.getIndividu(i_2);


        

    }


}



